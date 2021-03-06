//
//  MerchantHelper.m
//  DemoAcceptSDK
//
//  Created by Fortes, Francisco on 3/9/17.
//  Copyright © 2017 Wirecard. All rights reserved.
//

#import "UserHelper.h"

@implementation UserHelper
{
    NSUserDefaults *userDefaults;
    WDAcceptMerchantUser *currentUser;
}

static UserHelper *sharedInstance = nil;

- (instancetype)initPrivate
{
    self = [super init];
    userDefaults = [[NSUserDefaults alloc] initWithSuiteName:@"AcceptDemo"];
    return self;
}

+ (UserHelper *)sharedInstance
{
    static dispatch_once_t pred;
    dispatch_once(&pred, ^{
        sharedInstance = [[UserHelper alloc] initPrivate];
    });
    
    return sharedInstance;
}

-(void)setUser:(WDAcceptMerchantUser*)merchantUser
{
    currentUser = merchantUser;
}

-(const WDAcceptMerchantUser*)getCurrentUser
{
    return currentUser;
}

-(NSDecimalNumber*)preferredSaleItemTax
{
    //You are free to select the tax from the avalilables in taxCategories and taxRates, that will depend on the country of your merchant
    return [[currentUser.merchant.taxCategories firstObject] currentValue];
}

-(NSDecimalNumber*)tipTax
{
    //You are free to select
    return [NSDecimalNumber decimalNumberWithString: [[currentUser.merchant tipTaxRate] stringValue]];
}

-(NSDecimalNumber*)serviceChargeRate
{
    //You are free to select
    return [NSDecimalNumber decimalNumberWithString: [[currentUser.merchant serviceChargeRate] stringValue]];
}

-(NSDecimalNumber*)serviceChargeTax
{
    //You are free to select
    return [NSDecimalNumber decimalNumberWithString:  [[currentUser.merchant serviceChargeTaxRate] stringValue]];
}

-(void)storeOpenShiftId:(NSString*)shiftId
{
    [userDefaults setObject:shiftId forKey:@"shiftId"];
}

-(NSString*)lastShiftId
{
    return [userDefaults objectForKey:@"shiftId"];
}

-(void)storeCashRegisterId:(NSString*)cashRegisterId
{
    [userDefaults setObject:cashRegisterId forKey:@"cashRegisterId"];
}

-(NSString*)selectedCashRegisterId
{
    return [userDefaults objectForKey:@"cashRegisterId"];
}

@end
