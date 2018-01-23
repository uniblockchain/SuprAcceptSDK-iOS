//
//  TestUtils.h
//  acceptSDK
//
//  Created by Francisco Fortes on 17/10/15.
//  Copyright © 2015 Wirecard. All rights reserved.
//

#import "SaleHelper.h"
#import "UserHelper.h"
#import "DDLog.h"

@interface PaymentHandler : NSObject<WDAcceptPaymentDelegate>
@end

@interface BaseTestsObcj : XCTestCase <AcceptSDKDelegate>
{
    __block NSError *returnedErr;
    __weak XCTestExpectation *expectation;
    AcceptSDK *sdk;
    SaleHelper *saleHelper;
    UserHelper *userHelper;
    __block WDAcceptMerchantUser *loggedUser;
    __block WDAcceptCashRegister *cashRegister;
    __block WDAcceptCashShift *lastShift;
    __block WDAcceptSaleRequest *aSale;
    __block WDAcceptSaleResponse *saleResponse;
    __block AcceptResultStatus resultStatus;
    __block WDAcceptTerminal *selectedDevice;
    __block PaymentHandler *_paymentHandler;
}

-(void)loginAndGetUserData;
-(void)discoverDevices:(WDAExtensionTypeUUID)extensionUUID;

@end
