//
//  CashTests.m
//  AlphaMPOS
//
//  Created by Francisco Fortes on 31/10/16.
//  Copyright © 2016 Wirecard. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <libextobjc/EXTScope.h>
#import "BaseTests.h"

@implementation BaseTestsObcj

- (void)setUp
{
    [super setUp];
    self.continueAfterFailure = NO;
    sdk = [AcceptSDK sharedInstance];
    saleHelper = [SaleHelper sharedInstance];
    userHelper = [UserHelper sharedInstance];
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

- (void)tearDown
{
    [super tearDown];
}

-(void)loginAndGetUserData
{
    MerchantDetailCompletion completion = ^(WDAcceptMerchantUser *merchantUser, NSError *err)
    {
        loggedUser = merchantUser;
        returnedErr = err;
        [expectation fulfill];
    };
    loggedUser = nil;
    [[sdk userManager] currentUser:completion];
}

-(void)discoverDevices:(WDAExtensionTypeUUID)extensionUUID
{
    DeviceDiscoveryCompletion completionTerminals = ^(NSArray *arr, NSError *err)
    {
        returnedErr = err;
        selectedDevice = arr.firstObject;
        [expectation fulfill];
    };
    
    [sdk.cashDrawerManager discoverDevices:extensionUUID completion:completionTerminals];
}

@end
