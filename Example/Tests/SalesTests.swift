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

class SalesTestsSwift: XCTestCase, AcceptSDKDelegate
{
    var returnedErr : Error!
    var expectation : XCTestExpectation!
    var sdk : AcceptSDK!
    var loggedUser : WDAcceptMerchantUser?
    var saleResponse : WDAcceptSaleResponse?
    
    override func setUp()
    {
        super.setUp()
        self.continueAfterFailure = false
        sdk = AcceptSDK.sharedInstance()
        expectation = self.expectation(description: "Setup")
        weak var welf = self
        
        sdk.setup(with: .development, username: KUSERNAME, password: KPASSWORD, completion:{( currentUser:WDAcceptMerchantUser? , cashier:WDAcceptMerchantCashier?, error:Error?) in
            
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
    
    func loginAndGetUserData()
    {
        loggedUser = nil
        weak var welf = self
        sdk.userManager.currentUser({(merchantUser : WDAcceptMerchantUser?, error: Error?) in
            NSLog("err:%@",[error])
            welf?.loggedUser = merchantUser
            welf?.returnedErr = error
            welf?.expectation.fulfill()
        })
    }
    
    func getSales()
    {
        let statuses = [NSNumber].init(arrayLiteral: NSNumber.init(value: AcceptSaleState.completed.rawValue), NSNumber.init(value:AcceptSaleState.failed.rawValue), NSNumber.init(value: AcceptSaleState.returned.rawValue), NSNumber.init(value: AcceptSaleState.canceled.rawValue))
        let types = [NSNumber].init(arrayLiteral:NSNumber.init(value: AcceptSaleType.purchase.rawValue))        
        let query : WDAcceptSalesQuery = WDAcceptSalesQuery.init(page: 0, pageSize: 20, orderBy: .createdAt, order: .descending, statuses: statuses, saleTypes: types)
        weak var welf = self
        sdk.saleManager.querySales(query, completion: {(arr : [WDAcceptSaleResponse]?, error: Error?) in
            welf?.saleResponse = arr?.first
            welf?.returnedErr = error
            welf?.expectation.fulfill()
        })
    }
}
