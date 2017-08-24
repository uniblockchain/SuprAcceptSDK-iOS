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

class DatecsPrinterTestsSwift: BaseTestsSwift, WDAcceptPrinting, WDAcceptManagerDelegate
{
    var printingSuccess : Bool?
    var receiptData : WDAcceptReceiptData?
    var datecsReceipt : WDAcceptReceipt?
    
    override func setUp()
    {
        super.setUp()
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
        self.waitForExpectations(timeout: 100,
                                 handler: nil)
        if self.receiptData == nil {
            XCTFail("Error getting a complete sale. Please create some test (ie. run CashTest). Otherwise, debug and check the returned error")
        }
        
        //PART 3: We detect paired devices
        //--------------------------------------
        expectation = self.expectation(description: "We detect paired devices")
        self.discoverDevices(.WDADatecsPrinterExtensionUUID)
        self.waitForExpectations(timeout: 100,
                                 handler: nil)
        if (selectedDevice == nil)
        {
            XCTFail("Error detecting printer. Make sure is charger, switched on and properly paired in your iOS device settings");
        }
        else
        {
            sdk.printerManager.add(self,
                                   forDevice: selectedDevice!)
        }
        
        //PART 4: We print the receipt date
        //--------------------------------------
        expectation = self.expectation(description: "Printing receipt")
        self.printReceipt()
        self.waitForExpectations(timeout: 100,
                                 handler: nil)
        if (printingSuccess == nil)
        {
            XCTFail("Printing failed. Please make the hardware is switched on and paired to yout iOS device settings. If it was paired to other iOS device, please unpair to it first.");
        }
    }
    
    func getSaleReceipt()
    {
        let query : WDAcceptSalesQuery = WDAcceptSalesQuery.init()
        query.saleId = SaleHelper.sharedInstance().saleIdSaved()
        sdk.saleManager.querySales(query,
                                   completion: {[weak self](arr : [WDAcceptSaleResponse]?, error: Error?) in
            self?.saleResponse = arr?.first
            if ((arr?.first) != nil)
            {
                self?.receiptData = self?.saleResponse?.getAcceptReceiptData()
                self?.saleResponse?.receipt(true,
                                            showReturns: false,
                                            format: .datecs,
                                            dpi: AcceptPrintDpi.default,
                                            completion: {(receipt : Any?, error : Error?) in
                    self?.datecsReceipt = receipt as? WDAcceptReceipt
                    self?.expectation.fulfill()
                })
            }
            else
            {
                self?.expectation.fulfill()
            }
            self?.returnedErr = error
        })
    }
    
    func printReceipt()
    {
        let completion : PrintCompletion = {[weak self](printStatusOK : Bool?, error : Error?) in
            self?.printingSuccess = error == nil && printStatusOK == true
            self?.returnedErr = error
            self?.expectation.fulfill()
        }
        
        let progress : PrinterStateUpdate = {(update : AcceptPrinterStateUpdate?) in
            print("Print progress is: \(String(describing: update))")
        }
        //You can just send an image to the printer using printerConfig, but due to paper size and capabilities of Datecs printer, is always faster and more efficient to send receipt data and let the SDK build a text receipt. Image receipt are slow and even consume resources for the blank areas.
        
        let printerConfig : WDAcceptPrinterConfig = WDAcceptPrinterConfig.init(printer: self.selectedDevice!,
                                                                               printJobs: [self.datecsReceipt!])
        
        //Alternatively, you can print a sales report, with catalogue categories, category items, and statistics on discounts, taxes and more, filling the parameters you need in:
        //printerConfig.report = ...
        //See declaration of class WDAcceptZReport for the available parameters
        sdk.printerManager.print(printerConfig,
                                 progress: progress,
                                 completion: completion)
        
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
