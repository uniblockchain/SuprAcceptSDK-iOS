//
//  StatsTests.swift
//  DemoAcceptSDK
//
//  Created by Fortes, Francisco on 7/25/17.
//  Copyright © 2017 Wirecard. All rights reserved.
//

import Foundation
import XCTest
import Accept

class DatecsPrinterTestsSwift: XCTestCase, AcceptSDKDelegate, WDAcceptPrinting, WDAcceptManagerDelegate
{
    var returnedErr : Error!
    var expectation : XCTestExpectation!
    var sdk : AcceptSDK!
    var loggedUser : WDAcceptMerchantUser?
    var resultStatus : AcceptResultStatus?
    var selectedDevice : WDAcceptTerminal?
    var connectionStatus : AcceptExtensionConnectionStatus?
    var printingSuccess : Bool?
    var saleResponse : WDAcceptSaleResponse?
    var receiptData : WDAcceptReceiptData?
    var datecsReceipt : WDAcceptReceipt?
    
    override func setUp()
    {
        super.setUp()
        self.continueAfterFailure = false
        sdk = AcceptSDK.sharedInstance()
        expectation = self.expectation(description: "Setup")
        weak var welf = self
        connectionStatus = .disconnected
        
        sdk.setup(with: .publicTest, username: KUSERNAME, password: KPASSWORD, completion:{( currentUser:WDAcceptMerchantUser? , cashier:WDAcceptMerchantCashier?, error:Error?) in
            
            welf?.sdk.add(self)
            welf?.sdk.setDevMode(true) //Setting dev mode as enabled will write logs in your app's document folder and fill the console log with debug messages - Do not forget to disable it before releasing your app to the public!!
            AcceptSDK.ddSetLogLevel(DDLogLevel.info.rawValue)
            //Under StarIO or StarMicronics you can select two types of hardware, the mPOP (WDAMPOPExtensionUUID) and the regular Star Micronics CB2002 (WDAStarMicronicsExtensionUUID). Both operate in the same way, with the second not having barcode reader built-in.
            welf?.expectation.fulfill()
        })

        self.waitForExpectations(timeout: 25, handler: nil)
    }
    
    override func tearDown()
    {
        super.tearDown()
    }
  
    
    func testDatecsPrinter()
    {
        #if arch(i386) || arch(x86_64)
            let file:NSString = (#file as NSString).lastPathComponent as NSString
            NSLog("\n\t\t    [%@ %@] Not runnable on simulator 📱",file.deletingPathExtension , #function);
            return
            
        #endif
        
        //PART 1: We log-in and request user data
        //--------------------------------------
        expectation = self.expectation(description: "Requesting User Data")
        self.loginAndGetUserData()
        self.waitForExpectations(timeout: 100, handler: nil)
        if (loggedUser == nil || (loggedUser?.isKind(of: WDAcceptMerchantUser.self)) == false)
        {
            XCTFail("Error, did not return Merchant User. Are your credentials correct? Try login into the backend through internet browser.")
        }
        
        //PART 2: We request a sale for getting a receipt
        //-----------------------------------------------
        expectation = self.expectation(description: "Getting sale receipt")
        self.getSaleReceipt()
        self.waitForExpectations(timeout: 100, handler: nil)
        if self.receiptData == nil {
            XCTFail("Error getting a complete sale. Please create some test (ie. run CashTest). Otherwise, debug and check the returned error")
        }
        
        //PART 3: We detect paired devices
        //--------------------------------------
        expectation = self.expectation(description: "We detect paired devices")
        self.detectDevice()
        self.waitForExpectations(timeout: 100, handler: nil)
        if (selectedDevice == nil)
        {
            XCTFail("Error detecting printer. Make sure is charger, switched on and properly paired in your iOS device settings");
        }
        else
        {
            sdk.printerManager.add(self, forDevice: selectedDevice!)
        }
        
        //PART 4: We print the receipt date
        //--------------------------------------
        expectation = self.expectation(description: "Printing receipt")
        self.printReceipt()
        self.waitForExpectations(timeout: 100, handler: nil)
        if (printingSuccess == nil)
        {
            XCTFail("Printing failed. Please make the hardware is switched on and paired to yout iOS device settings. If it was paired to other iOS device, please unpair to it first.");
        }
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
    
    func getSaleReceipt()
    {
        let query : WDAcceptSalesQuery = WDAcceptSalesQuery.init()
        query.saleId = SaleHelper.sharedInstance().saleIdSaved()
        weak var welf = self
        sdk.saleManager.querySales(query, completion: {(arr : [WDAcceptSaleResponse]?, error: Error?) in
            welf?.saleResponse = arr?.first
            if ((arr?.first) != nil)
            {
                welf?.receiptData = welf?.saleResponse?.getAcceptReceiptData()
                welf?.saleResponse?.receipt(true, showReturns: false, format: .datecs, dpi: AcceptPrintDpi.default, completion: {(receipt : Any?, error : Error?) in
                    welf?.datecsReceipt = receipt as? WDAcceptReceipt
                    welf?.expectation.fulfill()
                })
            }
            else
            {
                welf?.expectation.fulfill()
            }
            welf?.returnedErr = error
        })
    }
    
    func detectDevice()
    {
        weak var welf = self
        sdk.printerManager.discoverDevices(.WDADatecsPrinterExtensionUUID, completion: {(arr : [WDAcceptTerminal]?, error : Error?) in
            welf?.selectedDevice = arr?.first
            welf?.returnedErr = error
            welf?.expectation.fulfill()
        })
    }
    
    func printReceipt()
    {
        weak var welf = self
        let completion : PrintCompletion = {(printStatusOK : Bool?, error : Error?) in
            welf?.printingSuccess = error == nil && printStatusOK == true
            welf?.returnedErr = error
            welf?.expectation.fulfill()
        }
        
        let progress : PrinterStateUpdate = {(update : AcceptPrinterStateUpdate?) in
            print("Print progress is: \(String(describing: update))")
        }
        //You can just send an image to the printer using printerConfig, but due to paper size and capabilities of Datecs printer, is always faster and more efficient to send receipt data and let the SDK build a text receipt. Image receipt are slow and even consume resources for the blank areas.
        
        let printerConfig : WDAcceptPrinterConfig = WDAcceptPrinterConfig.init(printer: self.selectedDevice!, printJobs: [self.datecsReceipt!])
        
        //Alternatively, you can print a sales report, with catalogue categories, category items, and statistics on discounts, taxes and more, filling the parameters you need in:
        //printerConfig.report = ...
        //See declaration of class WDAcceptZReport for the available parameters
        sdk.printerManager.print(printerConfig, progress: progress, completion: completion)
        
    }
    
    func device(_ device: WDAcceptTerminal, connectionStatusDidChange status:AcceptExtensionConnectionStatus)
    {
        print("Connection status changed \(status)")
    }
    
    func device(_ device: WDAcceptTerminal, batteryLevelDidChange batteryLevel: Int)
    {
        //StarIO devices do not inform about battery levels
    }
    
}
