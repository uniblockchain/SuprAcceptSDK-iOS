//
//  WDAcceptPaymentRequestCoupon.h
//  acceptSDK
//
//  Created by Danko, Radoslav on 03/05/16.
//  Copyright © 2016 Wirecard. All rights reserved.
//

#import "WDAcceptPayment.h"

/**
 *  @class WDAcceptPaymentRequestCoupon
 *  @brief Coupon Payment Request - contains the information specific to Coupon payment
 **/
@interface WDAcceptPaymentRequestCoupon : WDAcceptPayment
/// Default NSObject init is unavailable
-(nonnull instancetype)init __attribute__((unavailable("use initWithAmount")));

-(nullable instancetype)initWithCoder:(nonnull NSCoder *)decoder NS_DESIGNATED_INITIALIZER;
-(nullable instancetype)initWithAmount:(NSDecimalNumber * __nonnull)amount
                       transactionType:(AcceptTransactionType)transactionType
                              internalId:(NSString *__nonnull)internalId
                               externalId:(NSString *__nonnull)externalId NS_DESIGNATED_INITIALIZER;

@property (nullable, nonatomic, strong) NSString *internalId;
@property (nullable, nonatomic, strong) NSString *externalId;

@end
