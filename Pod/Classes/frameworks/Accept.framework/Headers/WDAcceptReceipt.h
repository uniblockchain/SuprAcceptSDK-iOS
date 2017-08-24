//
//  WdAcceptReceipt.h
//  Pods
//
//  Created by Danko, Radoslav on 8/7/14.
//
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 *  @class WDAcceptReceiptAlipayDetails
 *  @brief Receipt content for Alipay payment - to be used by Datecs printer
 **/
@interface WDAcceptReceiptAlipayDetails : NSObject
/**
 */
@property (nullable,nonatomic,strong) UIImage *alipayLogo;
/**
 */
@property (nullable,nonatomic) NSDecimalNumber * transactionAmountCny;
/**
 */
@property (nullable,nonatomic) NSDecimalNumber * exchangeRate;
/**
 */
@property (nullable,nonatomic) NSString * alipayTransactionId;
/**
 */
@property (nullable,nonatomic) NSString * alipayBusinessName;
/**
 */
@property (nullable,nonatomic) NSString * alipayBuyerLoginId;
/**
 */
@property (nullable,nonatomic) NSString * alipayBuyerUserId;
/**
 */
@property (nullable,nonatomic) NSString * terminalId;
/**
 */
@property (nullable,nonatomic) NSString * partnerTransactionId;
/**
 */
@property (nullable,nonatomic) NSString * alipayPayTime;
/**
 */
@end

/**
 *  @class WDAcceptReceiptMerchant
 *  @brief Receipt Merchant Information
 **/
@interface WDAcceptReceiptMerchant : NSObject
/**
 */
@property (nullable,nonatomic,strong) NSString *shopID;
/**
 */
@property (nullable,nonatomic,strong) NSString *merchantName;
/**
 */
@property (nullable,nonatomic,strong) NSString *merchantAddressLine1;
/**
 */
@property (nullable,nonatomic,strong) NSString *merchantAddressLine2;
/**
 */
@property (nullable,nonatomic,strong) NSString *merchantAddressZipCode;
/**
 */
@property (nullable,nonatomic,strong) NSString *merchantAddressCityAndCountry;

@end

/**
 *  @class WDAcceptReceipt
 *  @brief Receipt content for Payment  - to be used by Datecs printer
 **/
@interface WDAcceptReceipt : WDAcceptReceiptMerchant
/**
 */
@property (nullable,nonatomic,strong) NSString *header;
/**
 */
@property (nullable,nonatomic,strong) NSString *merchantIDHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *merchantID;
/**
 */
@property (nullable,nonatomic,strong) NSString *merchantTaxNumber;
/**
 */
@property (nullable,nonatomic,strong) NSString *merchantPhone;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedReceiptDateHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedPaymentDateHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *receiptDate;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedReceiptTimeHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *receiptTime;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedReceiptIDHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedReceiptNumberHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *receiptID;
/**
 */
@property (nullable,nonatomic,strong) NSString *aidHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *aid;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedCardTypeHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *cardType;
/**
 */
@property (nullable,nonatomic,strong) NSString *transactionTypeString;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedTransactionTypeHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedCardNumberHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *cardNumber;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedCardHolderHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *cardHolder;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedExpiryDateHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *expiryDate;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedTerminalIDHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *terminalID;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedApprovalCodeHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *approvalCode;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedAmountHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedAOSAHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *amount;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedTransactionStatusHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *transactionStatus;
/**
 */
@property (nullable,nonatomic,strong) NSArray *paymentItems;
/**
 */
@property (nullable,nonatomic,strong) NSString *taxSummary;
/**
 */
@property (nullable,nonatomic,strong) NSString *tipSummary;
/**
 */
@property (nullable,nonatomic,strong) NSString *serviceChargeSummary;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedPaymentDetailsHeader;
/**
 * Create WDApplicationName custom string value in the Info.plist of your application to appear as "Issued by YOUR_APP_NAME"
 */
@property (nullable,nonatomic,strong) NSString *footer;
/**
 */
@property (nullable,nonatomic,strong) NSString *footerThankYou;
/**
 */
@property (nullable,nonatomic,strong) NSString *footerCopyright;
/**
 */
@property (nullable,nonatomic,strong) NSString *receiptStringToQRCode;
/**
 */
@property (nullable,nonatomic,strong) NSString *receiptStringToBarCode;
/**
 */
@property (nullable,nonatomic,strong) NSString *availableOfflineSpendingAmount;
/**
 */
@property (nonatomic) BOOL verifiedOnDeviceCVM;
/**
 */
@property (nullable,nonatomic,strong) NSString *appCrypt;
/**
 */
@property (nullable,nonatomic,strong) NSString *cryptID;
/**
 */
@property (nullable,nonatomic,strong) NSString *appTransCounter;
/**
 */
@property (nullable,nonatomic,strong) NSString *declinedReason;
/**
 */
@property (nonatomic) BOOL PINVerified;
/**
 */
@property (nullable,nonatomic,strong) NSString *saleTypeAsText;
/**
 */
@property (nonatomic) BOOL isContactless;
/**
 */
@property (nullable,nonatomic,strong) NSString *posEntryModeInterpreted;
/**
 */
