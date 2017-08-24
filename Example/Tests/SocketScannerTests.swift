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

class SocketScannerTestsSwift: XCTestCase, AcceptSDKDelegate, WDAcceptManagerDelegate
{
    var returnedErr : Error!
    var expectation : XCTestExpectation!
    var sdk : AcceptSDK!
    var selectedDevice : WDAcceptTerminal?

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
            //Under StarIO or StarMicronics you can select two types of hardware, the mPOP (WDAMPOPExtensionUUID) and the regular Star Micronics CB2002 (WDAStarMicronicsExtensionUUID). Both operate in the same way, with the second not having barcode reader built-in.
            welf?.expectation.fulfill()
        })

        self.waitForExpectations(timeout: 25, handler: nil)
    }
    
    override func tearDown()
    {
        super.tearDown()
    }
  
    
    func testSocketScanner()
    {
        #if arch(i386) || arch(x86_64)
            let file:NSString = (#file as NSString).lastPathComponent as NSString
            NSLog("\n\t\t    [%@ %@] Not runnable on simulator 📱",file.deletingPathExtension , #function);
            return
            
        #endif
        
        //PART 1: We discover Socket scanners paired to your iOS device.
        //--------------------------------------
        expectation = self.expectation(description: "Discovering devices")
        self.discoverDevices()
        self.waitForExpectations(timeout: 100, handler: nil)
        if (self.selectedDevice == nil)
        {
            XCTFail("No paired scanner found. Make sure your terminal is paired in your iOS device settings and that the scanner is in stand-by mode (ie. by switching off and then on). For pairing you need to scan the pairing barcode in your Socket Scanner printed instructions.")
        }
        
        //PART 2: We set delegate for listening on paired scanner.
        //--------------------------------------
        expectation = self.expectation(description: "Setting active scanner to listen to")
        self.setDelegateAndActiveScanner()
        self.waitForExpectations(timeout: 100, handler: nil)
    }
    
    func discoverDevices()
    {
        weak var welf = self
        sdk.scannerManager.discoverDevices(.WDASocketExtensionUUID, completion: {(arr : [WDAcceptTerminal]?, error : Error?) in
            welf?.selectedDevice = arr?.first
            welf?.returnedErr = error
            welf?.expectation.fulfill()
        })
    }
    
    func setDelegateAndActiveScanner()
    {
        //When something is scanned, it will trigger the function below, dataReceived. So please, scan a barcode to pass the test.
        //You have a barcode in this demo, a file image under the name barcode_example
        sdk.scannerManager.add(self, forDevice: selectedDevice!)
    }
    
    func removeSpecialCharsFromString(text: String) -> String
    {
        let okayChars : Set<Character> =
            Set("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLKMNOPQRSTUVWXYZ1234567890+-*=(),.:!_".characters)
        return String(text.characters.filter {okayChars.contains($0) })
    }
    
    func device(_ device: WDAcceptTerminal, connectionStatusDidChange status:AcceptExtensionConnectionStatus)
    {
        print("Connection status changed \(status)")
    }
    
    func device(_ device: WDAcceptTerminal, dataReceived: Data) //Data received through barcode scanner
    {
        //It is a good practice to remove control characters as scanners have the bad tendency to add garbage at the end
        let barcodeAsText = self.removeSpecialCharsFromString(text: String.init(data: dataReceived, encoding: String.Encoding.utf8)!)
        print("Barcode read with value as string: \(barcodeAsText)")
        self.expectation.fulfill()
    }
    
    func device(_ device: WDAcceptTerminal, batteryLevelDidChange batteryLevel:Int)
    {
        print("Connection status changed \(batteryLevel)")
    }
}
