//
//  StatsTests.swift
//  DemoAcceptSDK
//
//  Created by Fortes, Francisco on 6/26/17.
//  Copyright © 2017 Wirecard. All rights reserved.
//

import Foundation
import XCTest
import Accept

class StatsTestsSwift: XCTestCase, AcceptSDKDelegate
{
    var returnedErr : Error!
    var expectation : XCTestExpectation!
    var sdk : AcceptSDK!
    var loggedUser : WDAcceptMerchantUser!
    
    override func setUp()
    {
        super.setUp()
        self.continueAfterFailure = false
        sdk = AcceptSDK.sharedInstance()
        expectation = self.expectation(description: "Setup")
        weak var welf = self
        sdk.setup(with: .development, username: KUSERNAME, password: KPASSWORD, completion:{( currentUser:WDAcceptMerchantUser? , cashier:WDAcceptMerchantCashier? ,
            error:Error?) in
            
            welf?.sdk.add(self)
            welf?.sdk.setDevMode(true) //Setting dev mode as enabled will write logs in your app's document folder and fill the console log with debug messages - Do not forget to disable it before releasing your app to the public!!
            AcceptSDK.ddSetLogLevel(DDLogLevel.info.rawValue)
            welf?.expectation.fulfill()
        })
        
        self.waitForExpectations(timeout: 25, handler: nil)
    }
    
    override func tearDown()
    {
        super.tearDown()
    }
  
    func testTransactionsStatistics()
    {
         //PART 1: We log-in and request user data
         //--------------------------------------
        expectation = self.expectation(description: "Requesting User Data")
        self.loginAndGetUserData()
        self.waitForExpectations(timeout: 100, handler: nil)
        if (loggedUser == nil || (loggedUser.isKind(of: WDAcceptMerchantUser.self)) == false)
        {
            XCTFail("Error, did not return Merchant User. Are your credentials correct? Try login into the backend through internet browser.")
        }
        
         //PART 2: We request stats from user sales
         //----------------------------------------
        expectation = self.expectation(description: "Requesting Stats")
        self.getSaleStats()
        self.waitForExpectations(timeout: 100, handler: nil)
    }
    
    func loginAndGetUserData()
    {
        loggedUser = nil
        weak var welf = self
        sdk.userManager.currentUser({(merchantUser : WDAcceptMerchantUser?, error: Error?) in
            welf?.loggedUser = merchantUser
            welf?.returnedErr = error
            welf?.expectation.fulfill()
        })
    }
    
    func getSaleStats()
    {
        weak var welf = self
        let query : WDAcceptStatisticsQuery = WDAcceptStatisticsQuery.init()
        query.merchantId = (loggedUser?.merchant?.merchantId)!; //Your Merchant ID
        //Recommendation: check NSDate+Utils implementation for a useful set of functions to handle daily, weekly and monthly intervals
        query.processedFrom = NSDate().firstDateOfWeek() //[[NSDate date] firstDateOfWeek];//from first date of week
        query.processedTo = Date() //till today
        query.status = .completed; // Completed Sales only
        query.period = .day; //This is how the stats data will grouped in the response. You can have it weekly, monthly, etc.
        query.currency = "EUR" // Performed Sales Currency
    
        sdk.saleManager.salesStatistics(query, completion: ({(statistics : Array<WDAcceptSaleStatistics>?, error : Error?) in
            // statistics - list of WDAcceptSaleStatistics objects
            // SaleStatistics has all the details of Sale statistics including
            // - MIN, MAX, AVG amounts
            // - Turnover
            // - Transaction count

            welf?.returnedErr = error
            welf?.expectation.fulfill()
        }))
    }
}
