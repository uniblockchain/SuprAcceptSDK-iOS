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

class UserTestsSwift: XCTestCase, AcceptSDKDelegate
{
    var returnedErr : Error!
    var expectation : XCTestExpectation!
    var sdk : AcceptSDK!
    var userHelper : UserHelper!
    var loggedUser : WDAcceptMerchantUser?
    var resultStatus : WDAcceptResult?
    
    override func setUp()
    {
        super.setUp()
        self.continueAfterFailure = false
        sdk = AcceptSDK.sharedInstance()
        userHelper = UserHelper.sharedInstance()
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
    
    func testCredentialsAndGetUser()
    {
        expectation = self.expectation(description: "Requesting User Data")
        self.loginAndGetUserData()
        self.waitForExpectations(timeout: 100, handler: nil)
        if (loggedUser == nil || (loggedUser?.isKind(of: WDAcceptMerchantUser.self)) == false)
        {
            XCTFail("Error, did not return Merchant User. Are your credentials correct? Try login into the backend through internet browser.")
        }
    }
    
    
    func testRemindUsername()
    {
        expectation = self.expectation(description: "Remind Username")
        let request : WDAcceptRemindUsername = WDAcceptRemindUsername()
        weak var welf = self
        request.email = "your@email.com";//Here goes the email address you want to send the username for reminder
        sdk.userManager.manageCredentials(request, completion: {(result : WDAcceptResult?, error: Error?) in
            welf?.returnedErr = error
            welf?.resultStatus = result
            welf?.expectation.fulfill()
        })
        self.waitForExpectations(timeout: 100, handler: nil)
        if (returnedErr != nil || resultStatus == nil || resultStatus?.status != .OK)
        {
            XCTFail("Failed to remind username")
        }
    }
    
    func testRequestPasswordReset()
    {
        weak var welf = self
        expectation = self.expectation(description: "Request Password Reset")
        let request : WDAcceptRequestPasswordReset = WDAcceptRequestPasswordReset()
        request.username = "your username";//Here goes the username of the user who wants to reset the password. Password will be sent to his/her email. Note that, even when the username was not found, this will return OK: it is not secure to disclose that a username is correct.
        sdk.userManager.manageCredentials(request, completion: {(result : WDAcceptResult?, error: Error?) in
            welf?.returnedErr = error
            welf?.resultStatus = result
            welf?.expectation.fulfill()
        })
        self.waitForExpectations(timeout: 100, handler: nil)
        if (returnedErr != nil || resultStatus == nil || resultStatus?.status != .OK)
        {
            XCTFail("Failed to reset password.")
        }
    }
    
    func testChangePassword()
    {
        expectation = self.expectation(description: "Change Password")
        weak var welf = self
        let changePassword : WDAcceptChangePassword = WDAcceptChangePassword()
        //NOTE: To test password change functionality please provide below your own old password and your new password instead of the dummy strings
        changePassword.currentPassword = "Your Old Password Here"; // old password of the current user
        changePassword.theNewPassword = "Your New Password Here"; // new password of the current user
        //Note that you should offer the functionality to change password only to users already authenticated users in your app, as the SDK needs the credentials from its initialization:
        sdk.userManager.manageCredentials(changePassword, completion: {(result : WDAcceptResult?, error : Error?) in
            /* "result" are the details from the credential management process.
             AcceptResultStatusOK indicates the process ended with OK status.
             AcceptResultStatusPasswordCriteriaNotMet - in the case of changing the password indicates that the new password does not meet the criteria.
             AcceptResultStatusPasswordValidationFailure - in the case of changing password indicates the password validation failure old and new password mismatch.
             
             Note that result.detail will tell you what may have failed, including incorrect current password, password criteria not met, etc.
             The password policy can be requested using sdk.userManager.passwordPolicy, so you can use this criteria in your UI, and even for validating the strings yourself, though this is necessary as you will get a validation result in completion anyways.
             */
            welf?.returnedErr = error
            welf?.resultStatus = result
            welf?.expectation.fulfill()
        })
            
        self.waitForExpectations(timeout: 100, handler: nil)
        if (returnedErr != nil || resultStatus == nil || resultStatus?.status != .OK)
        {
            XCTFail("Failed to change password.")
        }
    }
    
}
