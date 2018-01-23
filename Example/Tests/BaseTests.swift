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

class PaymentHandler : NSObject, WDAcceptPaymentDelegate {
    var completion: ((_ transaction: WDAcceptSaleResponse?, _ error: Error?) -> Void)?

    init(completion: @escaping (_ transaction: WDAcceptSaleResponse?, _ error: Error?) -> Void) {
        self.completion = completion
        super.init()
    }

    // Updates from the payment flow
    func progress(_ paymentProgress: AcceptStateUpdate) {
        // statusUpdate - coded statuses are reported throughout the payment flow
    }

    // In the case the Cardholder Signature is required by the Payment flow this block will be executed
    // Your task is to respond to it by collecting the signature image from the customer and
    // posting it back in the sendCollectedSignature method
    func collectSignature(_ signatureRequest: WDAcceptSignatureRequest) {
        //signatureRequest - comes from the payment flow and once you collect the signature from the customer
        // send it back in the signatureRequest.sendCollectedSignature
        signatureRequest.sendCollectedSignature(TestUtils.signatureImage(fromText: "Test"),nil)
        //The signature image is transferred to the backend and stored with the Sale
    }

    // Note: Applicable to terminals without BUTTONS
    // In the case the Cardholder Signature was collected then the merchant is required to confirm it's validity
    // A. If the terminal has buttons that are used for Approving/Rejecting then this block is either never called from Payment flow
    // or it's signatureVerificationCallback comes nil
    // B. If the terminal does not have buttons then the Application must present a user interface to Approve/Reject the Cardholder Signature
    func confirm(_ confirmationType: AcceptPaymentConfirmationType, paymentConfirmationResult: PaymentConfirmationResult? = nil) {
        if let paymentConfirmationResult = paymentConfirmationResult {
            // Here the simplified use of Approving the Cardholder Signature is demonstrated
            paymentConfirmationResult(AcceptPaymentConfirmationResult.approved)
        }
    }

    // Note: Applicable to terminals without BUTTONS
    // In the case the payment Card has more than one card application available then the client application
    // has to present user interface for the Cardholder to select preferred card application
    // The list of card applications is present in appSelectionRequest.appsArray as a list of Strings
    func cardApplication(_ appSelectionRequest: WDAcceptAppSelectionRequest) {
        // There is more than 1 card application available
        // Present the UI for the Cardholder to select preferred card application (Debit | Credit)
        if ((appSelectionRequest.appsArray?.count) != nil) {
            // Here we demonstrate the simplified use of selecting the first card application from the list of available card applications
            // and sending it to the Payment flow
            appSelectionRequest.selectCardApplication(UInt(0))
        }
    }

    // The end of the payment process
    func completion(_ saleResponse: WDAcceptSaleResponse?, saleResponseError: Error?) {
        //sale - Is the completed Sale - contains the sale status, details, results
        //error - If any error is encountered during the sale it would be reported
        //in the form of error and hierarchy of underlying errors to give you as much details as possible
        self.completion?(saleResponse, saleResponseError)
    }
}

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
    var paymentHandler: PaymentHandler?
    
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

        self.paymentHandler = PaymentHandler(completion: { (transaction: WDAcceptSaleResponse?, error: Error?) in
            self.saleResponse = transaction
            self.returnedErr = error
            self.expectation.fulfill()
        })
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
