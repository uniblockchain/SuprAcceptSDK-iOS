//
//  WDAcceptSaleManagerUI.h
//  acceptSDK
//
//  Created by Danko, Radoslav on 13/04/2017.
//  Copyright © 2017 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Accept/WDADataTypes.h>

NS_ASSUME_NONNULL_BEGIN

///**
// *  @brief AcceptPaymentMethod
// *  @discussion Enumerator of payment method types
// **/
//typedef NS_ENUM(NSInteger, AcceptPaymentMethod ) {
//    AcceptPaymentMethodCash,
//    AcceptPaymentMethodCard,
//    AcceptPaymentMethodCoupon,
//    AcceptPaymentMethodAlipay
//};

/**
 *  @brief AcceptPaymentMethodMask
 *  @discussion These constants are mask bits for specifying the payment method type
 **/
typedef NS_OPTIONS(NSUInteger, AcceptPaymentMethodMask)   {
    AcceptPaymentMethodMaskCashOnly = 1 << 20,
    AcceptPaymentMethodMaskCardOnly = 1 << 21,
    AcceptPaymentMethodMaskAlipayOnly = 1 << 22,
    AcceptPaymentMethodMaskWeChatOnly = 1 << 23,
    //    AcceptPaymentMethodMaskCouponOnly = 1 << 24,
    AcceptPaymentMethodMaskStandard = (AcceptPaymentMethodCash | AcceptPaymentMethodCard),
    AcceptPaymentMethodMaskQR = (AcceptPaymentMethodAlipay | AcceptPaymentMethodWeChat),
    AcceptPaymentMethodMaskAll = (AcceptPaymentMethodCash | AcceptPaymentMethodCard | AcceptPaymentMethodAlipay | AcceptPaymentMethodWeChat)
};

#pragma mark - WDAcceptSaleConfiguration
/**
 *  @class WDAcceptSaleConfiguration
 *  @discussion  Sale configuration
 **/
@interface WDAcceptSaleConfiguration : NSObject
/// Sale Amount - if nil then user entry UI will be displayed to collect the amount
@property (nullable,nonatomic,readonly) NSDecimalNumber *amount;
/// Currency for the sale
@property (nonatomic, readonly) NSString *currency;
/// Tax rate for the Sale
@property (nonatomic, readonly) NSDecimalNumber *taxRate;
/// Payment Methods
@property (nonatomic, readonly) AcceptPaymentMethodMask paymentMethods;
/// Number of decimal places for the set currency
@property (nonatomic,readonly) NSUInteger currencyDecimalPlaces;
/// Clear user preferences [Cash Register, Shift, User, Merchant]
@property (nonatomic) BOOL resetUserPreferences;
/// Language for the Localization of the UI elements [en,de,es] - defaults to "en"
@property (nonatomic, strong) NSString *language;

/**
 * @brief Default Initializer - Amount was entered by user before
 * @param amount Sale amount - if nil then user entry UI will be presented to collect the amount
 * @param currency Currency for the sale
 * @param taxRate Tax rate for the sale
 * @return the sale configuration
 **/
-(nullable instancetype)initWithAmount:(NSDecimalNumber *)amount
                              currency:(NSString *)currency
                               taxRate:(NSDecimalNumber *)taxRate
                        paymentMethods:(AcceptPaymentMethodMask)paymentMethods NS_DESIGNATED_INITIALIZER;
/**
 * @brief Default Initializer - Amount to be entered in the payment flow
 * @param currency Currency for the sale
 * @param taxRate Tax rate for the sale
 * @return the sale configuration
 **/
-(nullable instancetype)initWithCurrency:(NSString *)currency
                               taxRate:(NSDecimalNumber *)taxRate
                        paymentMethods:(AcceptPaymentMethodMask)paymentMethods NS_DESIGNATED_INITIALIZER;
@end

#pragma mark - WDAcceptSaleManagerUI

/**
 *  @class WDAcceptSaleManagerUI
 *  @brief UI component of Sale Management
 */
@interface WDAcceptSaleManagerUI : NSObject
/// Default NSObject init is unavailable
- (nonnull instancetype)init __attribute__((unavailable("use [WDAcceptSaleManagerUI  sharedInstance]")));
//Default NSObject new is unavailable
+ (nonnull instancetype)new __attribute__((unavailable("use [WDAcceptSaleManagerUI sharedInstance]")));
///default initializer
+ (WDAcceptSaleManagerUI*)sharedInstance;

/// copy of the completion block called at the end of Sale process
@property (nonatomic,copy) SaleCompletion paymentCompletion;
/// copy of the progress block called upon the update from the Payment flow
@property (nonatomic,copy) PaymentProgress paymentProgress;

/**
 *  @brief Start the payment process by using built in UI
 *  @param progress Block bearing the information about the payment process progress
 *  @param completion Block that will be called at the very end of payment flow. It provides an AcceptTransaction object (that may be nil if unauthorised) or a descriptive error
 **/
- (void)pay:(WDAcceptSaleConfiguration *)saleConfiguration
   progress:(PaymentProgress )progress
 completion:(SaleCompletion )completion;

@end

NS_ASSUME_NONNULL_END
