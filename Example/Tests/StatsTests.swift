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

class StatsTestsSwift: BaseTestsSwift
{

    override func setUp()
    {
        super.setUp()
    }

    func testTransactionsStatistics()
    {
         //PART 1: We log-in and request user data
         //--------------------------------------
        expectation = self.expectation(description: "Requesting User Data")
        self.loginAndGetUserData()
        self.waitForExpectations(timeout: 100, handler: nil)
        if (loggedUser == nil || (loggedUser?.isKind(of: WDAcceptMerchantUser.self)) == false)
        {
            XCTFail("Error, did not return Merchant User. Are your credentials correct? Try login into the backend through internet browser.")
        }
        
         //PART 2: We request stats from user sales
         //----------------------------------------
        expectation = self.expectation(description: "Requesting Stats")
        self.getSaleStats()
        self.waitForExpectations(timeout: 100, handler: nil)
    }
    
    func getSaleStats()
    {
        guard let merchantId = loggedUser?.merchant?.merchantId else
        {
            XCTFail("Something went really wrong - getSaleStats")
            self.expectation.fulfill()
            return
        }
        let query : WDAcceptStatisticsQuery = WDAcceptStatisticsQuery.init()
        query.merchantId = merchantId; //Your Merchant ID
        //Recommendation: check NSDate+Utils implementation for a useful set of functions to handle daily, weekly and monthly intervals
        query.processedFrom = NSDate().firstDateOfWeek() //[[NSDate date] firstDateOfWeek];//from first date of week
        query.processedTo = Date() //till today
        query.status = .completed; // Completed Sales only
        query.period = .day; //This is how the stats data will grouped in the response. You can have it weekly, monthly, etc.
        query.currency = "EUR" // Performed Sales Currency
    
        sdk.saleManager.salesStatistics(query, completion: ({[weak self](statistics : Array<WDAcceptSaleStatistics>?, error : Error?) in
            // statistics - list of WDAcceptSaleStatistics objects
            // SaleStatistics has all the details of Sale statistics including
            // - MIN, MAX, AVG amounts
            // - Turnover
            // - Transaction count

            self?.returnedErr = error
            self?.expectation.fulfill()
        }))
    }
}
