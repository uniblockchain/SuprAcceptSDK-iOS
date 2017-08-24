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

class BaseTestsSwift: XCTestCase, AcceptSDKDelegate
{
    var returnedErr : Error!
    var expectation : XCTestExpectation!
    var sdk : AcceptSDK!
    var loggedUser : WDAcceptMerchantUser?
    var cashRegister : WDAcceptCashRegister?
    var lastShift : WDAcceptCashShift?
    var aSale : WDAcceptSaleRequest!
    var saleResponse : WDAcceptSaleResponse?
    var cashOperationSucceed : Bool?
    var resultStatus : AcceptResultStatus?
    var successfulDownload : Bool?
    var selectedDevice : WDAcceptTerminal?
    var connectionStatus : AcceptExtensionConnectionStatus?
    
    override func setUp()
    {
        super.setUp()
        self.continueAfterFailure = false
        sdk = AcceptSDK.sharedInstance()
        expectation = self.expectation(description: "Setup")
        
        sdk.setup(with: .publicTest,
                  username: KUSERNAME,
                  password: KPASSWORD,
                  completion:{[weak self]( currentUser:WDAcceptMerchantUser? , cashier:WDAcceptMerchantCashier?, error:Error?) in
            
            self?.sdk.add(self!)
            self?.sdk.setDevMode(true) //Setting dev mode as enabled will write logs in your app's document folder and fill the console log with debug messages - Do not forget to disable it before releasing your app to the public!!
            AcceptSDK.ddSetLogLevel(DDLogLevel.info.rawValue)
            self?.expectation.fulfill()
        })
        
        self.waitForExpectations(timeout: 25, handler: nil)
    }
    
    override func tearDown()
    {
        super.tearDown()
    }
  
    
    func loginAndGetUserData()
    {
        loggedUser = nil
        sdk.userManager.currentUser({[weak self](merchantUser : WDAcceptMerchantUser?, error: Error?) in
            NSLog("err:%@",[error])
            self?.loggedUser = merchantUser
            self?.returnedErr = error
            self?.expectation.fulfill()
        })
    }
    
    func discoverDevices(_ extensionUUID: WDAExtensionTypeUUID)
    {
        sdk.printerManager.discoverDevices(extensionUUID,
                                           completion: {[weak self](arr : [WDAcceptTerminal]?, error : Error?) in
            self?.selectedDevice = arr?.first
            self?.returnedErr = error
            self?.expectation.fulfill()
        })
    }
}
