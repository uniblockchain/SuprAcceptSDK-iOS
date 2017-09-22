//
//  WDAcceptPaymentRequestCard.h
//  acceptSDK
//
//  Created by Danko, Radoslav on 03/05/16.
//  Copyright © 2016 Wirecard. All rights reserved.
//

#import "WDAcceptPayment.h"

@class WDAcceptTerminal;

/**
 *  @class WDAcceptPaymentRequestCard
 *  @brief Card Payment Request - contains the information specific to Card payment
 **/
@interface WDAcceptPaymentRequestCard : WDAcceptPayment
/// Default NSObject init is unavailable
-(nonnull instancetype)init __attribute__((unavailable("use initWithAmount:transactionType:terminal:")));
+(nonnull instancetype)new __attribute__((unavailable("use initWithAmount:transactionType:terminal:")));
-(nonnull instancetype)initWithAmount:(nonnull NSDecimalNumber *)amount
                        paymentMethod:(AcceptPaymentMethod)paymentMethod
                      transactionType:(AcceptTransactionType)transactionType __attribute__((unavailable("use initWithAmount:transactionType:terminal:")));

/**
 */
- (nullable instancetype)initWithCoder:(nonnull NSCoder *)decoder NS_DESIGNATED_INITIALIZER;
/**
 */
- (nullable instancetype )initWithAmount:(nonnull NSDecimalNumber *)amount
                         transactionType:(AcceptTransactionType)transactionType
                                terminal:(nonnull WDAcceptTerminal *)terminal NS_DESIGNATED_INITIALIZER;
/**
 */
@property (nonnull, nonatomic, strong) WDAcceptTerminal * terminal;

@end
