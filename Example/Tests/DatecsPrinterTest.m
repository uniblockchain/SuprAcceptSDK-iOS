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

@interface DatecsPrinterTestsObjC : XCTestCase <AcceptSDKDelegate>
{
    __block NSError *returnedErr;
    __weak XCTestExpectation *expectation;
    AcceptSDK *sdk;
    UserHelper *userHelper;
    __block WDAcceptMerchantUser *loggedUser;
    __block AcceptResultStatus resultStatus;
    __block WDAcceptReceiptData *receiptData;
    __block WDAcceptReceipt *datecsReceipt;
    __block WDAcceptTerminal *selectedPrinter;
    __block BOOL printingSuccess;
}

@end

@implementation DatecsPrinterTestsObjC

- (void)setUp
{
    [super setUp];
    self.continueAfterFailure = NO;
    sdk = [AcceptSDK sharedInstance];
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

-(void)testDatecsPrinter
{
    #if TARGET_OS_SIMULATOR
        NSLog(@"\n\t\t   %s Not runnable on simulator 📱",__PRETTY_FUNCTION__);
        return;
    
    #endif
    //PART 1: We log-in and request user data
    //--------------------------------------
    expectation = [self expectationWithDescription:@"Requesting User Data"];
    [self loginAndGetUserData];
    [self waitForExpectationsWithTimeout:100 handler:nil];
    if (!loggedUser || ![loggedUser isKindOfClass:[WDAcceptMerchantUser class]])
    {
        XCTFail(@"Error, did not return Merchant User. Are your credentials correct? Try login into the backend through internet browser.");
    }
    
    
    //PART 2: We request a sale for getting a receipt
    //-----------------------------------------------
    expectation = [self expectationWithDescription:@"Getting sale receipt"];
    [self getSaleReceipt];
    [self waitForExpectationsWithTimeout:100 handler:nil];
    if (!receiptData)
    {
        XCTFail(@"Error getting a complete sale. Please create some test (ie. run CashTest). Otherwise, debug and check the returned error");
    }
    
    
    //PART 3: We detect the printer
    //---------------------------------
    expectation = [self expectationWithDescription:@"Detecting printer"];
    [self detectPrinter];
    [self waitForExpectationsWithTimeout:100 handler:nil];
    if (!selectedPrinter)
    {
        XCTFail(@"Error detecting printer. Make sure is charger, switched on and properly paired in your iOS device settings");
    }
    
    //PART 4: We print the receipt date
    //---------------------------------
    expectation = [self expectationWithDescription:@"Printing sale receipt"];
    [self printReceipt];
    [self waitForExpectationsWithTimeout:100 handler:nil];
    if (!printingSuccess)
    {
        XCTFail(@"Error Printing. Please, debug and check the returned error");
    }

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

-(void)getSaleReceipt
{
    WDAcceptSalesQuery *query = [[WDAcceptSalesQuery alloc] init];
    query.saleId = [[[SaleHelper sharedInstance] saleIdSaved] length]? [[SaleHelper sharedInstance] saleIdSaved] : @"No id, you won't get a sale as response"; //Do never leave this empty: you will requests all sales to backend, with no page size limit, and it will take quite long and the response will be up to 1000 items.

    [[sdk saleManager] querySales:query completion:^(NSArray<WDAcceptSaleResponse *> * arr, NSError * error)
     {
         WDAcceptSaleResponse *saleResponse = [arr firstObject];
         if (saleResponse)
         {
             receiptData = [saleResponse getAcceptReceiptData];
             //alternatively use the Default Designed receipt for Datecs
             [saleResponse receipt:YES //Is the receipt for cardholder use
                       showReturns:NO //Should the receipt contain returns ?
                            format:AcceptPrintFormatDatecs //The receipt format is AcceptReceipt object for Datecs
                               dpi:AcceptPrintDpiDefault //The dots per width is set to Default - valid for Datecs or AirPrint
                        completion:^(id  _Nullable receipt, NSError * _Nullable error) {
                            //Receipt as per format specified HTML | PDF | UIImage | AcceptReceipt object
                            datecsReceipt = receipt;
                             [expectation fulfill];
                        }];
         }
         else{
              [expectation fulfill];
         }
         returnedErr = error;

     }];
}

-(void)detectPrinter
{
    DeviceDiscoveryCompletion completionTerminals = ^(NSArray *arr, NSError *err)
    {
        returnedErr = err;
        selectedPrinter = arr.firstObject;
        [expectation fulfill];
    };
    
    [sdk.printerManager discoverDevices:WDADatecsPrinterExtensionUUID completion:completionTerminals];
}

-(void)printReceipt
{
    
    //End of printing process
    PrintCompletion completion = ^(BOOL printStatusOK, NSError* _Nullable printError){
        //printStatusOK is true if printing ended with OK status
        printingSuccess = (!printError && printStatusOK);
        returnedErr = printError;
        [expectation fulfill];
    };
    
    PrinterStateUpdate progress = ^(AcceptPrinterStateUpdate update)
    {
        //printProgress - print progress Initialisation | Printing | Finished
        NSLog(@"Print progress is: %ld", (long)update);
    };
    
    
    WDAcceptPrinterConfig *printerConfig = [[WDAcceptPrinterConfig alloc] initWithPrinter:selectedPrinter printJobs:@[datecsReceipt]];
    //You can just send an image to the printer using printerConfig, but due to paper size and capabilities of Datecs printer, is always faster and more efficient to send receipt data and let the SDK build a text receipt. Image receipt are slow and even consume resources for the blank areas.

    //Alternatively, you can print a sales report, with catalogue categories, category items, and statistics on discounts, taxes and more, filling the parameters you need in:
    //printerConfig.report = ...
    //See declaration of class WDAcceptZReport for the available parameters
    
    [sdk.printerManager print:printerConfig progress:progress completion:completion];
}

@end
