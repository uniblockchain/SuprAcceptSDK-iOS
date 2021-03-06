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

class StarIOTestsSwift: BaseTestsSwift, WDAcceptScanning, WDAcceptPrinting, WDAcceptManagerDelegate
{
    var userHelper : UserHelper!
    var printingSuccess : Bool?
    var openingDrawerSuccess, openingDrawerDone  : Bool?
    var scanningSuccess : Bool?
    var deviceModel : WDAExtensionTypeUUID!
    
    override func setUp()
    {
        super.setUp()
        deviceModel = .WDAMPOPExtensionUUID
        self.openingDrawerSuccess = false
        self.openingDrawerDone = false
        self.scanningSuccess = false
        self.scanningSuccess = false
    }

    func testStarMicronics()
    {
        #if arch(i386) || arch(x86_64)
            let file:NSString = (#file as NSString).lastPathComponent as NSString
            NSLog("\n\t\t    [%@ %@] Not runnable on simulator 📱",file.deletingPathExtension , #function);
            return
            
        #endif
        
        //PART 1: We detect paired devices
        //--------------------------------------
        expectation = self.expectation(description: "We detect paired devices")
        self.discoverDevices(deviceModel)
        self.waitForExpectations(timeout: 100, handler: nil)
        if (selectedDevice == nil)
        {
            XCTFail("No device found. Please make the hardware is switched on and paired to yout iOS device settings");
        }
        else
        {
            sdk.scannerManager.add(self, forDevice: selectedDevice!)
            sdk.printerManager.add(self, forDevice: selectedDevice!)
            sdk.cashDrawerManager.add(self, forDevice: selectedDevice!)
        }
        
        //PART 2: We open the cash drawer
        //--------------------------------------
        expectation = self.expectation(description: "Open cash drawer")
        //Open of cash drawer is trigger in delegate method connectionStatusDidChange below, once it is connected
        self.waitForExpectations(timeout: 100, handler: nil)
        if (openingDrawerSuccess == false)
        {
            XCTFail("Device communication failed. Please make the hardware is switched on and paired to yout iOS device settings. If it was paired to other iOS device, please unpair it first.");
        }
        
        //PART 4: Getting a sale
        //--------------------------------------
        expectation = self.expectation(description: "Getting a sale")
        self.gettingSale()
        self.waitForExpectations(timeout: 100, handler: nil)
        if (saleResponse == nil)
        {
            XCTFail("No sale could be reached. Please run cash unit test first, for example.");
        }
        
        //PART 3: Printing receipt
        //--------------------------------------
        expectation = self.expectation(description: "Printing receipt")
        self.printReceipt()
        self.waitForExpectations(timeout: 100, handler: nil)
        if (printingSuccess == false)
        {
            XCTFail("Printing failed. Please make the hardware is switched on and paired to yout iOS device settings. If it was paired to other iOS device, please unpair to it first.");
        }
        
        if (deviceModel == .WDAMPOPExtensionUUID) //StarMicronics CB2002 does not have barcode scanner, so disable this if you are not using mPOP one
        {
            //PART 4: Scanning barcode
            //--------------------------------------
            expectation = self.expectation(description: "Read barcode")
            self.waitForExpectations(timeout: 100, handler: nil)
        }
    }
    
    func openCashDrawer()
    {
        sdk.cashDrawerManager.openCashDrawer(self.selectedDevice!,
                                             completion: {[weak self](success : Bool?, error : Error?) in
                self?.openingDrawerSuccess = success
                self?.returnedErr = error
                self?.expectation.fulfill()
        })
    }
    
    func gettingSale()
    {
        let statuses = [NSNumber].init(arrayLiteral: NSNumber.init(value: AcceptSaleState.completed.rawValue))
        let types = [NSNumber].init(arrayLiteral:NSNumber.init(value: AcceptSaleType.purchase.rawValue))
        let query : WDAcceptSalesQuery = WDAcceptSalesQuery.init(page: 0,
                                                                 pageSize: 20,
                                                                 orderBy: .createdAt,
                                                                 order: .descending,
                                                                 statuses: statuses,
                                                                 saleTypes: types)
        
        sdk.saleManager.querySales(query, completion: {[weak self](arr : [WDAcceptSaleResponse]?, error : Error?) in
            self?.returnedErr = error
            self?.saleResponse = arr?.first //Use the first returned sale for this example
            self?.expectation.fulfill()
        })
    }
    
    func printReceipt()
    {
        guard let receiptImage = UIImage.init(named: "fakereceipt") else
        {
            XCTFail("Something went really wrong - printReceipt")
            self.expectation.fulfill()
            return
        }
        let printProgress : PrinterStateUpdate = {(update : AcceptPrinterStateUpdate) in
            print("Print progress is \(update.rawValue)")
        }
        
        let printCompletion : PrintCompletion = {[weak self](success : Bool?, error : Error?) in
            self?.printingSuccess = success
            self?.returnedErr = error
            self?.expectation.fulfill()
        }

        let printerConfig : WDAcceptPrinterConfig = WDAcceptPrinterConfig.init(printer:self.selectedDevice!,
                                                                               printJobs:[UIImage].init(arrayLiteral: receiptImage))
        /*Note that the printer adds borders to the image and it cannot be avoided. Try  not to include
        borders in the picture -- otherwise the image will be scaled down.
        If you wish to use the Default Design receipt you can obtain the SaleResponse from
            a) a saleManager pay:
            b) a saleManager querySales:
        Here we demonstrate the use of saleManager/saleResponse query.
        NOTE: Star Micronics devices only accept receipts in the format UIImage
        */

        self.saleResponse?.receipt(true,
                              showReturns: false,
                              format: .uiImage,
            dpi: .starMicronics,
            completion: {[weak self](receipt : Any?, error : Error?) in
                self?.returnedErr = error
                //Receipt as per format specified HTML | PDF | UIImage | AcceptReceipt object
                if (receipt != nil)
                {
                    printerConfig.printJobs = [Any].init(arrayLiteral: receipt!)
                    self?.sdk.printerManager.print(printerConfig,
                                                   progress: printProgress,
                                                   completion: printCompletion)
                }
                else
                {
                    self?.expectation.fulfill()
                }
        })
    }
    
    func device(_ device: WDAcceptTerminal, connectionStatusDidChange status:AcceptExtensionConnectionStatus)
    {
        print("Connection status changed \(status)")
        if (status == .connected && self.openingDrawerDone == false)
        {
            self.openingDrawerDone = true
            self.openCashDrawer()
        }
    }
    
    func device(_ device: WDAcceptTerminal, batteryLevelDidChange batteryLevel: Int)
    {
        //StarIO devices do not inform about battery levels
    }
    
    func device(_ device: WDAcceptTerminal, paperStatusUpdated status: AcceptPrinterPaperStatus)
    {
        print("The level of paper in your printer is \(status)")
    }
    
    func removeSpecialCharsFromString(text: String) -> String
    {
        let okayChars : Set<Character> =
            Set("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLKMNOPQRSTUVWXYZ1234567890+-*=(),.:!_")
        return String(text.filter {okayChars.contains($0) })
    }
    
    func device(_ device: WDAcceptTerminal, barcodeReceived: String, symbology: AcceptBarcodeSymbology) //Data received through barcode scanner
    {
        print("Barcode read with value as string: \(barcodeReceived)")
        
        if self.scanningSuccess == false {
            self.scanningSuccess = true
            self.expectation.fulfill()
        }
    }

}