@property (nullable,nonatomic,strong) NSString *cashierID;
/**
 */
@property (nullable,nonatomic,strong) NSString *subtotal;
/**
 */
@property (nullable,nonatomic,strong) NSString *tip;
/**
 */
@property (nullable,nonatomic,strong) NSString *serviceCharge;
/**
 */
@property (nullable,nonatomic,strong) NSString *serviceChargeWithTax;
/**
 */
@property (nullable,nonatomic,strong) NSString *discount;
/**
 */
@property (nullable,nonatomic,strong) NSString *voucher;
/**
 */
@property (nullable,nonatomic,strong) NSString *customerCard;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedCashierIDHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedShopIDHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedSubtotalHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedTipHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedServiceChargeHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedServiceChargeWithTaxHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedDiscountHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedVoucherHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedCustomerCardHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedPaymentTypeHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *paymentType;
/**
 */
@property (nullable,nonatomic,strong) UIImage *headerLogo;
/**
 */
@property (nullable,nonatomic, strong) WDAcceptReceiptAlipayDetails *alipayDetails;
@end

/**
 *********************************************
 */

/**
 *  @class WDAcceptZReportCategoryItem
 *  @brief ZReport Category Item
 **/
@interface WDAcceptZReportCategoryItem : NSObject
/**
 */
@property (nonatomic,strong,nonnull) NSString *categoryItemName;
/**
 */
@property (nonatomic,strong,nonnull) NSString *parentCategoryName;
/**
 */
@property (nonatomic,strong,nullable) NSString *netAmount;
/**
 */
@property (nonatomic,strong,nullable) NSString *taxAmount;
/**
 */
@property (nonatomic,strong,nullable) NSString *grossAmount;
/**
 */
@property (nonatomic,strong,nullable) NSString *localisedNetAmount;
/**
 */
@property (nonatomic,strong,nullable) NSString *localisedTaxAmount;
/**
 */
@property (nonatomic,strong,nullable) NSString *localisedGrossAmount;
@end

/**
 *********************************************
 */

/**
 *  @class WDAcceptZReportCategory
 *  @brief ZReport Category
 **/
@interface WDAcceptZReportCategory : NSObject
/**
 */
@property (nonatomic,strong,nonnull) NSString *categoryName;
/**
 */
@property (nonatomic,strong,nullable) NSArray<WDAcceptZReportCategoryItem*>* categoryItems;
@end

/**
*********************************************
*/

/**
 *  @class WDAcceptZReport
 *  @brief ZReport
 **/
@interface WDAcceptZReport : WDAcceptReceiptMerchant
/**
 */
@property (nullable,nonatomic,strong) UIImage *imageReportLogo;
/**
 */
@property (nullable,nonatomic,strong) NSString *shopName;
/**
 */
@property (nullable,nonatomic,strong) NSString *shopAddressLine1;
/**
 */
@property (nullable,nonatomic,strong) NSString *shopAddressLine2;
/**
 */
@property (nullable,nonatomic,strong) NSString *shopAddressZipCode;
/**
 */
@property (nullable,nonatomic,strong) NSString *shopAddressCityAndCountry;
/**
 */
@property (nullable,nonatomic,strong) NSString *merchantTaxNumber;
/**
 */
@property (nullable,nonatomic,strong) NSString *cashRegisterName;
/**
 */
@property (nullable,nonatomic,strong) NSString *zReportId;
/**
 */
@property (nullable,nonatomic,strong) NSString *cashRegisterExternalId;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedZReportId;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedCashRegister;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedRegisterName;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedRegisterExternalId;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedShiftData;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedOpenTime;
/**
 */
@property (nullable,nonatomic,strong) NSString *openTime;
/**
 */
@property (nullable,nonatomic,strong) NSString *currentReportTime;
/**
 */
@property (nullable,nonatomic,strong) NSString *currentReportDate;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedOpenedBy;
/**
 */
@property (nullable,nonatomic,strong) NSString *openedBy;
/**
 */
@property (nullable,nonatomic,strong) NSString *closeTime;
/**
 */
@property (nullable,nonatomic,strong) NSString *closedBy;
/**
 */
@property (nullable,nonatomic,strong) NSString *openingAmount;
/**
 */
@property (nullable,nonatomic,strong) NSString *cashPurchases;
/**
 */
@property (nullable,nonatomic,strong) NSString *cashRefunds;
/**
 */
@property (nullable,nonatomic,strong) NSString *cashOperationsBalance;
/**
 */
@property (nullable,nonatomic,strong) NSString *closingCashBalance;
/**
 */
@property (nullable,nonatomic,strong) NSString *closingActualAmount;
/**
 */
@property (nullable,nonatomic,strong) NSString *overShort;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedCloseTime;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedClosedBy;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedOpeningAmount;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedCashPurchases;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedCashRefunds;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedCashOperationsBalance;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedCashOperationsBalanceLine2;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedClosingCashBalance;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedClosingCashBalanceLine2;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedClosingActualAmount;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedOverShort;
/**
 */
@property (nullable,nonatomic,strong) NSArray<WDAcceptZReportCategory*>* categories;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedPaymentMethods;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedEnds;
@end
