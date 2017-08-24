//
//  MerchantHelper.h
//  DemoAcceptSDK
//
//  Created by Fortes, Francisco on 3/9/17.
//  Copyright © 2017 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Accept/Accept.h>
#import "Constants.h"

@interface UserHelper : NSObject
+ (UserHelper *)sharedInstance;
-(void)setUser:(WDAcceptMerchantUser*)merchantUser;
-(const WDAcceptMerchantUser*)getCurrentUser;
-(NSDecimalNumber*)preferredSaleItemTax;
-(NSDecimalNumber*)tipTax;
-(NSDecimalNumber*)serviceChargeRate;
-(NSDecimalNumber*)serviceChargeTax;
-(void)storeOpenShiftId:(NSString*)shiftId;
-(NSString*)lastShiftId;
-(void)storeCashRegisterId:(NSString*)cashRegisterId;
-(NSString*)selectedCashRegisterId;
@end
