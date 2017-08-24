//
//  WDAcceptPaymentDetailCoupon.h
//  acceptSDK
//
//  Created by Danko, Radoslav on 04/05/16.
//  Copyright © 2016 Wirecard. All rights reserved.
//

#import "WDAcceptPaymentDetail.h"
/**
 *  @class WDAcceptPaymentDetailCoupon
 *  @brief Coupon Payment Detail - contains the information specific to Coupon payment
 **/
@interface WDAcceptPaymentDetailCoupon : WDAcceptPaymentDetail
/**
 */
@property (nullable, nonatomic, retain) NSString *couponId;
@property (nullable, nonatomic, retain) NSString *brandId;
@end
