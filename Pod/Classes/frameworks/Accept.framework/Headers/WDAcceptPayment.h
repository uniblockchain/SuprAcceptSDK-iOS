//
//  WDAcceptPayment.h
//  acceptSDK
//
//  Created by Danko, Radoslav on 03/05/16.
//  Copyright © 2016 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
NS_ASSUME_NONNULL_BEGIN
/**
 *  @brief AcceptPaymentMethod
 *  @discussion Enumerator with the payment types.
 **/
typedef NS_ENUM(NSInteger, AcceptPaymentMethod ){
    AcceptPaymentMethodCash, //Default
    AcceptPaymentMethodCard,
    AcceptPaymentMethodCoupon,
    AcceptPaymentMethodAlipay,
    AcceptPaymentMethodUnknown
    
};

/**
 *  @brief AcceptTransactionType
 *  @discussion Enumerator with the transaction types.
 **/
//typedef NS_ENUM(NSInteger, AcceptTransactionType) {
//    AcceptTransactionTypeUnknown = 0,
//    AcceptTransactionTypeCardPurchase,
//    AcceptTransactionTypeCardRefund,
//    AcceptTransactionTypeCardAuthorize,
//    AcceptTransactionTypeCardCapture,
//    AcceptTransactionTypeCardReversal,
//    AcceptTransactionTypeCardAutoResolve,
//    AcceptTransactionTypeCashPurchase,
//    AcceptTransactionTypeCashRefund,
//    AcceptTransactionTypeCashReversal,
//    AcceptTransactionTypeCouponPurchase,
//    AcceptTransactionTypeCouponReversal,
//    AcceptTransactionTypeAlipayPurchase,
//    AcceptTransactionTypeAlipayReversal,
//    AcceptTransactionTypeAlipayRefund
//};
typedef NS_ENUM(NSInteger, AcceptTransactionType) {
    AcceptTransactionTypePurchase, //Default
    AcceptTransactionTypeAuthorize,
    AcceptTransactionTypeCapture,
    AcceptTransactionTypeRefund,
    AcceptTransactionTypeReferenceRefund,
    AcceptTransactionTypeReversal,
    AcceptTransactionTypeAutoResolve,
    AcceptTransactionTypeUnknown
};

/**
 *  @brief WDAcceptPaymentState
 *  @discussion Payment Status enumeration
 **/
typedef NS_ENUM(NSUInteger, AcceptPaymentState) {
    AcceptPaymentStateUnknown=0,
    AcceptPaymentStateNotNeeded,
    AcceptPaymentStateSkipped,
    AcceptPaymentStateApproved,
    AcceptPaymentStateCompleted,
    AcceptPaymentStateCaptured,
    AcceptPaymentStateReversed,
    AcceptPaymentStateRefunded,
    AcceptPaymentStateInitialized,
    AcceptPaymentStateIncomplete,
    AcceptPaymentStateDeclined,
    AcceptPaymentStateRejected,
    AcceptPaymentStateFailed,
    AcceptPaymentStateFailedMin
};

/**
 *  @class WDAcceptPayment
 *  @brief Payment Request - contains the information about payment method, transaction type and amount
 **/
@interface WDAcceptPayment : WDAcceptObject<NSCoding>
/// Default NSObject init is unavailable
- (nonnull instancetype)init __attribute__((unavailable("use initWithAmount:paymentMethod:transactionType:")));
/**
 */
- (nullable instancetype)initWithAmount:(nonnull NSDecimalNumber *)amount
                          paymentMethod:(AcceptPaymentMethod)paymentMethod
                        transactionType:(AcceptTransactionType)transactionType NS_DESIGNATED_INITIALIZER;
/**
 */
- (nullable instancetype)initWithCoder:(nonnull NSCoder *)decoder NS_DESIGNATED_INITIALIZER;
/**
 */
@property (nonatomic) AcceptPaymentMethod paymentMethod;
/**
 */
@property (nonatomic) AcceptTransactionType transactionType;
/**
 */
@property (nonnull, nonatomic, strong) NSDecimalNumber *amount;

@end
NS_ASSUME_NONNULL_END
