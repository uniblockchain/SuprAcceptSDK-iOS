//
//  SaleHelper.h
//  DemoAcceptSDK
//
//  Created by Fortes, Francisco on 3/9/17.
//  Copyright © 2017 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Accept/Accept.h>
#import "Constants.h"

@interface SaleHelper : NSObject
+ (SaleHelper *)sharedInstance;
-(WDAcceptSaleRequest *)currentSale;
-(WDAcceptSaleRequest *)newSale;
-(void)saleToSaveIdFrom:(WDAcceptSaleResponse*)sale;
-(NSString*)saleIdSaved;
-(WDAcceptReceipt*)receiptForDatecsFromReceiptData:(WDAcceptReceiptData*)receiptData;
@end
