//
//  TestDomainDataServices.m
//  acceptSDK
//
//  Created by Danko, Radoslav on 17/10/15.
//  Copyright © 2015 Wirecard. All rights reserved.
//


#import <XCTest/XCTest.h>
#import <libextobjc/EXTScope.h>
#import "SaleHelper.h"
#import "UserHelper.h"
#import "DDLog.h"

@interface UserTestsObjc : XCTestCase <AcceptSDKDelegate>
{
    __block NSError *returnedErr;
    __weak XCTestExpectation *expectation;
    AcceptSDK *sdk;
    UserHelper *userHelper;
    __block WDAcceptMerchantUser *loggedUser;
    __block AcceptResultStatus resultStatus;
}

@end

@implementation UserTestsObjc

- (void)setUp
{
    [super setUp];
    self.continueAfterFailure = NO;
    sdk = [AcceptSDK sharedInstance];
    userHelper = [UserHelper sharedInstance];
    [sdk setupWithEnvironment:AcceptEnvironmentPublicTest username:KUSERNAME password:KPASSWORD completion:^(WDAcceptMerchantUser * _Nullable currentUser, WDAcceptMerchantCashier * _Nullable cashier, NSError * _Nullable error) {
        [sdk addDelegate:self];
        [sdk setDevMode:YES]; //Setting dev mode as enabled will write logs in your app's document folder and fill the console log with debug messages - do not forget to disable it
                              //before releasing your app to the public!!
        [AcceptSDK ddSetLogLevel:DDLogLevelInfo];
        
    }];
    
    [self waitForExpectationsWithTimeout:25 handler:nil];
    
    XCTAssert(true,@"Setup success");
}

-(void)testCredentialsAndGetUser
{
    expectation = [self expectationWithDescription:@"testCredentialsAndGetUser"];
    MerchantDetailCompletion completion = ^(WDAcceptMerchantUser *merchantUser, NSError *err)
    {
        loggedUser = merchantUser;
        returnedErr = err;
        [expectation fulfill];
    };
    loggedUser = nil;
    [[sdk userManager] currentUser:completion];
    
    [self waitForExpectationsWithTimeout:100 handler:nil];
    if (returnedErr || !loggedUser)
    {
        XCTFail(@"Failed to get user, probably credentials were wrong.");
    }
}

- (void)testRemindUsername
{
    expectation = [self expectationWithDescription:@"testRemindUsername"];
    WDAcceptRemindUsername *request = [WDAcceptRemindUsername new];
    request.email = @"your@email.com";//Here goes the email address you want to send the username for reminder
    [sdk.userManager manageCredentials:request completion:^(WDAcceptResult * result, NSError* error)
    {
        returnedErr = error;
        resultStatus = result && result.status;
        [expectation fulfill];
    }];
    
    [self waitForExpectationsWithTimeout:100 handler:nil];
    if (returnedErr || !resultStatus || resultStatus != AcceptResultStatusOK)
    {
        XCTFail(@"Failed to remind username.");
    }
}

- (void)testRequestPasswordReset
{
    expectation = [self expectationWithDescription:@"testRemindUsername"];
    WDAcceptRequestPasswordReset *request = [WDAcceptRequestPasswordReset new];
    request.username = @"your username";//Here goes the username of the user who wants to reset the password. Password will be sent to his/her email
    //Note that, even when the username was not found, this will return OK: it is not secure to confirm a username is correct in such a request.
    [sdk.userManager manageCredentials:request completion:^(WDAcceptResult * result, NSError* error)
     {
         resultStatus = result && result.status;
         returnedErr = error;
         [expectation fulfill];
     }];
    
    [self waitForExpectationsWithTimeout:100 handler:nil];
    if (returnedErr || !resultStatus || resultStatus != AcceptResultStatusOK)
    {
        XCTFail(@"Failed to reset password.");
    }
}

- (void)testChangePassword
{
    expectation = [self expectationWithDescription:@"testChangePassword"];
    
    //End of credential management process
    CredentialManagementCompletion completion = ^(WDAcceptResult * _Nullable result, NSError* _Nullable error){
        //result - details from the credential management process
        // AcceptResultStatusOK indicates the process ended with OK status
        // AcceptResultStatusPasswordCriteriaNotMet - in the case of changing the password indicates that the new password does not
        //                                            meet the criteria
        // AcceptResultStatusPasswordValidationFailure - in the case of changing password indicates the password validation failure
        //                                               old and new password mismatch
        
        //Note that result.detail will tell you what may have failed, including incorrect current password, password criteria not met, etc.
        //The password policy can be requested using sdk.userManager.passwordPolicy, so you can use this criteria in your UI, and even for validating the strings yourself, though this is necessary as you will get a validation result in completion anyways.
        returnedErr = error;
        resultStatus = result && result.status;
        [expectation fulfill];
    };
    
    //******************* CHANGE PASSWORD *******************//
    // Change Password details - available only to the AUTHENTICATED user
    WDAcceptChangePassword *changePassword = [WDAcceptChangePassword new];
    //NOTE: To test password change functionality please provide your own old password and your new password
    changePassword.currentPassword = @"Old Password"; // old password of the current user
    changePassword.theNewPassword = @"New Password"; // new password of the current user
    
    
    // Change password for the AUTHENTICATED user
   //Note that current password and username are setup in sdk already, see first function in this file
    [sdk.userManager manageCredentials:changePassword // Change password object
                            completion:completion];//End of credential management process
    
    
    [self waitForExpectationsWithTimeout:100 handler:nil];
    if (returnedErr || !resultStatus || resultStatus != AcceptResultStatusOK)
    {
        XCTFail(@"Failed to change password.");
    }
}


 
@end