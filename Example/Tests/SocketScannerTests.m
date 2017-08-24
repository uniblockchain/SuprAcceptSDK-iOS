//
//  TestDomainDataServices.m
//  acceptSDK
//
//  Created by Danko, Radoslav on 17/10/15.
//  Copyright © 2015 Wirecard. All rights reserved.
//


#import <XCTest/XCTest.h>
#import <libextobjc/EXTScope.h>
#import "SaleHelper.h"
#import "UserHelper.h"
#import "DDLog.h"
#import <Accept/NSString+AcceptExtras.h>

@interface SocketScannerTestsObjC : XCTestCase <AcceptSDKDelegate, WDAcceptScanning>
{
    __block NSError *returnedErr;
    __weak XCTestExpectation *expectation;
    AcceptSDK *sdk;
    __block NSArray *scannersArray;
}

@end

/*
 
 Note: when using Socket Scanner pod/library, you are required to have some libstdc++ linked in your frameworks
 and libraries to be able to compile.
 
*/

@implementation SocketScannerTestsObjC

- (void)setUp
{
    [super setUp];
    self.continueAfterFailure = NO;
    sdk = [AcceptSDK sharedInstance];
    expectation = [self expectationWithDescription:@"Setup"];
    [sdk setupWithEnvironment:AcceptEnvironmentPublicTest username:KUSERNAME password:KPASSWORD completion:^(WDAcceptMerchantUser * _Nullable currentUser, WDAcceptMerchantCashier * _Nullable cashier, NSError * _Nullable error) {
        [sdk addDelegate:self];
        [sdk setDevMode:YES]; //Setting dev mode as enabled will write logs in your app's document folder and fill the console log with debug messages - do not forget to disable it
                              //before releasing your app to the public!!
        [AcceptSDK ddSetLogLevel:DDLogLevelInfo];
        [expectation fulfill];
    }];
    
    [self waitForExpectationsWithTimeout:25 handler:nil];
    
    XCTAssert(true,@"Setup success");
}

-(void)testSocketScanner
{
#if TARGET_OS_SIMULATOR
    NSLog(@"\n\t\t   %s Not runnable on simulator 📱",__PRETTY_FUNCTION__);
    return;
    
#endif
    
    //PART 1: We discover Socket scanners
    //paired to your iOS device.
    //--------------------------------------
    expectation = [self expectationWithDescription:@"Discovering devices"];
    [self discoverDevices];
    [self waitForExpectationsWithTimeout:100 handler:nil];
    if (![scannersArray firstObject] || ![[scannersArray firstObject] isKindOfClass:[WDAcceptTerminal class]])
    {
        XCTFail(@"No paired scanner found. Make sure your terminal is paired in your iOS device settings and that the scanner is in stand-by mode (ie. by switching off and then on). For pairing you need to scan the pairing barcode in your Socket Scanner printed instructions");
    }

    //PART 2: We set delegate for listening
    //on paired scanner.
    //--------------------------------------
    expectation = [self expectationWithDescription:@"Setting active scanner to listen to"];
    [self setDelegateAndActiveScanner];
    [self waitForExpectationsWithTimeout:100 handler:nil];
}

-(void)discoverDevices
{
    DeviceDiscoveryCompletion completionTerminals = ^(NSArray *arr, NSError *err)
    {
        returnedErr = err;
        scannersArray = arr;
        [expectation fulfill];
    };
    
    [sdk.scannerManager discoverDevices:WDASocketExtensionUUID completion:completionTerminals];
}

-(void)setDelegateAndActiveScanner
{
    [sdk.scannerManager addScannerManagerDelegate:self forScanner:scannersArray.firstObject];
    
    //When something is scanned, it will trigger the function below, dataReceived. So please, scan a barcode to pass the test.
    //You have a barcode in this demo, a file image under the name barcode_example
}

- (void)device:(WDAcceptTerminal*)device dataReceived:(NSData *)dataReceived
{
    //It is a good practice to remove control characters as scanners have the bad tendency to add garbage at the end most of the time.
    NSString *barcodeAsText = [[[NSString alloc] initWithData:dataReceived encoding:NSUTF8StringEncoding] stringByRemovingControlCharacters];
    NSLog(@"Barcode read with value as string: %@", barcodeAsText);
    [expectation fulfill];
}

-(void)device:(WDAcceptTerminal *)device batteryLevelDidChange:(NSInteger)batteryLevel
{
    //This is a delegate function that will be called when there is a battery level change
    NSLog(@"Battery level for Socket Scanner is currently %ld", (long)batteryLevel);
}

@end
