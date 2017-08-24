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

class StarIOTestsSwift: XCTestCase, AcceptSDKDelegate, WDAcceptScanning, WDAcceptPrinting, WDAcceptManagerDelegate
{
    var returnedErr : Error!
    var expectation : XCTestExpectation!
    var sdk : AcceptSDK!
    var userHelper : UserHelper!
    var loggedUser : WDAcceptMerchantUser?
    var resultStatus : AcceptResultStatus?
    var selectedDevice : WDAcceptTerminal?
    var connectionStatus : AcceptExtensionConnectionStatus?
    var printingSuccess : Bool?
    var openingDrawerSuccess : Bool?
    var deviceModel : WDAExtensionTypeUUID!
    
    
    override func setUp()
    {
        super.setUp()
        self.continueAfterFailure = false
        sdk = AcceptSDK.sharedInstance()
        expectation = self.expectation(description: "Setup")
        weak var welf = self
        connectionStatus = .disconnected
        
        sdk.setup(with: .development, username: KUSERNAME, password: KPASSWORD, completion:{( currentUser:WDAcceptMerchantUser? , cashier:WDAcceptMerchantCashier?, error:Error?) in
            
            welf?.sdk.add(self)
            welf?.sdk.setDevMode(true) //Setting dev mode as enabled will write logs in your app's document folder and fill the console log with debug messages - Do not forget to disable it before releasing your app to the public!!
            AcceptSDK.ddSetLogLevel(DDLogLevel.info.rawValue)
            welf?.deviceModel = .WDAMPOPExtensionUUID
            //Under StarIO or StarMicronics you can select two types of hardware, the mPOP (WDAMPOPExtensionUUID) and the regular Star Micronics CB2002 (WDAStarMicronicsExtensionUUID). Both operate in the same way, with the second not having barcode reader built-in.
            welf?.expectation.fulfill()
        })

        self.waitForExpectations(timeout: 25, handler: nil)
    }
    
    override func tearDown()
    {
        super.tearDown()
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
        self.detectDevice()
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
        if (openingDrawerSuccess == nil)
        {
            XCTFail("Device communication failed. Please make the hardware is switched on and paired to yout iOS device settings. If it was paired to other iOS device, please unpair it first.");
        }
        
        //PART 3: Printing receipt
        //--------------------------------------
        expectation = self.expectation(description: "Printing receipt")
        self.printReceipt()
        self.waitForExpectations(timeout: 100, handler: nil)
        if (printingSuccess == nil)
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
    
    func detectDevice()
    {
        weak var welf = self
        sdk.cashDrawerManager.discoverDevices(self.deviceModel, completion: {(arr : [WDAcceptTerminal]?, error : Error?) in
            welf?.selectedDevice = arr?.first
            welf?.returnedErr = error
            welf?.expectation.fulfill()
        })
    }
    
    func openCashDrawer()
    {
        weak var welf = self
        sdk.cashDrawerManager.openCashDrawer(self.selectedDevice!, completion: {(success : Bool?, error : Error?) in
            welf?.openingDrawerSuccess = success
            welf?.returnedErr = error
            welf?.expectation.fulfill()
        })
    }
    
    func printReceipt()
    {
        weak var welf = self        
        let printProgress : PrinterStateUpdate = {(update : AcceptPrinterStateUpdate) in
            print("Print progress is \(update.rawValue)")
        }
        
        let printCompletion : PrintCompletion = {(success : Bool?, error : Error?) in
            welf?.printingSuccess = success
            welf?.returnedErr = error
            welf?.expectation.fulfill()
        }

        let printerConfig : WDAcceptPrinterConfig = WDAcceptPrinterConfig.init(printer:self.selectedDevice!, printJobs:[UIImage].init(arrayLiteral: UIImage.init(named: "fakereceipt")!))
        /*Note that the printer adds borders to the image and it cannot be avoided. Try  not to include
        borders in the picture -- otherwise the image will be scaled down.
        If you wish to use the Default Design receipt you can obtain the SaleResponse from
            a) a saleManager pay:
            b) a saleManager querySales:
        Here we demonstrate the use of saleManager/saleResponse query.
        */

        let statuses = [NSNumber].init(arrayLiteral: NSNumber.init(value: AcceptSaleState.completed.rawValue))
        let types = [NSNumber].init(arrayLiteral:NSNumber.init(value: AcceptSaleType.purchase.rawValue))
        let query : WDAcceptSalesQuery = WDAcceptSalesQuery.init(page: 0, pageSize: 20, orderBy: .createdAt, order: .descending, statuses: statuses, saleTypes: types)
        
        sdk.saleManager.querySales(query, completion: {(arr : [WDAcceptSaleResponse]?, error : Error?) in
            let saleResponse : WDAcceptSaleResponse? = arr?.first //Use the first returned sale for this example
            welf?.returnedErr = error
            if saleResponse != nil && error != nil
            {
                saleResponse?.receipt(true, showReturns: false, format: .uiImage, dpi: .starMicronics, completion: {(receipt : Any?, error : Error?) in
                    //Receipt as per format specified HTML | PDF | UIImage | AcceptReceipt object
                    if (receipt != nil)
                    {
                        printerConfig.printJobs = [Any].init(arrayLiteral: receipt!)
                        welf?.sdk.printerManager.print(printerConfig, progress: printProgress, completion: printCompletion)
                    }
                    else
                    {
                        welf?.expectation.fulfill()
                    }
                })
            }
            else
            {
                welf?.expectation.fulfill()
            }
        })
    }
    
    func device(_ device: WDAcceptTerminal, connectionStatusDidChange status:AcceptExtensionConnectionStatus)
    {
        print("Connection status changed \(status)")
        if (status != .connected)
        {
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
            Set("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLKMNOPQRSTUVWXYZ1234567890+-*=(),.:!_".characters)
        return String(text.characters.filter {okayChars.contains($0) })
    }
    
    func device(_ device: WDAcceptTerminal, dataReceived: Data) //Data received through barcode scanner
    {
        //It is a good practice to remove control characters as scanners have the bad tendency to add garbage at the end
        let barcodeAsText = self.removeSpecialCharsFromString(text: String.init(data: dataReceived, encoding: String.Encoding.utf8)!)
        print("Barcode read with value as string: \(barcodeAsText)")
        self.expectation.fulfill()
    }

}
