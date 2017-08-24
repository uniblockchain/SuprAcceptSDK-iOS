//
//  Accept for iOS
//
//  Created by Radoslav Danko and Francisco Fortes.
//  Copyright (c) 2016 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "WDADataTypes.h"
#import "WDAcceptConstants.h"

#define WAIT_INTERVAL_SIGNATURE 30

#pragma mark - GCD utils

// causion! can make immediate sync call instead of async,
// usable if at least one dispatch_async with dispatch_get_main_queue() has already been called
void dispatch_main_unsafe(dispatch_block_t block);
void dispatch_main_safe(dispatch_block_t block);
void dispatch_main_sync_safe(dispatch_block_t block);
void synchronous_call(dispatch_queue_t queue, void *queueTag, dispatch_block_t block);

#define AssertProperQueue(queueTag) NSAssert(dispatch_get_specific((queueTag)), @"Invoked on incorrect queue")

#pragma mark - AcceptUtils

@interface AcceptUtils : NSObject

+(AcceptUtils *)sharedInstance;
+(NSString *)suiteName;

+ (NSUInteger) numberOfFractionDigitsForCurrency:(NSString*)currencyAsISO4217Code;
+ (NSUInteger) numberOfFractionDigitsForCurrencyIOS:(NSString *)currencyAsISO4217Code __attribute__((deprecated("Mismatch between iOS decimal places and ISO for IDR")));

+ (NSDecimalNumberHandler *)decimalHandlerForCurrency:(NSString*)currencyAsISO4217Code;

+ (NSUInteger) iso31661NumericCountryCodeFrom:(NSString*)iso3166Alpha3OrAlpha2;
+ (NSUInteger) isoISO4217CurrencyNumericCodeFrom:(NSString*)currencyAsISO4217Code;
+ (NSUInteger) isoISO4217CurrencyMinorUnitsFrom:(NSString*)currencyAsISO4217Code;

+ (NSString*) expandUnderlyingErrors:(NSError*)error;

+ (NSDecimalNumber*) amountWithoutFraction:(NSDecimalNumber*)amount currencyAsISO4217Code:(NSString*)currencyAsISO4217Code;

+ (NSData*) hexStringToData:(NSString*)hexText error:(NSError**)error;

+(BOOL)unzipFile:(NSString *)filePath toDocsDir:(NSString*)docsDir;

+ (BOOL) shouldAskForPINOnlineCheck:(NSString*)bin serviceCode:(NSString*)serviceCode;
+ (BOOL) hasChipBasedOn:(NSString*)serviceCode;

+(NSString *)getMaskedPANFromTrack2:(NSString *)track2;
-(NSDictionary *)getIssuerInformationFromPAN:(NSString *)pan;
-(NSDictionary *)getIssuerInformationFromPreparedPAN:(NSString *)pan;
-(NSDictionary *)getIssuerByAcceptCardType:(NSString *)acceptCardType;
-(NSDictionary *)getIssuerInformationFromAID:(NSString *)aid;

+(NSString*)getCurrencyStringCodeForLine:(NSString*)line;
+(NSString*)getCountryStringCodeForLine:(NSString*)line;
+(int)getCurrencyDecimalPlaces:(NSString *)currency;

+(NSDecimalNumber *)getDecimalNumberDividerForCurrency:(NSString *)currency;

+ (NSData *)encodeEMVIccBlob:(NSArray *)iccData;

-(NSString*)vendorIDForName:(NSString*)vendorDisplayName andUUID:(NSString*)vendorUUID;

-(BOOL)isVendorHavingBluetoothTerminals:(WDAExtensionTypeUUID)vendorUUID;

+(BOOL)isRequiringSignatureCVMResult:(NSString*)resultCVM;

+ (BOOL) luhnCheck:(NSString *)stringToTest;

+(void)showActivityIndicatorOnView:(UIView *)onView withMessage:(NSString *)message;

+(void)hideActivityIndicator:(UIView *)onView;

+(void)hideActivityIndicator:(UIView *)onView completion:(void (^)(void))moreCompletion;

+(UIImage*)generateQRCodeFromString:(NSString *)qrString;

+(UIImage*)generateBarCode128FromString:(NSString *)stringData;

+(UIImage*)generateBarCodeFromString:(NSString *)stringData filterName:(NSString *)filterName size:(CGSize)size includingText:(BOOL)includeText;

+ (NSDateFormatter *)dateFormatterISO8601;

+ (NSDateFormatter *)dateFormatterISO8601ForRequest;

+ (NSDateFormatter *)dateFormatterISO8601ForStatisticsRequest;

+ (NSDateFormatter *)dateFormatterISO8601Java;

+ (BOOL)isBinFromAMEX:(NSString*)bin;

+ (NSDateFormatter *)dateFormatterForSwitchRequest;

+ (NSString *)getDeviceModel;

+(Class)extensionFromVendor:(WDAExtensionTypeUUID)vendorUUID;
+(NSDate*)getDateFromFormattedString:(NSString *)dateString withFormat:(NSString *)format;
+(NSString *)dateAsString:(NSDate *)date withFormat:(NSString *)format;
+ (NSData *)asEMV:(NSArray *)iccData;

+(BOOL)reversible:(NSDate *)processedByGateway;
+(BOOL)refundable:(NSDate *)processedByGateway;
//+(NSDictionary*)describeObject:(id)obj;
- (NSString*)htmlTemplate:(NSString *)htmlTemplate;
-(NSString*)formatDateWithCurrentLocale:(NSString*)separator;
-(NSString*)formatDate:(NSDate *)date withFormat:(NSString*)withFormat;
-(NSString *)formatDecimalNumber:(NSDecimalNumber*)dn decimalPlaces:(int)decimalPlaces;
-(NSString *)formatDecimalNumber:(NSDecimalNumber*)dn minimumDecimalPlaces:(int)minimumDecimalPlaces maximumDecimalDigits:(int)maximumDecimalDigits;
+ (void)replaceMarkups:(NSMutableString*)strHtml usingMarkupReplacementCallback:(NSString*(^)(NSString*))markupReplacementCallback;

@end

NSString * AcceptGetVersion(NSString *className);
