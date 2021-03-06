//
//  TestDomainDataServices.m
//  acceptSDK
//
//  Created by Danko, Radoslav on 17/10/15.
//  Copyright © 2015 Wirecard. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <libextobjc/EXTScope.h>
#import "UserHelper.h"
#import "SaleHelper.h"
#import "DDLog.h"
#import "TestUtils.h"
#import "BaseTests.h"


@interface SpireTestsObjc : BaseTestsObcj
{
    __block AcceptUpdateConfigurationStatus configCompletionStatus;
}

@end

@implementation SpireTestsObjc


/*
 
 IMPORTANT NOTE: 
 -This test requires an actual iOS device (not simulator).
 -You have to have a Spire terminal paired through your iOS device settings.
 -Your terminal must have been provided by Wirecard, and be turned on.
 -If your backend settings include cash management with mandatory cash registers, you will need to run CashTests first (to have valid ids)
*/

- (void)setUp
{
    [super setUp];
}

-(void)testSpire
{
#if TARGET_OS_SIMULATOR
    NSLog(@"\n\t\t   %s Not runnable on simulator 📱",__PRETTY_FUNCTION__);
    return;
    
#endif
    
    //PART 1: We log-in and request user data
    //--------------------------------------
    expectation = [self expectationWithDescription:@"Requesting User Data"];
    [self loginAndGetUserData];
    [self waitForExpectationsWithTimeout:300 handler:nil];
    if (!loggedUser || ![loggedUser isKindOfClass:[WDAcceptMerchantUser class]])
    {
        XCTFail(@"Error, did not return Merchant User. Are your credentials correct? Try login into the backend through internet browser.");
    }
    else
    {
        [[UserHelper sharedInstance] setUser:loggedUser];
    }
    
    //PART 2: We discover Spire terminals
    //paired to your iOS device.
    //--------------------------------------
    expectation = [self expectationWithDescription:@"Discovering devices"];
    [self discoverDevices:WDAPosMateExtensionUUID];
    [self waitForExpectationsWithTimeout:300 handler:nil];
    if (!selectedDevice || ![selectedDevice isKindOfClass:[WDAcceptTerminal class]])
    {
        XCTFail(@"No paired terminal found. Make sure your terminal is paired in your iOS device settings and that the terminal is in stand-by mode (ie. by switching off and then on and waiting until the screen lights off).");
    }

    //PART 3: We check for updates on the terminal
    //---------------------------------------------
    expectation = [self expectationWithDescription:@"Checking for terminal update"];
    [self checkingForTerminalConfigUpdates];
    [self waitForExpectationsWithTimeout:300 handler:nil];
    if (configCompletionStatus == AcceptUpdateConfigurationStatusFailure)
    {
        XCTFail(@"Error when updating the terminal. Make sure your terminal is paired in your iOS device settings and that the terminal is in stand-by mode (ie. by switching off and then on and waiting until the screen lights off).");
    }
    
    //PART 4: We do a card sale using Spire terminal
    //---------------------------------------------
    expectation = [self expectationWithDescription:@"Card sale"];
    [self doCardPayment];
    [self waitForExpectationsWithTimeout:300 handler:nil];
    if (!saleResponse)
    {
        XCTFail(@"Sale did not succeed. Make sure your terminal is paired in your iOS device settings and that the terminal is in stand-by mode (ie. by switching off and then on and waiting until the screen lights off).");
    }
    else
    {
        //We save one valid sale id for other tests cases such as Printer ones
        [[SaleHelper sharedInstance] saleToSaveIdFrom:saleResponse];
    }
    
    //PART 5: We refund the sale we just did
    //(for testing purposes; this is important
    //if you develop using an actual credit card)
    //-------------------------------------------
    expectation = [self expectationWithDescription:@"Refund sale"];
    [self refundTransaction];
    [self waitForExpectationsWithTimeout:300 handler:nil];
    if (!saleResponse || saleResponse.status != AcceptSaleStateReturned)
    {
        XCTFail(@"Sale did cancel. Make sure your terminal is paired in your iOS device settings and that the terminal is in stand-by mode (ie. by switching off and then on and waiting until the screen lights off).");
    }
}

