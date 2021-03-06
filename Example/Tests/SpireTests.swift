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

class SpireTestsSwift: BaseTestsSwift, WDAcceptManagerDelegate
{
    var configCompletionStatus : AcceptUpdateConfigurationStatus!

    /*
     
     IMPORTANT NOTE:
     -This test requires an actual iOS device (not simulator).
     -You have to have a Spire terminal paired through your iOS device settings.
     -Your terminal must have been provided by Wirecard, and be turned on.
     -If your backend settings include cash management with mandatory cash registers, you will need to run CashTests first (to have valid ids)
     */
    
    override func setUp()
    {
        super.setUp()
    }
    
    func testSpire()
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
        else
        {
            UserHelper.sharedInstance().setUser(loggedUser)
        }
        
        //PART 2: We discover Spire terminals
        //paired to your iOS device.
        //--------------------------------------
        expectation = self.expectation(description: "Discovering devices")
        self.discoverDevices(.WDAPosMateExtensionUUID)
        self.waitForExpectations(timeout: 100, handler: nil)
        if (self.selectedDevice == nil)
        {
            XCTFail("No paired terminal found. Make sure your terminal is paired in your iOS device settings and that the terminal is in stand-by mode (ie. by switching off and then on and waiting until the screen lights off).")
        }
        else
        {
            sdk.terminalManager.add(self, forDevice: selectedDevice!)
        }
        
        //PART 3: We check for updates on the terminal
        //---------------------------------------------
        expectation = self.expectation(description: "Checking for terminal update")
        self.checkingForTerminalConfigUpdates()
        self.waitForExpectations(timeout: 300, handler: nil)
        if (self.configCompletionStatus == .failure)
        {
            XCTFail("Error when updating the terminal. Make sure your terminal is paired in your iOS device settings and that the terminal is in stand-by mode (ie. by switching off and then on and waiting until the screen lights off).")
        }
        
        //PART 4: We do a card sale using Spire terminal
        //---------------------------------------------
        expectation = self.expectation(description: "Card sale")
        self.doCardPayment()
        self.waitForExpectations(timeout: 300, handler: nil)
        if (self.saleResponse == nil)
        {
            XCTFail("Sale did not succeed. Make sure your terminal is paired in your iOS device settings and that the terminal is in stand-by mode (ie. by switching off and then on and waiting until the screen lights off).")
        }
        else
        {
            SaleHelper.sharedInstance().saleToSaveId(from:self.saleResponse)
        }

