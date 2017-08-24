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

@interface SalesTestsObjC : XCTestCase <AcceptSDKDelegate>
{
    __block NSError *returnedErr;
    __weak XCTestExpectation *expectation;
    AcceptSDK *sdk;
    __block WDAcceptMerchantUser *loggedUser;
    __block WDAcceptSaleResponse *saleResponse;
}

@end

@implementation SalesTestsObjC

#pragma mark - Helpers

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

- (void)tearDown
{
    [super tearDown];
}


-(void)testSales
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
    
    
    //PART 2: We request sales from current user
    //----------------------------------------
    expectation = [self expectationWithDescription:@"Requesting Sales"];
    [self getSales];
    [self waitForExpectationsWithTimeout:100 handler:nil];
    if (!saleResponse)
    {
        XCTFail(@"Error getting a complete sale. Please create some test (ie. run CashTest). Otherwise, debug and check the returned error");
    }
    else
    {
        //We save one valid sale id for other tests cases such as Printer ones
        [[SaleHelper sharedInstance] saleToSaveIdFrom:saleResponse];
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

-(void)getSales
{
    WDAcceptSalesQuery *query = [[WDAcceptSalesQuery alloc] init];
    query.page =  0; //Increase this if you want to do dynamic paging in your UI
    query.pageSize = 20; //Each sale includes a lot of data, so paging with small pageSizes is recommended
    query.orderBy = AcceptSaleQueryOrderByCreatedAt; //You can also sort by amount using AcceptTransactionsQueryOrderByAmount
    query.orderSort = AcceptQuerySortDescending;//Can be AcceptTransactionsQuerySortAscending
    query.statuses = @[@(AcceptSaleStateCompleted), @(AcceptSaleStateFailed), @(AcceptSaleStateReturned), @(AcceptSaleStateCanceled)];//You can define more or less statuses for the query, depending on your needs.
    //You can use a receiptId provided by backend in query.receiptId if you have one
    [[sdk saleManager] querySales:query completion:^(NSArray<WDAcceptSaleResponse *> * arr, NSError * error)
    {
        saleResponse = [arr firstObject];
        returnedErr = error;
        [expectation fulfill];
    }];
}


@end
