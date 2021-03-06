//
//  WDAcceptPaymentDetailWeChat.h
//  Accept
//
//  Created by Danko, Radoslav on 15/11/2017.
//  Copyright © 2017 Wirecard. All rights reserved.
//

#import "WDAcceptPaymentDetail.h"

/**
 *  @class WDAcceptPaymentDetailWeChat
 *  @brief WeChat Payment Detail - contains the information specific to WeChat
 **/
@interface WDAcceptPaymentDetailWeChat : WDAcceptPaymentDetail

@property (nonnull, nonatomic, strong) NSString *partnerTransactionId;
@property (nonnull, nonatomic, strong) NSString *timeStamp;
@property (nonnull, nonatomic, strong) NSString *wechatProviderTransactionId;
@property (nonnull, nonatomic, strong) NSString *wechatTimeEnd;
@property (nonnull, nonatomic, strong) NSDecimalNumber *wechatRate;
@property (nonnull, nonatomic, strong) NSString *wechatDeviceInfo;
@property (nonnull, nonatomic, strong) NSDecimalNumber *wechatCashFee;
@property (nonnull, nonatomic, strong) NSString *wechatSubMchId;
-(id _Nullable )castTo:(Class _Nonnull )targetClass;
@end