-(void)checkingForTerminalConfigUpdates
{
    UpdateTerminalCompletion completionUpdate = ^(AcceptUpdateConfigurationStatus updStatus, NSError *updError)
    {
        //Note that completion here will happen when:
        // 1- The update has been completed, but also the terminal has fully restarted and entered stand-by (this may take a couple of minutes in the case of firmware)
        // 2- There was no response from terminal (something went wrong) for several seconds, meaning update failed.
        returnedErr = updError;
        configCompletionStatus = updStatus;
        [expectation fulfill];
    };
    
    UpdateConfigurationProgress progress = ^(AcceptUpdateConfigurationProgressUpdate progressUpdate)
    {
        NSLog(@"Terminal update progress: %ld",(long)progressUpdate);
    };
    
    //Note: You may update the firmware too using AcceptTerminalUpdateTypeFirmware
    //Note: The accept SDK will keep track of what version was previously installed, and decide if an update is required by comparing with the latest in backend.
    //This means, the first time you run this test, the configuration will be updated on the terminal. A second time will tell you "AcceptUpdateConfigurationStatusUnnecessary"
    //To force the actual update again you will have to remove the demo app from your iOS device and re-run the test.
     [sdk.terminalManager update:selectedDevice
                      updateType:AcceptTerminalUpdateTypeMaskConfiguration
                        progress:progress completion:completionUpdate];
}

-(void)doCardPayment
{
    WDAcceptPaymentConfig *paymentConfiguration = [WDAcceptPaymentConfig new];
    aSale = [[SaleHelper sharedInstance] newSale];
    [aSale addSaleItem:[NSDecimalNumber decimalNumberWithString:@"2.5"]
              quantity:5
               taxRate:[[UserHelper sharedInstance] preferredSaleItemTax]
       itemDescription:@"Red Apple"
             productId:@"dummyId1"];
    [aSale addSaleItem:[NSDecimalNumber decimalNumberWithString:@"1.34"]
              quantity:2
               taxRate:[[UserHelper sharedInstance] preferredSaleItemTax]
       itemDescription:@"Pineapple"
             productId:@"dummyId2"];
    //You can add a service charge to the whole basket -- though this is totally optional
    [aSale addServiceCharge:[[UserHelper sharedInstance] serviceChargeRate]
                    taxRate:[[UserHelper sharedInstance] serviceChargeTax]];
    //You can add a tip of any value you want. Notice that backend validate taxes, so their values should match the ones your merchan has defined in setup.
    [aSale addGratuity:[NSDecimalNumber decimalNumberWithString:@"1"]
               taxRate:[[UserHelper sharedInstance] tipTax]];
    //You can add a discount for the whole basket when productId is nil, or per productId otherwise
    [aSale addDiscount:[NSDecimalNumber decimalNumberWithString:@"6"]
             productId:nil];
    paymentConfiguration.sale = aSale;
    paymentConfiguration.sale.cashRegisterId = [[UserHelper sharedInstance] selectedCashRegisterId]; //Note: if your backend settings have cash mgmt enabled in backend, you will need to run cash tests first to get this value as well as shiftId below
    paymentConfiguration.sale.shiftId = [[UserHelper sharedInstance] lastShiftId];
    [paymentConfiguration.sale resetPayments];
    [paymentConfiguration.sale addCardPayment:paymentConfiguration.sale.totalToPay
                                     terminal:selectedDevice];
    
    [sdk.terminalManager setActive:selectedDevice completion:
    ^{
        [[sdk saleManager] pay:paymentConfiguration delegate:_paymentHandler];
    }];
}

-(void)refundTransaction
{
    WDAcceptSaleRequest *saleToBeRefunded = [saleResponse saleReturn];
    saleToBeRefunded.cashRegisterId = [[UserHelper sharedInstance] selectedCashRegisterId];
    saleToBeRefunded.cashierId = saleResponse.cashierId;
    saleToBeRefunded.customerId = saleResponse.customerId;
    //This is an example of full refund: all items are refunded, EXCEPT SERVICE CHARGE
    [saleToBeRefunded removeServiceCharge];
    
     //For partial refund, see CashTests
    [saleToBeRefunded addCardPayment:[saleToBeRefunded totalToPay] terminal:[WDAcceptTerminal new]];
    
    saleResponse = nil;
    
    [[sdk saleManager] refundSale:saleToBeRefunded message:@"Refunded in demo app for testing reasons" completion:^(WDAcceptSaleResponse *acceptSale, NSError *error)
     {
         returnedErr = error;
         saleResponse = acceptSale;
         [expectation fulfill];
     }];
}

@end
