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
#import "DDLog.h"

@interface StatsTestsObjC : XCTestCase <AcceptSDKDelegate>
{
    __block NSError *returnedErr;
    __weak XCTestExpectation *expectation;
    AcceptSDK *sdk;
    WDAcceptMerchantUser *loggedUser;
}

@end

@implementation StatsTestsObjC

- (void)setUp
{
    [super setUp];
    self.continueAfterFailure = NO;
    sdk = [AcceptSDK sharedInstance];
    expectation = [self expectationWithDescription:@"Setup"];
    [sdk setupWithEnvironment:AcceptEnvironmentPublicTest username:KUSERNAME password:KPASSWORD completion:^(WDAcceptMerchantUser * _Nullable currentUser, WDAcceptMerchantCashier * _Nullable cashier, NSError * _Nullable error) {
        [sdk addDelegate:self];
        [sdk setDevMode:YES]; //Setting dev mode as enabled will write logs in your app's document folder and fill the console log with debug messages - Do not forget to disable it before releasing your app to the public!!
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


-(void)testTransactionsStatistics
{
    //PART 1: We log-in and request user data
    //--------------------------------------
    expectation = [self expectationWithDescription:@"Requesting User Data"];
    [self loginAndGetUserData];
    [self waitForExpectationsWithTimeout:100 handler:nil];
    if (!loggedUser || ![loggedUser isKindOfClass:[WDAcceptMerchantUser class]])
    {
        XCTFail(@"Error, did not return Merchant User. Are your credentials correct? Try login into the backend through internet browser.");
    }

    
    //PART 2: We request stats from user sales
    //----------------------------------------
    expectation = [self expectationWithDescription:@"Requesting Stats"];
    [self getSaleStats];
    [self waitForExpectationsWithTimeout:100 handler:nil];
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

-(void)getSaleStats
{
    
    // End of Sale Statistics process
    SaleStatisticsCompletion completion = ^(NSArray  <WDAcceptSaleStatistics *>* _Nullable statistics, NSError* _Nullable error){
        // statistics - list of WDAcceptSaleStatistics objects
        // SaleStatistics has all the details of Sale statistics including
        // - MIN, MAX, AVG amounts
        // - Turnover
        // - Transaction count
        returnedErr = error;
        //Check the value returned as results, including max, min, turnover, etc per time units, for you to show by text or barchart/piechart graphics.
        [expectation fulfill];
    };
    
    // Query parameters such as filters start/end Sale dates, Sale status and reporting Period
    WDAcceptStatisticsQuery *query = [WDAcceptStatisticsQuery new];
    query.merchantId = loggedUser.merchant.merchantId; //Your Merchant ID
    //Recommendation: check NSDate+Utils implementation for a useful set of functions to handle daily, weekly and monthly intervals
    query.processedFrom = [[NSDate date] firstDateOfWeek];//from first date of week
    query.processedTo = [NSDate date]; //till today
    query.status = AcceptStatisticStatusCompleted; // Completed Sales only
    query.period = AcceptStatisticPeriodDay; //This is how the stats data will grouped in the response. You can have it weekly, monthly, etc.
    query.currency = @"EUR"; // Performed Sales Currency

    // Obtain Sale statistics
    [sdk.saleManager salesStatistics:query // Sale statistics query parameters
                          completion:completion]; // End of Sale Statistics Query process
    
}

@end
