//
//  AcceptReceiptData.h
//  acceptSDK
//
//  Created by Danko, Radoslav on 23/10/15.
//  Copyright © 2015 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WDAcceptSale.h"

#define kWDACONTACTLESS @"CONTACTLESS"
#define kWDASwipe @"Swipe"
#define kWDASwipeFallback @"Swipe fallback"
#define kWDAChip @"Chip"

@class WDAcceptReceiptItem, WDAcceptSaleSummaryItem ;

/**
 *  @class WDAcceptReceiptData
 *  @discussion Complete Receipt Data - to be used to construct a receipt
 **/
@interface WDAcceptReceiptData : NSObject
/**
 */
@property (nonatomic) AcceptSaleType saleType;
/**
 */
@property (nullable,nonatomic,strong) NSString * merchantName;
/**
 */
@property (nullable,nonatomic,strong) NSString * merchantTaxNumber;
/**
 */
@property (nullable,nonatomic,strong) NSString * merchantPhone;
/**
 */
@property (nullable, nonatomic, strong) WDAcceptAddress * address;
/**
 */
@property (nullable, nonatomic, strong) NSString * shopId;
/**
 */
@property (nullable, nonatomic, strong) NSString * cashierId;
/**
 */
@property (nullable, nonatomic, strong) NSString * cashRegisterId;
/**
 */
@property (nullable, nonatomic, strong) NSArray <WDAcceptSaleItem *> * receiptItems;
/**
 */
@property (nullable,nonatomic, strong) NSArray <WDAcceptSaleSummaryItem *>* taxSummaryItems;
/**
 */
@property (nonatomic) BOOL  inclusiveTax;
/**
 */
@property (nullable,nonatomic, strong) WDAcceptSaleSummaryItem  *serviceChargeItem;
/**
 */
@property (nullable,nonatomic, strong) WDAcceptSaleSummaryItem  *tipItem;
/**
 */
@property (nullable,nonatomic, strong) WDAcceptSaleSummaryItem  *discountItem;
/**
 */
@property (nullable,nonatomic, strong)  NSArray <WDAcceptSaleSummaryItem  *>*couponItems;
/**
 */
@property (nullable,nonatomic, strong) NSDate  *utcPaymentDate;
/**
 */
@property (nullable,nonatomic) NSDecimalNumber *totalAmount;
/**
 */
@property (nonatomic) AcceptSaleState status;
/**
 */
@property (nullable,nonatomic) NSString * maskedCardNumber;
/**
 */
@property (nullable,nonatomic) NSString * cardholderName;
/**
 */
@property (nullable,nonatomic) NSString * cardType;
/**
 */
@property (nullable,nonatomic) NSString * emvAID;
/**
 */
@property (nullable,nonatomic) NSString * emvTID;
/**
 */
@property (nullable,nonatomic) NSString * emvMID;
/**
 */
@property (nullable,nonatomic) NSString * emvTransactionType;
/**
 */
@property (nonatomic) NSUInteger receiptID;
/**
 */
@property (nullable,nonatomic) NSString * currencyCode;
/**
 */
@property (nonatomic) NSInteger currencyMinorUnits;
/**
 */
@property (nullable,nonatomic) NSString * approvalCode;
/**
 */
@property (nullable, nonatomic, strong) NSString *technicalMessage;
/**
 */
@property (nullable,nonatomic,strong) NSString * transactionCertificate; //all emv tags
/**
 */
@property (nullable,nonatomic,strong) NSString * posEntryMode;
/**
 */
@property (nullable,nonatomic,strong) NSString * emvTVR;
/**
 */
@property (nullable,nonatomic, strong) NSString *issuerScript;
/**
 */
@property (nullable,nonatomic) NSString * signatureImage;
/**
 */
@property (nullable,nonatomic) NSString * memberId;
/**
 */
@property (nullable,nonatomic) NSDecimalNumber * aosa;
/**
 */
@property (nonatomic) BOOL verifiedOnTerminalCVM;
/**
 */
@property (nonatomic) BOOL PINVerified;
/**
 */
@property (nullable, nonatomic,strong) NSArray * receiptPaymentTypes;
/**
 */
@property (nullable,nonatomic) NSString * applicationCryptogram;
/**
 */
@property (nullable,nonatomic) WDAcceptReceiptAlipayDetails *alipayDetails;
/**
 * @discussion Receipt data stringified to print out in the console
 */
-(NSString * _Nullable)receiptDescription;
/**
 * @discussion POS entry mode described
 */
-(NSString * _Nullable)posEntryModeDescriptionWithCardType:(NSString* _Nullable) cardType;
/**
 * @discussion flag YES if the card transaction was performed CONTACTLESS
 */
-(BOOL)contactless;
/**
 */
-(UIImage * __nullable)receiptIdAsBarCodeImage;
/**
 */
-(UIImage * __nullable)alipayIdAsBarCodeImage;
/**
 */
-(NSString * __nullable)receiptIdAsBarCodeBase64;
/**
 */
-(NSString * __nullable)alipayIdAsBarCodeBase64;
/**
 */
@property (nullable,nonatomic, strong)  NSArray <WDAcceptReceiptData  *>*returns;
/**
 */
-(NSString* _Nullable)receiptAcceptSaleStatusDescription;
@end

