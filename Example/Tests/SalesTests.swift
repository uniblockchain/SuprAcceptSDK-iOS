//
//  UserTestsSwift.swift
//  DemoAcceptSDK
//
//  Created by Fortes, Francisco on 7/25/17.
//  Copyright © 2017 Wirecard. All rights reserved.
//

import Foundation
import XCTest
import Accept

class SalesTestsSwift: BaseTestsSwift
{
    override func setUp()
    {
        super.setUp()
    }
    func testSales()
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
        
        //PART 2: We request sales from current user
        //----------------------------------------
        expectation = self.expectation(description: "Requesting Sales")
        self.getSales()
        self.waitForExpectations(timeout: 100, handler: nil)
        if (self.saleResponse == nil)
        {
            XCTFail("Error getting a complete sale. Please create some test (ie. run CashTest). Otherwise, debug and check the returned error.")
        }
        else
        {
            SaleHelper.sharedInstance().saleToSaveId(from: self.saleResponse)
        }
    }
    
    func getSales()
    {
        let statuses = [NSNumber].init(arrayLiteral: NSNumber.init(value: AcceptSaleState.completed.rawValue),
                                       NSNumber.init(value:AcceptSaleState.failed.rawValue),
                                       NSNumber.init(value: AcceptSaleState.returned.rawValue),
                                       NSNumber.init(value: AcceptSaleState.canceled.rawValue))
        let types = [NSNumber].init(arrayLiteral:NSNumber.init(value: AcceptSaleType.purchase.rawValue))        
        let query : WDAcceptSalesQuery = WDAcceptSalesQuery.init(page: 0,
                                                                 pageSize: 20,
                                                                 orderBy: .createdAt,
                                                                 order: .descending,
                                                                 statuses: statuses,
                                                                 saleTypes: types)
        sdk.saleManager.querySales(query, completion: {[weak self](arr : [WDAcceptSaleResponse]?, error: Error?) in
            self?.saleResponse = arr?.first
            self?.returnedErr = error
            self?.expectation.fulfill()
        })
    }
}
