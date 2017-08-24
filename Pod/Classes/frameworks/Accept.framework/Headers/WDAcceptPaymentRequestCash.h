//
//  WDAcceptPaymentRequestCash.h
//  acceptSDK
//
//  Created by Danko, Radoslav on 03/05/16.
//  Copyright © 2016 Wirecard. All rights reserved.
//

#import "WDAcceptPayment.h"

/**
 *  @class WDAcceptPaymentRequestCash
 *  @brief Cash Payment Detail - contains the information specific to Cash payment
 **/
@interface WDAcceptPaymentRequestCash : WDAcceptPayment
/// Default NSObject init is unavailable
-(nonnull instancetype)init __attribute__((unavailable("use initWithAmount")));
-(nullable instancetype)initWithCoder:(nonnull NSCoder *)decoder NS_DESIGNATED_INITIALIZER;
-(nullable instancetype)initWithAmount:(NSDecimalNumber * __nonnull)amount
                       transactionType:(AcceptTransactionType)transactionType NS_DESIGNATED_INITIALIZER;
@end