        //PART 5: We refund the sale we just did
        //(for testing purposes; this is important if you develop using an actual credit card)
        //Algo note that refunds are allowed only for some period of time (ie: midnight on current time, or next 24 hours, etc) and after that, only reversals are allowed. But refunds are for free, while reversals actually cost money (so use reversals responsibly!)
        //-------------------------------------------
        expectation = self.expectation(description: "Refund sale")
        self.refundTransaction()
        self.waitForExpectations(timeout: 300, handler: nil)
        if (self.saleResponse == nil || self.saleResponse?.status != .returned)
        {
            XCTFail("Sale did not succeed. Make sure your terminal is paired in your iOS device settings and that the terminal is in stand-by mode (ie. by switching off and then on and waiting until the screen lights off).")
        }
    }
    
    
    func checkingForTerminalConfigUpdates()
    {
        let completionUpdate : UpdateTerminalCompletion = {[weak self](updStatus : AcceptUpdateConfigurationStatus?, updError : Error?) in
            //Note that completion here will happen when:
            // 1- The update has been completed, but also the terminal has fully restarted and entered stand-by (this may take a couple of minutes in the case of firmware)
            // 2- There was no response from terminal (something went wrong) for several seconds, meaning update failed.
            self?.returnedErr = updError
            self?.configCompletionStatus = updStatus
            self?.expectation.fulfill()
        }
        
        let progress : UpdateConfigurationProgress = {(progressUpdate : AcceptUpdateConfigurationProgressUpdate) in
            print("Terminal update progress: \(progressUpdate.rawValue)")
        }

        //Note: You may update the firmware too using AcceptTerminalUpdateTypeFirmware
        //Note: The accept SDK will keep track of what version was previously installed, and decide if an update is required by comparing with the latest in backend.
        //This means, the first time you run this test, the configuration will be updated on the terminal. A second time will tell you "AcceptUpdateConfigurationStatusUnnecessary"
        //To force the actual update again you will have to remove the demo app from your iOS device and re-run the test.
        
        sdk.terminalManager.update(selectedDevice!,
                                   updateType:AcceptTerminalUpdateTypeMaskConfiguration,
                                   progress:progress,
                                   completion:completionUpdate)
    }
    
    func doCardPayment()
    {
        
        let paymentConfiguration : WDAcceptPaymentConfig = WDAcceptPaymentConfig.init()
        guard let sale = SaleHelper.sharedInstance().newSale() else
        {
            XCTFail("Something went really wrong - doCardPayment")
            self.expectation.fulfill()
            return
        }
        self.aSale = sale
        self.aSale.addSaleItem(NSDecimalNumber(value: 3.4),
                               quantity:5,
                               taxRate:UserHelper.sharedInstance().preferredSaleItemTax(),
                               itemDescription:"Red Apple",
                               productId:"Dummy ID 1")
        self.aSale.addSaleItem(NSDecimalNumber(value: 2.25),
                               quantity:3,
                               taxRate:UserHelper.sharedInstance().preferredSaleItemTax(),
                               itemDescription:"Orange",
                               productId:"Dummy ID 2")
        //You can add a service charge to the whole basket -- but this is optional
        self.aSale.addServiceCharge(UserHelper.sharedInstance().serviceChargeRate(),
                                    taxRate:UserHelper.sharedInstance().serviceChargeTax())
        //You can add a tip of any value you want. Notice that backend validate taxes, so their values should match the ones your merchant has defined in setup.
        self.aSale.addGratuity(NSDecimalNumber(value: 1.0),
                               taxRate:UserHelper.sharedInstance().tipTax())
        //You can add a discount for the whole basket when productId is nil, or per productId otherwise. Below, a discount of 6%
        self.aSale.addDiscount(NSDecimalNumber(value: 6.0),
                               productId:nil)
        paymentConfiguration.sale = self.aSale
        paymentConfiguration.sale.cashRegisterId = UserHelper.sharedInstance().selectedCashRegisterId() //Note: if your backend settings have cash mgmt enabled in backend, you will need to run cash tests first to get this value as well as shiftId below
        paymentConfiguration.sale.shiftId = UserHelper.sharedInstance().lastShiftId()
        paymentConfiguration.sale.resetPayments()
        paymentConfiguration.sale.addCardPayment(paymentConfiguration.sale.totalToPay() ?? NSDecimalNumber.init(value:0),
                                                 terminal:self.selectedDevice!)
        
        sdk.terminalManager.setActive(self.selectedDevice, completion:{[weak self]() in
            self?.sdk.saleManager.pay(paymentConfiguration, delegate: (self?.paymentHandler)!)
        })
    }
    
    func refundTransaction()
    {
        guard let saleToBeRefunded = self.saleResponse!.saleReturn() else
        {
            XCTFail("Something went really wrong - refundTransaction saleReturn")
            self.expectation.fulfill()
            return
        }
        //This is an example of full refund: all items are refunded, EXCEPT SERVICE CHARGE
        saleToBeRefunded.removeServiceCharge()
        guard let totalToPay = saleToBeRefunded.totalToPay() else
        {
            XCTFail("Something went really wrong - refundTransaction totalToPay")
            self.expectation.fulfill()
            return
        }
        saleToBeRefunded.cashRegisterId = UserHelper.sharedInstance().selectedCashRegisterId()
        saleToBeRefunded.cashierId = self.aSale.cashierId
        saleToBeRefunded.customerId = self.aSale.customerId
        //This is an example of full refund: all items are refunded, EXCEPT SERVICE CHARGE
        saleToBeRefunded.removeServiceCharge()
        //For partial refund, see CashTests example
        saleToBeRefunded.addCardPayment(totalToPay, terminal:WDAcceptTerminal.init()) //terminal is unnecessary here
        self.saleResponse = nil
        sdk.saleManager.refundSale(saleToBeRefunded, message:"Refunded in demo app for testing reasons", completion:{[weak self](acceptSale : WDAcceptSaleResponse?, error : Error?) in
            self?.returnedErr = error
            self?.saleResponse = acceptSale
            self?.expectation.fulfill()
        })
    }

    
    func device(_ device: WDAcceptTerminal, connectionStatusDidChange status:AcceptExtensionConnectionStatus)
    {
        print("Connection status changed \(status)")

    }
}
