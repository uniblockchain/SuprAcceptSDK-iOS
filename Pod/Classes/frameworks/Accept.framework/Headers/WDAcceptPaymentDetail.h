//
//  WDAcceptPayment.h
//  acceptSDK
//
//  Created by Danko, Radoslav on 23/10/15.
//  Copyright © 2015 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "WDAcceptPayment.h"


/**
 *  @class WDAcceptPaymentDetail
 *  @brief Complete information about performed Payment
 **/
@interface WDAcceptPaymentDetail : WDAcceptObject<NSCoding>
/**
 */
@property (nonatomic) AcceptPaymentMethod paymentMethod;
/**
 */
@property (nonatomic) AcceptTransactionType transactionType;
/**
 */
@property (nonnull, nonatomic, retain) NSString *internalId;
/**
 */
@property (nonatomic) AcceptPaymentState status;
/**
 */
@property (nonnull, nonatomic, retain) NSDecimalNumber *amount;
/**
 */
@property (nullable, nonatomic, retain) NSDate *processedByGateway;
/**
 */
@property (nullable, nonatomic, retain) NSDate *lastUpdated;
/**
 */
@property (nullable, nonatomic, retain) NSString *gatewayReference;
/**
 */
@property (nonnull, nonatomic, retain) NSDate *initialized;
/**
 */
@property (nullable, nonatomic, retain) NSString *gateway;
/**
 */
@property (nullable, nonatomic, strong) NSString *technicalMessage;
/**
 */
@property (nullable, nonatomic, strong) NSArray * refundPayments;
/**
 */
@property (nullable, nonatomic, strong) NSArray * reversalPayments;
/**
 */
@property (nullable, nonatomic, strong) NSArray * autoResolvePayments;
/**
 */
-(NSString *_Nullable)statusDescription;
/**
 */
-(NSString *_Nullable)paymentMethodDescription;
/**
 */
-(BOOL)paymentStatusPositive;
/**
 */
-(BOOL)refundable;
/**
 */
-(BOOL)reversible;

@end

