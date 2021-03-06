//
//  WDAcceptPaymentRequestAlipay.h
//  Accept
//
//  Created by Timko, Marek on 07/07/2017.
//  Copyright © 2017 Wirecard. All rights reserved.
//

#import "WDAcceptPayment.h"

/**
 *  @class WDAcceptPaymentRequestAlipay
 *  @brief Alipay Payment Request - contains the information specific to Alipay
 **/
@interface WDAcceptPaymentRequestAlipay : WDAcceptPayment
/// Default NSObject init is unavailable
- (nonnull instancetype)init __attribute__((unavailable("use initWithAmount:consumerId:")));
- (nonnull instancetype)initWithAmount:(nonnull NSDecimalNumber *)amount paymentMethod:(AcceptPaymentMethod)paymentMethod transactionType:(AcceptTransactionType)transactionType __attribute__((unavailable("use initWithAmount:transactionType:consumerId:")));
/**
 */
- (nullable instancetype)initWithCoder:(nonnull NSCoder *)decoder NS_DESIGNATED_INITIALIZER;
/**
 */
- (nullable instancetype )initWithAmount:(nonnull NSDecimalNumber *)amount
                         transactionType:(AcceptTransactionType)transactionType
                              consumerId:(nonnull NSString *)consumerId NS_DESIGNATED_INITIALIZER;
/**
 */
@property (nonnull, nonatomic, strong) NSString * consumerId;

@end
