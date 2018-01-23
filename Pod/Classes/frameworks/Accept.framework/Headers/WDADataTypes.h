//
//  WDADataTypes.h
//  acceptSDK
//
//  Created by Danko, Radoslav on 22/10/15.
//  Copyright © 2015 Wirecard. All rights reserved.
//

#ifndef WDA_DATA_TYPES
#define WDA_DATA_TYPES

#import <UIKit/UIKit.h>
#import "WDAcceptReceipt.h"
#import "WDAcceptProductCatalogue.h"
#import "WDAcceptPaymentRequestCoupon.h"
#import "WDAcceptPaymentRequestCard.h"
#import "WDAcceptPaymentRequestCash.h"
#import "WDAcceptPaymentRequestAlipay.h"
#import "WDAcceptPaymentRequestWeChat.h"
#import "WDAcceptPaymentDetailCard.h"
#import "WDAcceptPaymentDetailCoupon.h"
#import "WDAcceptPaymentDetailWeChat.h"
#import "WDAcceptPaymentDetailAlipay.h"
#import "WDAcceptPaymentDetail.h"
#import "WDAcceptObject.h"
//#import <Accept/Accept-Swift.h>

//#import "WDAcceptSale.h"

@class WDAcceptSaleRequest, WDAcceptSale, WDAcceptSaleResponse;

@class WDAcceptCashRegister;

#define kStarMicronicsModelName @"CB2002" //This is the actual model name of the Star Micronics drawer with no printer within

#define WDAVariableName(arg) (@""#arg)
#define kWDAMissingInputText @"Missing input: %@ variable cannot be nil."
#define WDAOptionsHasValue(options, value) (((options) & (value)) == (value))

#define WDAOBJC_STRINGIFY(x) @#x

NS_ASSUME_NONNULL_BEGIN

#pragma mark - Enumerations

/**
 *  @typedef AcceptUpdateSeverity
 *  @brief Enumerator of severities for a update to be applied to a terminal
 **/
typedef NS_ENUM(NSInteger, AcceptUpdateSeverity ) {
    /// Mandatory firmware update to be applied asap (Miura) "A"
    AcceptUpdateSeverityMandatory,
    /// Mandatory firmware update that allows only one more transaction before forcing it (Miura) "B"
    AcceptUpdateSeverityNextMandatory,
    /// Non mandatory firmware, or no new firmware at all. No need to inform or trigger the update (Miura and Spire) "C"
    AcceptUpdateSeverityOptional,
    /// Firmware update to be applied at user's earliest convenience - client application should prompt for a manual installation repeatedly (Spire) "D"
    AcceptUpdateSeverityNotifyMandatory
};

/**
 *  @typedef WDAExtensionTypeUUID
 *  @brief Enumerator of supported terminal extensions
 **/
typedef NS_ENUM(NSInteger, WDAExtensionTypeUUID ) {
        WDAExtensionNoneUUID = -1,
        WDAExtensionUUID = 0,
        WDAPosMateExtensionUUID,
        WDAEmvSwipeExtensionUUID,
        WDAUnimagExtensionUUID,
        WDADatecsExtensionUUID,
        WDAAirPrintExtensionUUID,
        WDADatecsPrinterExtensionUUID,
        WDAMPOPExtensionUUID,
        WDAStarMicronicsExtensionUUID,
        WDAMiuraExtensionUUID,
        WDAPaxExtensionUUID,
        WDASocketExtensionUUID,
        WDAWisepadExtensionUUID
};


/**
 *  @typedef AcceptStateUpdate
 *  @brief Enumerator of statuses for informing the flow status or asking feedback to the user, received in the progress block of Pay function.
 **/
typedef NS_ENUM(NSInteger, AcceptStateUpdate ) {
    AcceptStateConfigurationProgressTerminalNotReady = -1,
    AcceptStateWaitingForPlugIn = 0,
    AcceptStateWaitingForSwipe,
    AcceptStateDamagedChipAndWaitingForSwipe,
    AcceptStateProcessingData,
    AcceptStateOnlineProcessingData,
    AcceptStateFollowTerminalInstructions,
    AcceptStateInitialize,
    AcceptStateTerminalConfigOngoing,
    AcceptStateInsertOrSwipeCard,
    AcceptStateTapOrInsertOrSwipeCard,    
    AcceptStateWaitingForInsertCard, //10
    AcceptStateCheckingCard,
    AcceptStateRemoveCard,
    AcceptStateCardRemoved,
    AcceptStateConfirmAmount,
    AcceptStateAmountConfirmed,
    AcceptStatePINEntered,
    AcceptStateCorrectPIN, //deprecated
    AcceptStatePINEntryLastTry,
    AcceptStateAskingForPIN,
    AcceptStatePinEntryWrong, //deprecated //20
    AcceptStateCardholderSignatureCheck,
    AcceptStateTerminalRestarting,
    AcceptStateGratuityEntryStarted,
    AcceptStateApplicationSelectionStarted,
    AcceptStateApplicationSelectionFinished,
    AcceptStateFollowInstructionsOnConsumerDevice, //on device CVM for contactless
    AcceptStateScanInitialisation,
    AcceptStateScanBarcode,
    AcceptStateScanFinished,
    
    AcceptStateConfigurationProgressUpdateWillStart=1000,//the below matches with AcceptUpdateConfigurationProgressUpdate enum
    AcceptStateConfigurationProgressDownloading,
    AcceptStateConfigurationProgressUnzipping,
    AcceptStateConfigurationProgressUploading,
    AcceptStateConfigurationProgressDeferredInstall
};


/**
 *  @typedef AcceptTaxationType
 *  @brief Enumerator with the taxation types.
 **/
typedef NS_ENUM(NSInteger, AcceptTaxationType ) {
    AcceptTaxationTypeGross = 0,
    AcceptTaxationTypeNet = 1
};

/**
 *  @typedef AcceptCashierPinValidationResult
 *  @brief Enumerator with the Pin validation results.
 **/
typedef NS_ENUM(NSInteger, AcceptCashierPinValidationResult ) {
    AcceptCashierPinValidationResultInvalid,
    AcceptCashierPinValidationResultValid,
    AcceptCashierPinValidationResultLocked,
    AcceptCashierPinValidationResultUnknown
};

/**
 *  @typedef AcceptSaleCompletionOperation
 *  @brief Enumerator with the Sale completion operation types.
 **/
typedef NS_ENUM(NSInteger, AcceptSaleCompletionOperation ) {
    AcceptSaleCompletionOperationConfirm,
    AcceptSaleCompletionOperationCancel
};

/**
 *  @typedef AcceptReversalReason
 *  @brief Enumerator with the reversal reasons
 **/
typedef NS_ENUM(NSInteger, AcceptReversalReason)
{   AcceptReversalReasonUndefined = -1,
    AcceptReversalReasonSignatureDeclined = 0,
    AcceptReversalReasonAdviceUnsupported = 1,
    AcceptReversalReasonCardDeclined=2,
    AcceptReversalReasonCaptureUnsupported=4,
    AcceptReversalReasonNoEFTResponse = 6,
    AcceptReversalReasonTerminalTerminated=7,
    AcceptReversalReasonSignatureVerificationTimeout = 10,
    AcceptReversalReasonOfflineDeclined = 11,
    AcceptReversalReasonUserCanceled = 12
//    AcceptReversalReasonGatewayDeclined = 13
};

/**
 *  @typedef AcceptExtensionConnectionStatus
 *  @brief The terminal connection status enumerator
 **/
typedef NS_ENUM(NSInteger, AcceptExtensionConnectionStatus){
    AcceptExtensionConnectionStatusDisconnected,
    AcceptExtensionConnectionStatusConnected,
    AcceptExtensionConnectionStatusUnknown,
    AcceptExtensionConnectionStatusConnecting
};

/**
 *  @typedef AcceptPrinterStateUpdate
 *  @brief Enumerator with the statuses of the printing flow, received in progress block of print.
 **/
typedef NS_ENUM(NSInteger, AcceptPrinterStateUpdate ) {
    AcceptPrinterStateInitialize = 0,
    AcceptPrinterStateConnecting,
    AcceptPrinterStateConnected,
    AcceptPrinterStatePrint,
    AcceptPrinterStateFinish
};

/**
 *  @typedef AcceptPrinterPaperStatus
 *  @brief Enumerator with the status of the paper amount.
 **/
typedef NS_ENUM(NSInteger, AcceptPrinterPaperStatus ) {
    AcceptPrinterStatusUnknown = 0,
    AcceptPrinterStatusNotSupported,
    AcceptPrinterStatusReady,
    AcceptPrinterStatusNearEmpty,
    AcceptPrinterStatusEmpty
};

/**
 *  @typedef AcceptUpdateConfigurationProgressUpdate
 *  @brief Enumerator with the progress during the terminal config file update
 **/
typedef NS_ENUM(NSInteger, AcceptUpdateConfigurationProgressUpdate) {
    AcceptUpdateConfigurationProgressTerminalNotReady = -1,
    AcceptUpdateConfigurationProgressUpdateWillStart=1000,
    AcceptUpdateConfigurationProgressDownloading,
    AcceptUpdateConfigurationProgressUnzipping,
    AcceptUpdateConfigurationProgressUploading,
    AcceptUpdateConfigurationProgressDeferredInstall
} ;

/**
 *  @typedef AcceptUpdateConfigurationStatus
 *  @brief Enumerator with the status during the terminal config file update
 **/
typedef NS_ENUM(NSInteger, AcceptUpdateConfigurationStatus) {
    AcceptUpdateConfigurationStatusTerminalDoesNotSupportUpdates,
    AcceptUpdateConfigurationStatusSuccess,
    AcceptUpdateConfigurationStatusUnnecessary,
    AcceptUpdateConfigurationStatusConfigurationDoesNotExist,
    AcceptUpdateConfigurationStatusFailure
} ;

/**
 *  @typedef AcceptSignatureVerificationResult
 *  @brief Enumerator with the result of the merchant verification
 **/
typedef NS_ENUM(NSInteger, AcceptSignatureVerificationResult)
{
    AcceptSignatureVerificationResultNotDefined = 0,
    AcceptSignatureVerificationResultApproved = 1,
    AcceptSignatureVerificationResultRejected = 2
};


/**
 *  @typedef AcceptPaymentConfirmationType
 *  @brief Enumerator with the type of the merchant payment confirmation
 **/
typedef NS_ENUM(NSInteger, AcceptPaymentConfirmationType)
{
    AcceptPaymentConfirmationTypeSignature = 0,
    AcceptPaymentConfirmationTypeAlipayPassword = 1,
    AcceptPaymentConfirmationTypeWeChatPassword = 2
};

/**
 *  @typedef AcceptPaymentConfirmationResult
 *  @brief Enumerator with the result of the merchant payment confirmation
 **/
typedef NS_ENUM(NSInteger, AcceptPaymentConfirmationResult)
{
    AcceptPaymentConfirmationResultRejected = 0,
    AcceptPaymentConfirmationResultApproved = 1
    
};


/**
 *  @typedef AcceptTerminalUpdateType
 *  @brief Enumerator of terminal update types
 **/
typedef NS_ENUM(NSInteger, AcceptTerminalUpdateType ) {
    AcceptTerminalUpdateTypeConfiguration,
    AcceptTerminalUpdateTypeFirmware,
    AcceptTerminalUpdateTypeApplication,
    AcceptTerminalUpdateTypeCAKeys
};

/**
 *  @typedef AcceptTerminalUpdateTypeMask
 *  @brief These constants are mask bits for specifying the terminal update type
 **/
typedef enum AcceptTerminalUpdateTypeMask : NSUInteger {
    AcceptTerminalUpdateTypeMaskConfiguration = (1 << AcceptTerminalUpdateTypeConfiguration),
    AcceptTerminalUpdateTypeMaskFirmware = (1 << AcceptTerminalUpdateTypeFirmware),
    AcceptTerminalUpdateTypeMaskApplication = (1 << AcceptTerminalUpdateTypeApplication),
    AcceptTerminalUpdateTypeMaskCAKeys = (1 << AcceptTerminalUpdateTypeCAKeys),
    AcceptTerminalUpdateTypeMaskSoftware = (AcceptTerminalUpdateTypeMaskFirmware | AcceptTerminalUpdateTypeMaskApplication),
    AcceptTerminalUpdateTypeMaskAll = (AcceptTerminalUpdateTypeMaskFirmware | AcceptTerminalUpdateTypeMaskApplication | AcceptTerminalUpdateTypeMaskConfiguration)
} AcceptTerminalUpdateTypeMask;

/**
 *  @typedef AcceptResultStatus
 *  @brief Enumerator with common response statuses
 **/
typedef NS_ENUM(NSInteger, AcceptResultStatus)
{
    AcceptResultStatusUnknown =0,
    AcceptResultStatusOK = 200,
    AcceptResultStatusCreated = 201,
    AcceptResultStatusUnauthorized = 401,
    AcceptResultStatusForbidden = 403,
    AcceptResultStatusNotFound = 404,
    AcceptResultStatusPasswordValidationFailure = 5000,
    AcceptResultStatusPasswordCriteriaNotMet = 5435
};



/**
 *  @typedef AcceptExtensionBatteryStatus
 *  @brief Enumerator with the battery status.
 **/
typedef NS_ENUM(NSInteger, AcceptExtensionBatteryStatus ) {
    AcceptExtensionBatteryStatusCharging = -3,
    AcceptExtensionBatteryStatusNoResponse = -2,
    AcceptExtensionBatteryStatusUnsupported = -1
};

/** 
 * @typedef AcceptQuerySort
 *  @brief Enumerator with the order by for sort.
 */
typedef NS_ENUM(NSUInteger, AcceptQuerySort) {
    /**
     */
    AcceptQuerySortDescending=0,
    /**
     */
    AcceptQuerySortAscending=1

};

/** 
 * @typedef AcceptSaleQueryOrderBy
 *  @brief Enumerator with order by for transaction queries
 */
typedef  NS_ENUM(NSUInteger,AcceptSaleQueryOrderBy) {
    /**
     */
    AcceptSaleQueryOrderByCreatedAt=0,
    /**
     */
    AcceptSaleQueryOrderByAmount,
    /**
     */
    //AcceptSaleQueryOrderByName //Switch does not support cardholdername sorting
} ;

/**
 * @typedef AcceptShiftQueryOrderBy
 *  @brief Enumerator with order by for Shift queries
 */
typedef  NS_ENUM(NSUInteger,AcceptShiftQueryOrderBy) {
    AcceptShiftQueryOrderByOpenTime=0,
    AcceptShiftQueryOrderByOpeningAmount
} ;


/**
 *  @typedef AcceptStatisticPeriod
 *  @brief Enumerator with the Statistic reporting Period
 **/
typedef NS_ENUM(NSUInteger, AcceptStatisticPeriod){
    AcceptStatisticPeriodUndefined,
    AcceptStatisticPeriodDay,
    AcceptStatisticPeriodWeek,
    AcceptStatisticPeriodMonth,
    AcceptStatisticPeriodQuarter,
    AcceptStatisticPeriodYear
};

/**
 *  @typedef AcceptStatisticGroupBy
 *  @brief Enumerator with the Statistic Grouping criteria
 **/
typedef NS_ENUM(NSUInteger, AcceptStatisticGroupBy){
    AcceptStatisticGroupByUndefined,
    AcceptStatisticGroupByType,
    AcceptStatisticGroupByStatus,
    AcceptStatisticGroupByCardBrand
};

/**
 *  @typedef AcceptStatisticStatuses
 *  @brief Enumerator with the Statistic Grouping criteria
 **/
typedef NS_ENUM(NSUInteger, AcceptStatisticStatus)
{
    AcceptStatisticStatusUndefined,
    AcceptStatisticStatusCompleted,
    AcceptStatisticStatusReturned,
    AcceptStatisticStatusCanceled
};

/**
 *  @typedef AcceptPrintFormat
 *  @brief Enumerator with the Accept Print format
 **/
typedef NS_ENUM(NSUInteger, AcceptPrintFormat)
{
    AcceptPrintFormatHTML,
    AcceptPrintFormatPDF,
    AcceptPrintFormatUIImage,
    AcceptPrintFormatDatecs,
    AcceptPrintFormatWisepad
};

/**
 *  @typedef AcceptPrintDpi
 *  @brief Enumerator with the Accept Print DPI
 **/
typedef NS_ENUM(NSUInteger, AcceptPrintDpi)
{
    AcceptPrintDpiDefault=306,
    AcceptPrintDpiMpop=384,
    AcceptPrintDpiStarMicronics=576
};

/**
 *  @typedef AcceptSaleType
 *  @brief Enumerator with the Sale types.
 **/
typedef NS_ENUM(NSInteger, AcceptSaleType ) {
    AcceptSaleTypePurchase,
    AcceptSaleTypeReturn,
    AcceptSaleTypeUnknown
};

/**
 *  @typedef AcceptSaleState
 *  @brief Sale Status enumeration
 **/
typedef NS_ENUM(NSUInteger, AcceptSaleState) {
    AcceptSaleStateUnknown=0,
    AcceptSaleStateInProgress,
    AcceptSaleStateUnconfirmed,
    AcceptSaleStateCompleted,
    AcceptSaleStateReturned,
    AcceptSaleStateCanceled,
    AcceptSaleStateFailed,
    AcceptSaleStateFailedIntervene,
    AcceptSaleStateFailedInconsistent,
    AcceptSaleStateCancelIncomplete,
    AcceptSaleStateAuthorized,
    AcceptSaleStateIncomplete
};

/**
 *  @typedef AcceptBarcodeSymbology
 *  @brief Barcode symbologies (standards) enumeration
 **/
typedef NS_ENUM(NSUInteger, AcceptBarcodeSymbology) {
    AcceptBarcodeSymbologyUnknown = 0,
    AcceptBarcodeSymbologyUPCE,
    AcceptBarcodeSymbologyUPCA,
    AcceptBarcodeSymbologyEAN8,
    AcceptBarcodeSymbologyEAN13,
    AcceptBarcodeSymbologyCode39,
    AcceptBarcodeSymbologyITF,
    AcceptBarcodeSymbologyCode128,
    AcceptBarcodeSymbologyCode93,
    AcceptBarcodeSymbologyCodabar,
    AcceptBarcodeSymbologyAztec,
    AcceptBarcodeSymbologyDataMatrix,
    AcceptBarcodeSymbologyPDF417,
    AcceptBarcodeSymbologyQRCode
};

#pragma mark - Response Callbacks
@class AcceptTransaction,WDAcceptExtendedProcessingInfo;

/**
 *  @typedef SignatureCollectedResponse
 *  @brief Callback to return collected signature back to the payment process
 *  @param collectedSignature signature image
 **/
typedef void (^SignatureCollectedResponse)(UIImage* _Nullable collectedSignature, NSError* _Nullable error);

/**
 *  @typedef PaymentCardApplicationSelectionResponse
 *  @brief Callback to return collected signature back to the payment process
 *  @param selectedApplication index of the selected card application
 **/
typedef void(^PaymentCardApplicationSelectionResponse)(NSUInteger selectedApplication);

/**
 *  @typedef SaleQueryResponse
 *  @brief Callback to return sales
 *  @param sales sales response block
 **/
typedef void(^SaleQueryResponse)(NSArray <WDAcceptSaleResponse *>* _Nullable sales, NSError* _Nullable error);

/**
 *  @typedef DeviceConnectionStatusCompletion
 *  @brief The callback to report the device connections status
 *  @param connectionStatus the connection status
 **/
typedef void (^DeviceConnectionStatusCompletion)(AcceptExtensionConnectionStatus connectionStatus);

/**
 *  @typedef BatteryLevelCallback
 *  @brief The callback to report the battery level
 **/
typedef void (^BatteryLevelCallback)(NSInteger);

/**
 *  @typedef ExtensionCommandCompletion
 *  @brief The callback to report the extension command status
 *  @param commandCompletionStatus the extension command SUCCESS
 *  @param error the extension command error
 **/
typedef void (^ExtensionCommandCompletion)(BOOL commandCompletionStatus,  NSError * _Nullable error);

/**
 *  @typedef ZReportCompletion
 *  @brief Callback to return created Z-Report
 *  @param report created report
 *  @param error error when creating report
 **/
typedef void(^ZReportCompletion)(id _Nullable report, NSError* _Nullable error);

/**
 *  @typedef ReceiptCompletion
 *  @brief Callback to return created receipt
 *  @param receipts array of created receipts - in the case of WDAcceptReceipt printing of All receipts (e.g. Original + Refunds) there can be multiple of receipts to be printed
 *  @param error error when creating receipt
 **/
typedef void(^ReceiptCompletion)(NSArray* _Nullable receipts, NSError* _Nullable error);


#pragma mark - Classes
/**
 *  @class WDAcceptVendor
 *  @brief Vendor information
 **/
@interface WDAcceptVendor : WDAcceptObject <NSCoding, NSCopying>
/**
 */
@property (nonatomic) WDAExtensionTypeUUID  vendorUUID;
/**
 */
@property (nonatomic, strong) NSString * _Nonnull displayName;
/**
 */
@property (nonatomic, strong) NSString * _Nullable alternativeDisplayName;
@end
/**
 *  @class WDAcceptTerminal
 *  @brief Terminal information
 **/
@interface WDAcceptTerminal : WDAcceptObject <NSCoding, NSCopying>
/**     
 */
@property (nonatomic, strong) WDAcceptVendor * _Nonnull terminalVendor;
/**
 */
@property (nonatomic, strong) NSString * _Nonnull terminalModel;
/**
 * @brief terminal model as reported by EAAccessory
 */
@property (nonatomic, strong) NSString * _Nonnull eaAccessoryModel;
/**
 */
@property (nonatomic, strong) NSString * _Nonnull terminalUUID;
/**
 * @brief configurable through paymentMethods.xml
 */
@property (nonatomic, strong) NSString * _Nonnull displayName;
/**
 */
@property (nonatomic, strong) NSString * _Nonnull firmwareVersion;
/**
 */
@property (nonatomic) BOOL  connected;
@end

/**
 *  @class WDAcceptPaymentConfig
 *  @brief Payment configuration class. Content required to execute the payment flow
 **/
@interface WDAcceptPaymentConfig : NSObject
/**
 *  @brief Payment Configuration
 *  @param sale Sale Request
 *  @param allowGratuity Terminal to ask for gratuity during the payment flow
 *  @return Payment configuration - to be used in Sale Manager to perform the payment
 **/
-(instancetype)initWithSaleRequest:(WDAcceptSaleRequest *)sale
              allowGratuity:(BOOL)allowGratuity;
@property (nonatomic, strong) WDAcceptSaleRequest * _Nonnull sale;
@property (nonatomic) BOOL allowGratuity;
@end


/**
 *  @class WDAcceptSignatureRequest
 *  @brief Used by extension to notify the Payment Flow that the Signature needs to be collected.
 *              Extension supplies card holder information to be displayed if necessary
 **/
@interface WDAcceptSignatureRequest: NSObject
/**
 */
@property (nonatomic, strong) NSString * _Nullable cardHolderName;
/**
 */
@property (nonatomic, strong) NSString * _Nullable cardNumber;
/**
 */
@property (nonatomic, strong) NSString *  _Nullable cardType;
/**
 */
@property (nonatomic, strong) NSString *  _Nullable issuer;
/**
 */
@property (nonatomic, strong) NSString * _Nullable maskedPAN;
/**
 */
@property (nonatomic) NSNumber *gratuityAmount;
/**
 *@discussion sendCollectedSignature - callback to Extension once the Payment Flow signalls the Approval/Rejection of the signature
 *                                It is used on the client side to confirm the signature validity
 *                                *If nil* then extension awaits the confirmation of the signature - e.g. by pressing the terminal buttons
 *                                *If NOT nil* then terminal does not have buttons and confirmation must be handled by the client application
 *                                  (presenting the OK/Cancel buttons to confirm the signature validity)
 */
@property (nonatomic, copy) SignatureCollectedResponse  _Nonnull sendCollectedSignature;
@end

/**
 *  @class WDAcceptAppSelectionRequest
 *  @brief Used by the extension to notify the Payment Flow that the ICC application selection is to be performed by the client app
 *
 **/
@interface WDAcceptAppSelectionRequest: NSObject
/**
 * @brief ICC applications list as retrieved from the card chip
 */
@property (nonatomic, strong) NSArray * _Nullable appsArray;
/**
 * @brief callback to be performed by the client app once ICC application is selected
 */
@property (nonatomic, copy) PaymentCardApplicationSelectionResponse _Nonnull selectCardApplication;
@end

/**
 *  @class WDAcceptPrinterConfig
 *  @brief Printer configuration class. Receipt Content or Receipt Image required to execute the printing flow
 **/
@interface WDAcceptPrinterConfig : NSObject
/**
 *  @brief Printer configuration to perform the printing
 *  @param printer Printer to use for printing
 *  @param printJobs Printing jobs
 *  @return Printer configuration
 **/
-(instancetype)initWithPrinter:(WDAcceptTerminal *)printer
                     printJobs:(NSArray *)printJobs;
///Device to print the receipt on
@property (nonatomic, strong) WDAcceptTerminal *  _Nonnull printer;
/// printJobs to print where its type is one of WDAcceptReceipt | WDAcceptZReport | UIImage
@property (nonatomic, strong) NSArray * printJobs;
@end

/**
 *  @class WDAcceptProductImage
 *  @brief Product Image information
 **/
@interface WDAcceptProductImage : NSObject
/**
 */
@property (nonatomic, strong) NSString *  _Nonnull productId;
/**
 */
@property (nonatomic, strong) NSError * _Nullable error;
/**
 */
@property (nonatomic, strong) NSString * _Nullable imagePath;
@end

/**
 *  @class WDAcceptSaleItem
 *  @brief  Payment item info
 **/
//@interface AcceptSaleItem : NSObject
///**
// */
//@property (nonatomic, strong) NSString * _Nullable itemDescription;
///**
// */
//@property (nonatomic, strong) NSDecimalNumber * _Nonnull unitPrice;
///**
// */
//@property (nonatomic) NSInteger quantity;
///**
// */
//@property (nonatomic, strong) NSDecimalNumber * _Nonnull unitTax;
///**
// */
//@property (nonatomic, strong) NSDecimalNumber * _Nonnull itemTotal;
///**
// */
//@property (nonatomic) AcceptSaleItemType itemType;
///**
// */
//-(NSDecimalNumber *)totalUnitPrice;
//@end

/**
 *  @class WDAcceptSaleStatistics
 *  @brief  Transaction Statistics
 **/
@interface WDAcceptSaleStatistics : NSObject
/**
 */
@property (nullable, nonatomic, strong) NSDecimalNumber *avgAmount;
/**
 */
@property (nullable, nonatomic, strong) NSDecimalNumber *maxAmount;
/**
 */
@property (nullable, nonatomic, strong) NSDecimalNumber *minAmount;
/**
 */
@property (nullable, nonatomic, strong) NSDecimalNumber *transactionCount;
/**
 */
@property (nullable, nonatomic, strong) NSDecimalNumber *turnover;
/**
 */
@property (nullable, nonatomic, strong) NSString *cardBrand;
/**
 */
@property (nullable, nonatomic, strong) NSString *period;
/**
 */
@property (nonatomic) AcceptTransactionType type;
/**
 */
@property (nonatomic) AcceptSaleState status;

-(NSDate *)date;
@end

/**
 *  @class WDAcceptRemindUsername
 *  @brief  Remind username object to be used with credential management API
 **/
@interface WDAcceptRemindUsername : NSObject
/**
 *  @brief Remind Username by Email
 *  @param email Email address to which to send the Username reminder
 *  @return new Remind Username
 **/
-(instancetype)initWithEmail:(NSString *)email;
/**
 */
@property (nullable, nonatomic, retain) NSString *email;
/**
 */
@property (nullable, nonatomic, retain) NSString *phone;
@end

/**
 *  @class WDAcceptRequestPasswordReset
 *  @brief  Request Reset Password object to be used with credential management API
 **/
@interface WDAcceptRequestPasswordReset : NSObject
/**
 *  @brief Reset Password for a user
 *  @param username Username for which to send the Password reset instructions
 *  @return new Reset Password
 **/
-(instancetype)initWithUsername:(NSString *)username;
/**
 */
@property (nullable, nonatomic, retain) NSString *username;
/**
 */
@property (nullable, nonatomic, retain) NSString *phone;
@end

/**
 *  @class WDAcceptChangePassword
 *  @brief  Change Password object to be used with credential management API
 **/
@interface WDAcceptChangePassword : NSObject
/**
 *  @brief Change Password for a current user
 *  @param oldPassword Current user password
 *  @param newPassword New user password
 *  @return new Change Password
 **/
-(instancetype)initWithOldPassword:(NSString *)oldPassword
                       newPassword:(NSString *)newPassword;
/**
 */
@property (nullable, nonatomic, retain) NSString *currentPassword;
/**
 */
@property (nullable, nonatomic, retain) NSString *theNewPassword;
@end

/**
 *  @class WDAcceptQuery
 *  @brief  Generic Query attributes
 **/
@interface WDAcceptQuery : NSObject
/**
 *  @brief Basic Accept Query attributes used for query request
 *  @param page Page to obtain from sorted results
 *  @param pageSize Size of the Page from sorted results
 *  @return new Accept Query
 **/
-(instancetype)initWithPage:(NSUInteger)page
                   pageSize:(NSUInteger)pageSize;
/// Page to retrieve
@property (nonatomic) NSUInteger page;
/// Page size
@property (nonatomic) NSUInteger pageSize;
@end

/**
 *  @class WDAcceptSalesQuery
 *  @brief Transaction query class used in payment searches
 **/
@interface WDAcceptSalesQuery : WDAcceptQuery
/**
 *  @brief Sales Query attributes used for query request
 *  @param page Page to obtain from sorted results
 *  @param orderBy results ordered by
 *  @param orderSort results sorted ascending/descending
 *  @param statuses Sale Statuses to query for
 *  @param saleTypes Sale Types to query for
 *  @return new Sales Query
 **/
-(instancetype)initWithPage:(NSUInteger)page
                   pageSize:(NSUInteger)pageSize
                    orderBy:(AcceptSaleQueryOrderBy)orderBy
                  orderSort:(AcceptQuerySort)orderSort
                   statuses:(NSArray <NSNumber*>*)statuses
                  saleTypes:(NSArray <NSNumber*>*)saleTypes;
/**
 * If not specified then current merchant Sale query  is performed
 * System Admin can perform Sale query on any merchant
 **/
@property (nonatomic, strong) NSString * _Nullable merchantId;
/**
 */
@property (nonatomic, strong) NSString *  _Nullable fullTextSearch;
/**
 */
@property (nonatomic, strong) NSDecimalNumber *  _Nullable amount;
/**
 */
@property (nonatomic, strong) NSString *  _Nullable cardNumber;
/**
 */
@property (nonatomic, strong) NSString *  _Nullable receiptId;
/**
 */
@property (nonatomic, strong) NSString *  _Nullable gatewayReference;
/**
 */
@property (nonatomic, strong) NSString *  _Nullable saleId;
/**
 */
@property (nonatomic, strong) NSString *  _Nullable originalSaleId;
/**
 * @brief saleTypes is an array of one or many of AcceptSaleType enumeration
 */
@property (nonatomic, strong) NSArray <NSNumber*>* _Nullable saleTypes;
/**
 * start interval for sale initialisation date
 */
@property (nonatomic, strong) NSDate *  _Nullable initializedFrom;
/**
 * end interval for sale initialisation date 
 */
@property (nonatomic, strong) NSDate *  _Nullable initializedTo;
/**
 * @brief statuses is an array of one or many of AcceptSaleState enumeration
 */
@property (nonatomic, strong) NSArray <NSNumber*>*  _Nullable statuses;
/**
 */
@property (nonatomic) AcceptQuerySort orderSort;
/**
 */
@property (nonatomic) AcceptSaleQueryOrderBy orderBy;
@end

/**
 *  @class WDAcceptStatisticsQuery
 *  @brief Transaction query class used in payment searches
 **/
@interface WDAcceptStatisticsQuery : NSObject
/**
 *  @brief Statistics Query attributes used for query request
 *  @param merchantId Merchant for whom to obtain the statistics
 *  @param from Date from - Sale processed date
 *  @param to Date to - Sale processed date
 *  @param status Sale Status
 *  @param period Statistics period
 *  @param currency Sales Currency
 *  @return new Statistics Query
 **/
-(instancetype)initWithMerchantId:(NSString *)merchantId
                            from:(NSDate *)from
                              to:(NSDate *)to
                           status:(AcceptStatisticStatus)status
                           period:(AcceptStatisticPeriod)period
                         currency:(NSString *)currency;
/**
 * The merchant for whom to perform the Sale statistics
 **/
@property (nonatomic, strong) NSString * _Nonnull merchantId;
/// Sale Statuses - grouping criteria
@property (nonatomic) AcceptStatisticStatus status;
/// Statistics Period
@property (nonatomic) AcceptStatisticPeriod period;
/**
 * start interval for transaction processing date
 */
@property (nonatomic, strong) NSDate * _Nonnull processedFrom;
/**
 * start interval for transaction processing date
 */
@property (nonatomic, strong) NSDate * _Nonnull processedTo;
/// Sales currency code
@property (nonatomic, strong) NSString * _Nonnull currency;
@end

/**
 *  @class WDAcceptProductsQuery
 *  @brief Products query class used in product searches
 **/
@interface WDAcceptProductsQuery : WDAcceptQuery
/**
 *  @brief Product Query attributes used for generic query request
 *  @param page Page to obtain from sorted results
 *  @param pageSize Size of the Page from sorted results
 *  @param catalogueId Product Catalogue Id to be queried
 *  @return new Product Query attributes
 **/
-(instancetype)initWithPage:(NSUInteger)page
                   pageSize:(NSUInteger)pageSize
                catalogueId:(NSString *)catalogueId;
/**
 *  @brief Product Query attributes used to query specific Product
 *  @param page Page to obtain from sorted results
 *  @param pageSize Size of the Page from sorted results
 *  @param catalogueId Product Catalogue Id to be queried
 *  @param productId Product Id to be queried
 *  @return new Product Query attributes
 **/
-(instancetype)initWithPage:(NSUInteger)page
                   pageSize:(NSUInteger)pageSize
                catalogueId:(NSString *)catalogueId
                  productId:(NSString *)productId;

/**
 *  @brief Product Query attributes used to query specific Product
 *  @param page Page to obtain from sorted results
 *  @param pageSize Size of the Page from sorted results
 *  @param catalogueId Product Catalogue Id to be queried
 *  @param categoryId Category Id to be queried
 *  @return new Product Query attributes
 **/
-(instancetype)initWithPage:(NSUInteger)page
                   pageSize:(NSUInteger)pageSize
                catalogueId:(NSString *)catalogueId
                  categoryId:(NSString *)categoryId;

/**
 *  @brief Product Query attributes used for Product Changes query request
 *  @param catalogueId Product Catalogue Id to be queried
 *  @param date get Product Changes since this date
 *  @return new Product Query attributes
 **/
-(instancetype)initWithCatalogueId:(NSString *)catalogueId
                              date:(NSDate *)date;

/**
 *  @brief Product Query attributes used to query specific Product Image
 *  @param catalogueId Product Catalogue Id to be queried
 *  @param productId Product Id to be queried
 *  @return new Product Query attributes
 **/
-(instancetype)initWithCatalogueId:(NSString *)catalogueId
                         productId:(NSString *)productId;
/**
 */
@property (nonatomic, strong, nonnull) NSString * productCatalogueId;
/**
 */
@property (nonatomic, strong,nullable) NSString * productId;
/**
 */
@property (nonatomic, strong,nullable) NSString * externalId;
/**
 */
@property (nonatomic, strong,nullable) NSString * productName;
/**
 */
@property (nonatomic, strong,nullable) NSString * barcodeValue;
/**
 */
@property (nonatomic, strong,nullable) NSString * productCategoryName;
/**
 */
@property (nonatomic, strong,nullable) NSString * productCategoryId;
/**
 */
@property (nonatomic, strong,nullable) NSDate * dateToLookForChanges;
/**
 */
@property (nonatomic) BOOL sortAscending;
@end

/**
 *  @class WDAcceptTerminalHardwareInformation
 *  @brief Terminal Hardware information - firmware version, configuration version, serial number
 **/
@interface WDAcceptTerminalHardwareInformation : WDAcceptObject <NSCoding>
/**
 * terminal serial number
 */
@property (nonatomic, strong, nullable) NSString * serial;
/**
 * firmware version - OS
 */
@property (nonatomic, strong, nullable) NSString * firmwareVersion;
/**
 * application version - MPI
 */
@property (nonatomic, strong, nullable) NSString * applicationVersion;
/**
 * in the case the configuration was uploaded to the terminal the configuration version will be appended later by SDK
 */
@property (nonatomic, strong, nullable) NSString * configVersion;
@end

/**
 *  @class WDAcceptResult
 *  @brief  Result object for credential management API
 **/
@interface WDAcceptResult : NSObject
@property (nullable, nonatomic, retain) NSString *detail;
@property (nullable, nonatomic, retain) NSString *message;
@property (nonatomic ) AcceptResultStatus status;
@property (nullable, nonatomic, retain) NSNumber *code;
@end

/**
 *  @class WDAcceptPasswordPolicyResult
 *  @brief  Result object for password policy
 **/
@interface WDAcceptPasswordPolicyResult : NSObject
@property (nullable, nonatomic, retain) NSNumber *expirationPeriod;
@property (nullable, nonatomic, retain) NSNumber *expiresNotificationDays;
@property (nullable, nonatomic, retain) NSNumber *minDigits;
@property (nullable, nonatomic, retain) NSNumber *minLength;
@property (nullable, nonatomic, retain) NSNumber *minLowerCase;
@property (nullable, nonatomic, retain) NSNumber *minSpecialCharacters;
@property (nullable, nonatomic, retain) NSNumber *minUpperCase;
@property (nullable, nonatomic, retain) NSString *specialCharacters;
@property (nullable, nonatomic, retain) NSNumber *whitespaceAllowed;
@end

/**
 *  @class WDAcceptCurrencyCore
 *  @brief  Currency core object
 **/
@interface WDAcceptCurrencyCore : WDAcceptObject <NSCoding>
/**
 *  @brief Currency
 *  @param code Currency Code
 *  @return new Currency
 **/
-(instancetype)initWithCurrencyCode:(NSString *)code;
@property (nullable, nonatomic, strong) NSString *code;
@end

/**
 *  @class WDAcceptCurrency
 *  @brief  Currency object
 **/
@interface WDAcceptCurrency : WDAcceptCurrencyCore
@property (nullable, nonatomic, strong) NSNumber *minorUnit;
@property (nullable, nonatomic, strong) NSString *name;
@property (nullable, nonatomic, strong) NSNumber *number;
@end

/**
 *  @class WDAcceptCountry
 *  @brief  Country object
 **/
@interface WDAcceptCountry : WDAcceptObject <NSCoding>

@property (nullable, nonatomic, strong) NSString *alpha2code;
@property (nullable, nonatomic, strong) NSString *alpha3code;
@property (nullable, nonatomic, strong) NSString *name;
@property (nullable, nonatomic, strong) NSNumber *numericCode;
@end

/**
 *  @class WDAcceptAddress
 *  @brief  Address object
 **/
@interface WDAcceptAddress : WDAcceptObject <NSCoding>
@property (nullable, nonatomic, strong) NSString *city;
@property (nullable, nonatomic, strong) NSString *postalCode;
@property (nullable, nonatomic, strong) NSString *stateOrProvince;
@property (nullable, nonatomic, strong) NSString *street1;
@property (nullable, nonatomic, strong) NSString *street2;
@property (nullable, nonatomic, strong) WDAcceptCountry *country;
-(NSString *)formattedAddress;
-(id _Nullable)castTo:(Class _Nonnull)targetClass;
@end

/**
 *  @class WDAcceptShop
 *  @brief  Shop object
 **/
@interface WDAcceptShop : WDAcceptObject <NSCoding>
@property (nullable, nonatomic, strong) NSString *internalId;
@property (nullable, nonatomic, strong) NSString *externalId;
@property (nullable, nonatomic, strong) NSString *siteId;
@property (nullable, nonatomic, strong) WDAcceptAddress *address;
@end

/**
 *  @class WDAcceptTaxRate
 *  @brief  Tax rate object
 **/
@interface WDAcceptTaxRate : WDAcceptObject<NSCoding>
@property (nullable, nonatomic, strong) NSDate *validFrom;
@property (nullable, nonatomic, strong) NSDecimalNumber *value;
@end

/**
 *  @class WDAcceptTaxCategory
 *  @brief  Tax category object
 **/
@interface WDAcceptTaxCategory : WDAcceptObject<NSCoding>
@property (nullable, nonatomic, retain) NSString *taxCategoryId;
@property (nullable, nonatomic, strong) NSDecimalNumber *currentValue;
@property (nullable, nonatomic, strong) NSString *name;
@property (nullable, nonatomic, strong) WDAcceptCountry *country;
@property (nullable, nonatomic, strong) NSArray<WDAcceptTaxRate *> *taxRates;
@end

/**
 *  @class WDAcceptPartner
 *  @brief  Partner category object
 **/
@interface WDAcceptPartner : WDAcceptObject <NSCoding>
@property (nullable, nonatomic, retain) NSString *partnerId;
@property (nullable, nonatomic, retain) NSString *name;
@property (nullable, nonatomic, retain) NSArray *paymentConstraints;
@end

/**
 *  @class WDAcceptMerchant
 *  @brief  Merchant object
 **/
@interface WDAcceptMerchant : WDAcceptObject <NSCoding>
@property (nullable, nonatomic, strong) NSNumber *defaultNetTaxation;
@property (nullable, nonatomic, strong) NSString *merchantId;
@property (nullable, nonatomic, strong) NSString *name;
@property (nullable, nonatomic, strong) NSString *notifyCallbackUrl;
@property (nullable, nonatomic, strong) NSString *phone;
@property (nullable, nonatomic, strong) NSNumber *receiptIncludedSaleItems;
@property (nullable, nonatomic, strong) NSNumber *smsSendingAllowed;
@property (nullable, nonatomic, strong) NSString *status;
@property (nullable, nonatomic, strong) WDAcceptAddress *address;
@property (nullable, nonatomic, strong) NSArray<WDAcceptCurrency *> *configuredCurrencies;
@property (nullable, nonatomic, strong) WDAcceptCurrency *defaultCurrency;
@property (nullable, nonatomic, strong) NSNumber *mccCode;
@property (nullable, nonatomic, strong) NSArray <WDAcceptTaxCategory *>* taxCategories;
@property (nullable, nonatomic, strong) NSDate *created;
@property (nullable, nonatomic, strong) NSString *supportEmail;
@property (nullable, nonatomic, strong) NSString *taxNumber;
@property (nullable, nonatomic, strong) NSString *supportPhone;
@property (nullable, nonatomic, strong) NSNumber *serviceChargeRate;
@property (nullable, nonatomic, strong) NSNumber *serviceChargeTaxRate;
@property (nullable, nonatomic, strong) NSNumber *tipTaxRate;
@property (nullable, nonatomic, strong) WDAcceptPartner *partner;
@property (nullable, nonatomic, strong) NSArray<WDAcceptShop *> *shops;
@property (nullable, nonatomic, strong) NSNumber *flatDiscount;
@property (nullable, nonatomic, strong) NSNumber *cashRegistersRequired;
@property (nullable, nonatomic, strong) NSString *erpSystemType;
/// Distinct Union of configured currencies and default currency
-(NSArray *)availableCurrencies;
@end



/**
 *  @class WDAcceptMerchantUser
 *  @brief  Merchant user object
 **/
@interface WDAcceptMerchantUser : WDAcceptObject<NSCoding>
@property (nullable, nonatomic, strong) NSDate *accountExpirationReference;
@property (nullable, nonatomic, strong) NSString *email;
@property (nullable, nonatomic, strong) NSNumber *failedLoginCount;
@property (nullable, nonatomic, strong) NSString *merchantUserId;
@property (nullable, nonatomic, strong) NSString *name;
@property (nullable, nonatomic, strong) NSString *phone;
@property (nullable, nonatomic, strong) NSNumber *requestPasswordChange;
@property (nullable, nonatomic, strong) NSString *status;
@property (nullable, nonatomic, strong) NSString *username;
@property (nullable, nonatomic, strong) WDAcceptMerchant *merchant;
@property (nullable, nonatomic, strong) NSArray<NSString *> *roles;
@property (nullable, nonatomic, strong) NSString *timeZone;
@property (nullable, nonatomic, strong) NSDate *created;
@property (nullable, nonatomic, strong) NSArray<WDAcceptShop *> *merchantShops;
@end

/**
 *  @class WDAcceptShiftReportCategoryItem
 *  @brief Item of a category received in the Cash Shift Report
 **/
@interface WDAcceptShiftReportCategoryItem : WDAcceptObject<NSCoding>
///**
// */
@property (nullable, nonatomic, copy) NSString *itemType;
///**
// */
@property (nonnull, nonatomic, copy) NSString *name;
///**
// */
@property (nullable, nonatomic, copy) NSDecimalNumber *netAmount;
///**
// */
@property (nullable, nonatomic, copy) NSDecimalNumber *taxAmount;
///**
// */
@property (nullable, nonatomic, copy) NSDecimalNumber *grossAmount;
///**
// */
-(instancetype)initWithShiftReportCategoryItem:(id)shiftReportCategoryItem;
@end

/**
 *  @class WDAcceptShiftReportCategory
 *  @brief Category received in the Cash Shift Report
 **/
@interface WDAcceptShiftReportCategory : WDAcceptObject<NSCoding>
///**
// */
@property (nullable, nonatomic, copy) NSString *categoryType;
///**
// */
@property (nonnull, nonatomic, copy) NSString *name;
///**
// */
@property (nullable, nonatomic, retain) NSArray <WDAcceptShiftReportCategoryItem *>*categoryItems;
///**
// */
-(instancetype)initWithShiftReportCategory:(id)shiftReportCategory;
@end

/**
 *  @class WDAcceptShiftReport
 *  @brief Report for a Cash Shift
 **/
@interface WDAcceptShiftReport : WDAcceptObject<NSCoding>
///**
// */
@property (nullable, nonatomic, strong) NSString *reportNumber;
///**
// */
@property (nullable, nonatomic, strong) WDAcceptMerchant *merchant;
///**
// */
@property (nullable, nonatomic, strong) WDAcceptShop *shop;
///**
// */
@property (nullable, nonatomic, strong) NSArray <WDAcceptShiftReportCategory *>*reportCategories;
///**
// */
-(instancetype)initWithShiftReport:(id)shiftReport;
@end

/**
 *  @class WDAcceptMerchantCashier
 *  @brief Merchant Cashier object
 **/
@interface WDAcceptMerchantCashier : WDAcceptObject<NSCoding>
/// Switch Cashier ID
@property (nullable, nonatomic, retain) NSString *internalId;
/// ERP Cashier ID
@property (nullable, nonatomic, retain) NSString *externalId;
/**
 */
@property (nonatomic, retain) NSNumber *version;
/**
 */
@property (nullable, nonatomic, retain) NSString *firstName;
/**
 */
@property (nullable, nonatomic, retain) NSString *lastName;
/// Pin Hash
@property (nullable, nonatomic, retain) NSString *pin;
/**
 */
@property (nullable, nonatomic, retain) NSArray<NSString *> *roles;
/**
 */
@property (nullable, nonatomic, retain) NSString *merchantId;
/**
 */
@property (nullable, nonatomic, retain) NSString *userId;
///**
// */
-(instancetype)initWithMerchantCashier:(id)mercCashier;
@end

/**
 *  @class WDAcceptCashShift
 *  @brief Cash Register object - Cash/Drawer Management
 **/
@interface WDAcceptCashShift : WDAcceptObject<NSCoding>
///**
// */
@property (nullable, nonatomic, retain) NSString *internalId;
///**
// */
@property (nullable, nonatomic, retain) NSDate *openTime;
///**
// */
@property (nullable, nonatomic, retain) NSDate *closeTime;
///**
// */
@property (nullable, nonatomic, retain) NSNumber *openingAmount;
///**
// */
@property (nullable, nonatomic, retain) NSNumber *closingAmount;
///**
// */
@property (nullable, nonatomic, retain) NSString *openingNote;
///**
// */
@property (nullable, nonatomic, retain) NSString *closingNote;
///**
// */
@property (nullable, nonatomic, retain) NSString *shiftStatus;
///**
// */
@property (nullable, nonatomic, retain) WDAcceptMerchantCashier *openedBy;
///**
// */
@property (nullable, nonatomic, retain) WDAcceptMerchantCashier *closedBy;
///**
// */
@property (nullable, nonatomic, retain) NSNumber *cashPurchases;
///**
// */
@property (nullable, nonatomic, retain) NSNumber *cashRefunds;
///**
// */
@property (nullable, nonatomic, retain) NSNumber *cashOperationsBalance;
///**
// */
@property (nullable, nonatomic, retain) NSNumber *cashBalance;
///**
// */
@property (nullable, nonatomic, retain) NSNumber *currentValue;
///**
// */
@property (nullable, nonatomic, retain) WDAcceptShiftReport *shiftReport;
///
@property (nullable, nonatomic, retain) WDAcceptCashRegister *cashRegister;
///
-(instancetype)initWithMerchantShift:(id)merchantShift;
/**
 * @brief Default Design of the Z-Report
 * @param format Format of the report
 * @param dpi dots per width of the receipt to be printed - not used for HTML or Datecs native format
 * @param completion Report in the requested format
 */
-(void)zReport:(AcceptPrintFormat)format
           dpi:(AcceptPrintDpi)dpi
    completion:(ZReportCompletion)completion;

/**
 * @brief Default Design of the Z-Report
 * @param format Format of the report
 * @param dpi dots per width of the receipt to be printed - not used for HTML or Datecs native format
 * @param language to use for translating the Z-Report labels
 * @param completion Report in the requested format
 */
-(void)zReport:(AcceptPrintFormat)format
           dpi:(AcceptPrintDpi)dpi
      language:(NSString *)language
    completion:(ZReportCompletion)completion;
@end

/**
 *  @class WDAcceptCashActivity
 *  @brief Cash Register object - Cash/Drawer Management
 **/
@interface WDAcceptCashActivity : WDAcceptObject<NSCoding>
///**
// */
@property (nullable, nonatomic, retain) NSNumber *amount;
///**
// */
@property (nullable, nonatomic, retain) NSDate *timestamp;
///**
// */
@property (nullable, nonatomic, retain) NSString *operationType;
///**
// */
@property (nullable, nonatomic, retain) NSString *firstname;
///**
// */
@property (nullable, nonatomic, retain) NSString *lastname;
///**
// */
@property (nullable, nonatomic, retain) NSString *note;
///**
// */
@property (nullable, nonatomic, retain) NSString *internalId;
///**
// */
-(instancetype)initWithShiftActivity:(id)shiftActivity;

@end

/**
 *  @class WDAcceptCashDrawerType
 *  @brief Cash Drawer Type
 **/
@interface WDAcceptCashDrawerType : WDAcceptObject<NSCoding>
/**
 */
@property (nullable, nonatomic, retain) NSString *internalId;
/**
 */
@property (nullable, nonatomic, strong) NSNumber *version;
/**
 */
@property (nullable, nonatomic, strong) NSString *vendor;
/**
 */
@property (nullable, nonatomic, strong) NSNumber *model;
@end

/**
 *  @class WDAcceptCashRegister
 *  @brief Cash Register object - Cash/Drawer Management
 **/
@interface WDAcceptCashRegister : WDAcceptObject<NSCoding>
/**
 */
@property (nullable, nonatomic, retain) NSString *internalId;
/**
 */
@property (nullable, nonatomic, retain) NSString *externalId;
/**
 */
@property (nonatomic, retain) NSNumber *version;
/**
 */
@property (nullable, nonatomic, retain) NSString *registerName;
/**
 */
@property (nullable, nonatomic, retain) NSString *serialNumber;
/**
 */
@property (nullable, nonatomic, retain) NSString *drawerStatus;
///**
// */
@property (nullable, nonatomic, retain) WDAcceptMerchantCashier *openedBy;
///**
// */
@property (nullable, nonatomic, retain) WDAcceptMerchantCashier *closedBy;
///**
// */
@property (nullable, nonatomic, retain) WDAcceptMerchant *merchant;
///**
// */
@property (nullable, nonatomic, retain) WDAcceptShop *shop;
///**
// */
@property (nullable, nonatomic, retain) WDAcceptCashShift *lastShift;
///**
// */
@property (nullable, nonatomic, retain) WDAcceptCurrency *currency;
///**
// */
@property (nullable, nonatomic, retain) WDAcceptCashDrawerType *cashDrawerType;
@end


/**
 *  @class WDAcceptUnitPrice
 *  @brief  Unit Price object
 **/
@interface WDAcceptUnitPrice : WDAcceptObject <NSCoding>
/**
 *  @brief Unit Price
 *  @param currency Currency
 *  @param unitValue Unit Price value
 *  @return new Unit Price
 **/
-(instancetype)initWithCurrency:(WDAcceptCurrencyCore *)currency unitValue:(NSNumber  *)unitValue;

@property (nonatomic, strong) WDAcceptCurrencyCore  *currency;
@property (nonatomic, strong) NSNumber  *unitValue;
@end

/**
 *  @class WDAcceptProductCatalogue
 *  @brief  Product Catalogue object
 **/
//@interface WDAcceptProductCatalogue : NSObject
//@property (nullable, nonatomic, retain) NSString *productCatalogueId;
//@property (nullable, nonatomic, retain) NSString *merchantId;
//@property (nullable, nonatomic, retain) NSString *productCatalogueName;
//@property (nullable, nonatomic, retain) NSString *productCatalogueDescription;
//@property (nullable, nonatomic, retain) NSNumber *version;
//@property (nullable, nonatomic, retain) NSString *lastUpdated;
//@end

/**
 *  @class WDAcceptTerminalCapabilities
 *  @brief  Terminal Capabilities template
 **/
@interface WDAcceptTerminalCapabilities : NSObject
@property (nullable, nonatomic, retain) NSString *terminalCapabilitiesId;
@property (nullable, nonatomic, retain) NSString *name;
@property (nullable, nonatomic, retain) NSString *emvTerminalType;
@property (nullable, nonatomic, retain) NSString *emvTransactionCategoryCode;
@property (nullable, nonatomic, retain) NSString *capabilities;
@property (nullable, nonatomic, retain) NSString *additionalCapabilities;
@end

/**
 *  @class WDAcceptICCApplication
 *  @brief  ICC Application template
 **/
@interface WDAcceptICCApplication : NSObject
@property (nullable, nonatomic, retain) NSString *iccApplicationId;
@property (nullable, nonatomic, retain) NSString *aid;
@property (nullable, nonatomic, retain) NSString *version;
@property (nullable, nonatomic, retain) NSString *product;
@property (nullable, nonatomic, retain) NSString *networkId;
@end

/**
 *  @class WDAcceptAID
 *  @brief  AID template
 **/
@interface WDAcceptAID : NSObject
@property (nullable, nonatomic, retain) NSString *aid;
@property (nullable, nonatomic, retain) NSString *ddol;
@property (nullable, nonatomic, retain) NSString *targetPercentage;
@property (nullable, nonatomic, retain) NSString *tacOnline;
@property (nullable, nonatomic, retain) NSString *terminalFloorLimit;
@property (nullable, nonatomic, retain) NSString *thresholdValue;
@property (nullable, nonatomic, retain) NSString *maxTargetPercentage;
@property (nullable, nonatomic, retain) NSString *tacDenial;
@property (nullable, nonatomic, retain) NSString *preferredApplicationName;
@property (nullable, nonatomic, retain) NSString *tdol;
@property (nullable, nonatomic, retain) NSString *applicationVersionNumber;
@property (nullable, nonatomic, retain) NSString *tacDefault;
@property (nullable, nonatomic, retain) NSString *acquirerIdentifier;
@property (nullable, nonatomic, retain) NSString *forceOnline;
@property (nullable, nonatomic, retain) NSString *transactionType;
@end

/**
 *  @class WDAcceptAIDConfiguration
 *  @brief  AID Configuration
 **/
@interface WDAcceptAIDConfiguration : NSObject
@property (nullable, nonatomic, retain) NSString *aidConfigurationId;
@property (nullable, nonatomic, retain) NSString *name;
@property (nullable, nonatomic, retain) WDAcceptICCApplication *chipApplication;
@property (nullable, nonatomic, retain) WDAcceptAID *items;
@end

/**
 *  @class WDAcceptNetwork
 *  @brief  Issuer Network detail
 **/
@interface WDAcceptNetwork : NSObject
@property (nullable, nonatomic, retain) NSString *networkId;
@property (nullable, nonatomic, retain) NSString *networkIssuerName;
@end

/**
 *  @class WDAcceptTerminalProfile
 *  @brief  Terminal Profile
 **/
@interface WDAcceptTerminalProfile : NSObject
@property (nullable, nonatomic, retain) NSString *terminalProfileId;
@property (nullable, nonatomic, retain) NSString *tid;
@property (nullable, nonatomic, retain) NSString *mid;
@property (nullable, nonatomic, retain) WDAcceptCurrency *currency;
@property (nullable, nonatomic, retain) WDAcceptNetwork *network;
-(NSString*)getNetworkName;
@end

/**
 *  @class WDAcceptTerminalAIDConfiguration
 *  @brief Terminal AID Configuration
 **/
@interface WDAcceptTerminalAIDConfiguration : NSObject
@property (nullable, nonatomic, retain) NSString *merchantName;
@property (nullable, nonatomic, retain) NSNumber *mcc;
@property (nullable, nonatomic, retain) NSString *terminalCountryCode;
@property (nullable, nonatomic, retain) NSArray<WDAcceptAIDConfiguration *> *aidConfigurations;
@property (nullable, nonatomic, retain) WDAcceptTerminalCapabilities *terminalCapabilitiesTemplate;
@property (nullable, nonatomic, retain) NSArray<WDAcceptTerminalProfile *> *terminalProfiles;

#pragma mark  Helpers
-(WDAcceptAIDConfiguration *)getTerminalAIDConfigurationForAID:(NSString *)aid;
-(WDAcceptAIDConfiguration *)getTerminalAIDChipAppConfigurationForAID:(NSString *)aid;
-(WDAcceptTerminalProfile *)getTerminalProfileForCurrency:(NSString *)currencyCode andNetwork:(NSString *)networkId;
@end


/**
 *  @class WDAcceptShiftQuery
 *  @brief  Query the shifts
 **/
@interface WDAcceptShiftQuery : WDAcceptQuery
/**
 *  @brief Shift Query attributes used for query request
 *  @param page Page to obtain from sorted results
 *  @param orderBy results ordered by
 *  @param orderSort results sorted ascending/descending
 *  @return new Accept Query
 **/
-(instancetype)initWithPage:(NSUInteger)page
                   pageSize:(NSUInteger)pageSize
                    orderBy:(AcceptShiftQueryOrderBy)orderBy
                  orderSort:(AcceptQuerySort)orderSort;
@property (nonatomic) AcceptShiftQueryOrderBy orderBy;
@property (nonatomic) AcceptQuerySort orderSort;
@end

/**
 *  @class WDAcceptExtendedProcessingInfo
 *  @brief Extented processing info class. Content needed for some Chip transactions with online PIN verification and/or CVM methods
 **/
@interface WDAcceptExtendedProcessingInfo : NSObject
/**
 */
@property (nonatomic, strong) NSNumber *gratuityAmount;
/**
 */
@property (nonatomic, strong) NSString * _Nullable applicationId;
/**
 */
@property (nonatomic, strong) NSString *  _Nullable merchantId;
/**
 */
@property (nonatomic, strong) NSString *  _Nullable encryptedPIN;
/**
 */
@property (nonatomic) BOOL reversalIsRequired;
/**
 */
@property (nonatomic) int reversalReason;
/**
 */
@property (nonatomic) BOOL signatureCheckIsRequired;
/**
 */
@property (nonatomic) NSArray *confirmationsRequired;
/**
 */
@property (nonatomic) NSString * _Nullable applicationCryptogram;
/**
 */
@property (nonatomic) BOOL onlineAuthentication;
/**
 */
@property (nonatomic) BOOL isCaptureRequired;
/**
 */
@property (nonatomic) BOOL contaclessOnlinePinWrong;
/**
 */
@property (nonatomic) UIImage *signatureImage;
@end

/**
 *  @class WDAcceptEncryptionParameters
 *  @brief Encryption parameters
 **/
@interface WDAcceptEncryptionParameters : NSObject
/**
 */
@property (nullable, nonatomic, retain) NSString *encoding;
/**
 */
@property (nullable, nonatomic, retain) NSString *format;
/**
 */
@property (nullable, nonatomic, retain) NSString *ksn;
/**
 */
@property (nullable, nonatomic, retain) NSString *name;
/**
 */
@property (nullable, nonatomic, retain) NSString *padding;
/**
 */
@property (nullable, nonatomic, retain) NSString *version;
@end

/**
 *  @class WDAcceptTerminalRKIRequest
 *  @brief Terminal Remote Key Injection values
 **/
@interface WDAcceptTerminalRKIRequest : WDAcceptObject
/**
 */
@property (nullable, nonatomic, retain) NSString *vendor;
/**
 */
@property (nullable, nonatomic, retain) NSString *model;
/**
 */
@property (nullable, nonatomic, retain) NSString *serialNo;
/**
 */
@property (nullable, nonatomic, retain) NSString *prodSignCrt;
/**
 */
@property (nullable, nonatomic, retain) NSString *terminalCrt;
/**
 */
@property (nullable, nonatomic, retain) NSString *tempKeyCrt;
/**
 */
@property (nullable, nonatomic, retain) NSString *suggestedIksn;

@end

/**
 *  @class WDAcceptTerminalRKI
 *  @brief Terminal Remote Key Injection values
 **/
@interface WDAcceptTerminalRKI : WDAcceptObject
/**
 */
@property (nullable, nonatomic, retain) NSString *hsmCertificate;
/**
 */
@property (nullable, nonatomic, retain) NSString *iksnPin;
/**
 */
@property (nullable, nonatomic, retain) NSString *iksnSred;
/**
 */
@property (nullable, nonatomic, retain) NSString *initialDukptPin;
/**
 */
@property (nullable, nonatomic, retain) NSString *initialDukptSred;
/**
 */
@property (nullable, nonatomic, retain) NSString *tmk;
/**
 */
@property (nullable, nonatomic, retain) NSString *tmkSignature;

@end

/**
 *  @class WDAcceptMember
 *  @brief ERP Members information
 **/
@interface WDAcceptMember : WDAcceptObject<NSCoding>
/**
 */
@property (nullable, nonatomic, retain) NSString *memberId;
/**
 */
@property (nullable, nonatomic, retain) NSString *accountId;
/**
 */
@property (nullable, nonatomic, retain) NSString *lifeCycleStatusCode;
/**
 */
@property (nullable, nonatomic, retain) NSString *birthDate;
/**
 */
@property (nullable, nonatomic, retain) NSString *email;
/**
 */
@property (nullable, nonatomic, retain) NSString *surname;
/**
 */
@property (nullable, nonatomic, retain) NSString *firstName;
@end

/**
 *  @class WDAcceptTerminalUpdate
 *  @brief Update information for the terminal
 **/
@interface WDAcceptTerminalUpdate : WDAcceptObject<NSCoding>
///
@property (nullable, nonatomic, retain) NSString *version;
///
@property (nullable, nonatomic, retain) NSNumber *size;
///
@property (nullable, nonatomic, retain) NSString *terminalUpdateId;
///
@property (nullable, nonatomic, retain) NSString *checksum;
///
@property (nullable, nonatomic, retain) NSString *updateDescription;
///
@property (nonatomic) AcceptUpdateSeverity severity;
///
@property (nullable, nonatomic, retain) NSString *downloadURL;
@end

/**
 *  @class WDAcceptTerminalUpdates
 *  @brief Set of updates information for the terminal APPLICATION + CONFIGURATION + FIRMWARE
 **/
@interface WDAcceptTerminalUpdates : WDAcceptObject<NSCoding>

@property (nullable, nonatomic, retain) WDAcceptTerminalUpdate *assignedApplication;
@property (nullable, nonatomic, retain) WDAcceptTerminalUpdate *assignedConfiguration;
@property (nullable, nonatomic, retain) WDAcceptTerminalUpdate *assignedFirmware;

@end

#pragma mark - Request Callbacks
/**
 *  @typedef PaymentProgress
 *  @brief Callback to be executed upon payment process stage change
 *  @param paymentProgress Coded payment progress
 **/
typedef void (^PaymentProgress)(AcceptStateUpdate paymentProgress);

/**
 *  @typedef PaymentSignature
 *  @brief Used by the extension to notify the Payment Flow to require the collection of customer's signature
 *  @param signatureRequest Details of the signature request (card holder details as supplied by extension)
 *  @see WDAcceptSignatureRequest
 **/
typedef void (^PaymentSignature)(WDAcceptSignatureRequest * _Nullable signatureRequest);

/**
 *  @typedef PaymentCardApplicationSelection
 *  @brief Used by extension to notify the Payment Flow to ask for the Card application selection
 *  @param appSelectionRequest  WDAcceptAppSelectionRequest to be sent to the client application
 *  @see WDAcceptAppSelectionRequest
 **/
typedef void (^PaymentCardApplicationSelectionRequest)(WDAcceptAppSelectionRequest * _Nullable appSelectionRequest);

/**
 *  @typedef PrintCompletion
 *  @brief Callback to be executed in the case the printing is complete
 **/
typedef void (^PrintCompletion)(BOOL printStatusOK, NSError* _Nullable printError);

/**
 *  @typedef PrinterStateUpdate
 *  @brief Callback to be executed upon print process stage change
 **/
typedef void (^PrinterStateUpdate)(AcceptPrinterStateUpdate printProgress);

/**
 *  @typedef DeviceDiscoveryCompletion
 *  @brief Callback to be executed upon completion of device discovery
 *  @param devices of AcceptTerminal
 **/
typedef void (^DeviceDiscoveryCompletion)(NSArray <WDAcceptTerminal *>* _Nullable devices, NSError* _Nullable devicesError);
/**
 *  @typedef VendorDiscoveryCompletion
 *  @brief Callback to be executed upon completion of vendor discovery
 *  @param vendors of WDAcceptVendor
 **/
typedef void (^VendorDiscoveryCompletion)(NSArray <WDAcceptVendor *> * _Nullable vendors);
/**
 *  @typedef WDAcceptUpdateConfigurationProgress
 *  @brief Callback to be executed at each progress update of the terminal configuration update process
 *  @param configurationUpdate progress status
 **/
typedef void (^UpdateConfigurationProgress)(AcceptUpdateConfigurationProgressUpdate configurationUpdate);

/**
 *  @typedef UpdateTerminalCompletion
 *  @brief Callback to be executed at the end of the terminal configuration update process
 *  @param updateStatus terminal update result
 **/
typedef void (^UpdateTerminalCompletion)(AcceptUpdateConfigurationStatus updateStatus, NSError* _Nullable updateError);

/**
 *  @typedef TerminalUpdatesCompletion
 *  @brief Callback to be executed at the end of the available terminal updates process
 *  @param availableUpdates the details of the available updates (Configuration, Terminal Application, Firmware)
 **/
typedef void (^TerminalUpdatesCompletion)(WDAcceptTerminalUpdates *_Nullable availableUpdates, NSError* _Nullable availableUpdatesError);

/**
 *  @typedef SignatureVerificationResultCallback
 *  @brief The callback to pass to startPay function with the result of Customer signature verification
 *  @param signatureVerificationResult the result of the Merchant veryfying the customer signature
 **/
typedef void (^SignatureVerificationResult)(AcceptSignatureVerificationResult signatureVerificationResult);

/**
 *  @typedef PaymentConfirmationResult
 *  @brief The callback to pass to startPay function with the result of Customer confirmation - either Signature confirmation or Password entry completed confirmation (In the case of WeChat)
 *  @param paymentConfirmationResult the result of the Merchant veryfying the customer signature or confirming Password was entered by customer (WeChat customer)
 **/
typedef void (^PaymentConfirmationResult)(AcceptPaymentConfirmationResult paymentConfirmationResult);

/**
 *  @typedef SignatureRequest
 *  @brief Callback to be executed if the signature is required during the payment process
 *  @param signatureRequest signature request block
 **/
typedef void (^SignatureRequiredRequest)(WDAcceptSignatureRequest* _Nonnull signatureRequest);

/**
 *  @typedef SignatureVerificationRequest
 *  @brief The callback to pass to startPay function with the result of Customer signature verification
 *  @param signatureVerificationResult the result of the Merchant veryfying the customer signature // if returned as nil from the sdk then Merchant accepts/rejects signature on the terminal and not within the app
 **/
typedef void (^SignatureVerificationRequest)(SignatureVerificationResult _Nullable signatureVerificationResult, NSError* _Nullable signatureVerificationError);


/**
 *  @typedef MerchantDetailCompletion
 *  @brief The callback upon the merchant detail method completion
 *  @param merchantUser the result of the login method - available if correct user credentials used
 **/
typedef void(^MerchantDetailCompletion)(WDAcceptMerchantUser * _Nullable merchantUser, NSError * _Nullable merchantUserError);

/**
 *  @typedef MerchantCashierCompletion
 *  @brief The callback upon the merchant cashier method completion
 *  @param merchantCashiers the result of the getMerchantCashiers method - available if correctly logged in
 **/
typedef void(^MerchantCashierCompletion)( NSArray <WDAcceptMerchantCashier *>* _Nullable merchantCashiers, NSError * _Nullable merchantCashiersError);

/**
 *  @typedef CurrentUserCompletion
 *  @brief The callback upon the current user method completion
 *  @param currentUser Current user - as per credentials used when initializing the SDK
 *  @param cashier Cashier record if exists for the Current user
 *  @error Error from the current user process
 **/
typedef void(^CurrentUserCompletion)( WDAcceptMerchantUser * _Nullable currentUser, WDAcceptMerchantCashier * _Nullable cashier, NSError * _Nullable error);

/**
 *  @typedef MerchantCashierPinValidationCompletion
 *  @brief The callback upon the merchant cashier PIN validation method completion
 *  @param pinValidationResult shows the result of the PIN validation
 **/
typedef void(^MerchantCashierPinValidationCompletion)( AcceptCashierPinValidationResult pinValidationResult, NSError * _Nullable merchantCashierValidationError);

/**
 *  @typedef CashRegisterCompletion
 *  @brief The callback upon the merchant cashier method completion
 *  @param cashRegisters the result of the getMerchantCashiers method - available if correctly logged in
 **/
typedef void(^CashRegisterCompletion)( NSArray <WDAcceptCashRegister *>* _Nullable cashRegisters, NSError * _Nullable cashRegistersError);

/**
 *  @typedef CashRegisterShiftCompletion
 *  @brief The callback upon the merchant cashier method completion
 *  @param cashShifts the result of the getMerchantCashiers method - available if correctly logged in
 **/
typedef void(^CashRegisterShiftCompletion)( NSArray <WDAcceptCashShift *>* _Nullable cashShifts, NSError * _Nullable cashShiftsError);

/**
 *  @typedef CashRegisterShiftCompletion
 *  @brief The callback upon the merchant cashier method completion
 *  @param cashShifts shifts for this merchant
 *  @param cashShiftsError error obtaining shifts
 **/
typedef void(^CashRegisterShiftDetailsCompletion)( WDAcceptCashShift * _Nullable cashShifts, NSError * _Nullable cashShiftsError);

/**
 *  @typedef CashRegisterActivityCompletion
 *  @brief The callback upon the cash register activity completion
 *  @param cashActivities cash activities of this cashier
 *  @param cashActivitiesError  error obtaining the cash activities
 **/
typedef void(^CashRegisterActivityCompletion)( NSArray <WDAcceptCashActivity *>* _Nullable cashActivities, NSError * _Nullable cashActivitiesError);

/**
 *  @typedef SaleCompletion
 *  @brief Callback to be executed at the end of the payment process
 *  @param saleResponse transaction object
 *  @param saleResponseError if encountered during the paymnet process
 **/
typedef void (^SaleCompletion)(WDAcceptSaleResponse* _Nullable saleResponse, NSError* _Nullable saleResponseError);

/**
 *  @typedef SendReceiptCompletion
 *  @brief Callback to be executed at the end of the send receipt process
 *  @param recepients recepient email addresses
 **/
typedef void (^SendReceiptCompletion)(NSArray <NSString*>* _Nullable recepients, NSError* _Nullable error);

/**
 *  @typedef CredentialManagementCompletion
 *  @brief Callback to be executed at the end of the credential management action
 *  @param result the credential management result
 **/
typedef void (^CredentialManagementCompletion)(WDAcceptResult * _Nullable result, NSError* _Nullable error);

/**
 *  @typedef PasswordPolicyCompletion
 *  @brief Callback to be executed at the end of the credential management action
 *  @param policy the password policy result object
 *  @param error if encountered during the process
 **/
typedef void (^PasswordPolicyCompletion)(WDAcceptPasswordPolicyResult * _Nullable policy, NSError* _Nullable error);

/**
 *  @typedef SaleStatisticsCompletion
 *  @brief Callback to be executed at the end of the get transaction statistics
 *  @param statistics array of transaction statistics objects
 **/
typedef void (^SaleStatisticsCompletion)(NSArray  <WDAcceptSaleStatistics *>* _Nullable statistics, NSError* _Nullable error);

/**
 *  @typedef SaleUpdateCompletion
 *  @brief Callback to be executed at the end of the transaction update process
 *  @param sale updated sale
 **/
typedef void (^SaleUpdateCompletion)(WDAcceptSaleResponse* _Nullable sale, NSError* _Nullable error);

/**
 *  @typedef ProductCatalogueCompletion
 *  @brief Callback to be executed at the end of the product catalogue maintenance or query process
 *  @param productCatalogues available product catalogues
 **/
typedef void (^ProductCatalogueCompletion)(NSArray <WDAcceptProductCatalogue *>*_Nullable productCatalogues, NSError* _Nullable error);

/**
 *  @typedef ProductCatalogueCategoryCompletion
 *  @brief Callback to be executed at the end of the product catalogue category maintenance or query process
 *  @param productCategories product categories
 **/
typedef void (^ProductCatalogueCategoryCompletion)(NSArray <WDAcceptProductCatalogueCategory *>*_Nullable productCategories, NSError* _Nullable error);

/**
 *  @typedef ProductCatalogueProductCompletion
 *  @brief Callback to be executed at the end of the product catalogue maintenance or query process
 *  @param products Products
 **/
typedef void (^ProductCatalogueProductCompletion)(NSArray <WDAcceptProductCatalogueProduct *>*_Nullable products,NSNumber * _Nullable totalCount, NSError* _Nullable error);

/**
 *  @typedef ProductStockCompletion
 *  @brief Callback to be executed at the end of the product stock query process
 *  @param stocks Stock availability
 **/
typedef void (^ProductStocksCompletion)(NSArray <WDAcceptProductStock *>*_Nullable stocks, NSError* _Nullable error);

/**
 *  @typedef MembersCompletion
 *  @brief Callback to be executed at the end of the members  query process
 *  @param members Members list
 **/
typedef void (^MembersCompletion)(NSArray <WDAcceptMember *>*_Nullable members, NSError* _Nullable error);

/**
 *  @typedef ProductCatalogueProductChangeCompletion
 *  @brief Callback to be executed at the end of the product catalogue maintenance or query process
 *  @param updatedProducts updated products
 *  @param deletedProducts of strings with the ids of the products that were removed
 **/
typedef void (^ProductCatalogueProductChangeCompletion)(NSArray <WDAcceptProductCatalogueProduct *>*_Nullable updatedProducts, NSArray <NSString *>*_Nullable deletedProducts, NSError* _Nullable error);

/**
 *  @typedef ProductCatalogueImageCompletion
 *  @brief Callback to get the image of a catalogue product
 *  @param productsImage  producs image
 **/
typedef void (^ProductCatalogueImageCompletion)(NSArray <WDAcceptProductImage *>*_Nullable productsImage, NSError* _Nullable error);

/**
 *  @typedef ProductPricesCompletion
 *  @brief Callback to be executed at the end of the member's products prices query process
 *  @param productPrices Products prices list
 **/
typedef void (^ProductPricesCompletion)(NSArray <WDAcceptProductPrice *>*_Nullable productPrices, NSError* _Nullable error);

/**
 *  @typedef WDAcceptTerminalRKICompletion
 *  @brief Callback after the terminal RKI were retrieved from backend
 *  @param terminalRKI  terminal RKI details
 **/
typedef void(^WDAcceptTerminalRKICompletion)(WDAcceptTerminalRKI * _Nullable terminalRKI, NSError * _Nullable error);


#pragma mark - Helper Functions
/**
 *  @brief Get the  Transaction State  from Accept Transaction State code
 *  @param acceptState Accept Transaction Status code
 *  @return  Transaction State as string
 **/
NSString *const _Nullable PaymentStateFromAcceptState(AcceptPaymentState acceptState);

/**
 *  @brief get the Switch transaction types as dictionary
 **/
NSDictionary *  WDATransactionTypes();

/**
 *  @brief get the Switch payment methods as dictionary
 **/
NSDictionary *  WDAPaymentMethods();

/**
 *  @brief Get the Accept Extensions as dictionary of code and names
 *  @return Accept Extensions dictionary
 **/
NSDictionary * WDAcceptExtensionNames();

/**
 *  @brief Get the Accept Extension name from Vendor UUID
 *  @return Accept Extension name
 **/
NSString * WDAcceptExtensionNameFromAcceptVendorUUID(WDAExtensionTypeUUID vendorUUID);

/**
 *  @brief Get the Accept Vendor UUID from Extension name
 *  @return Accept vendor UUID
 **/
WDAExtensionTypeUUID WDAcceptVendorUUIDFromAcceptExtensionName(NSString *extensionName);

/**
 *  @brief get the Internal transaction statuses as dictionary
 *  @return Dictionary of mapping internal Switch Payment statuses to external Accept Payment statuses
 **/
NSDictionary *  WDAPaymentStatuses();

/**
 *  @brief get the Internal sale statuses as dictionary
 *  @return Dictionary of mapping internal Switch Sale statuses to external Accept sale statuses
 **/
NSDictionary *  WDASaleStatuses();


/**
 *  @brief get the Accept Sale status from Switch Sale status
 *  @return Accept Sale Status
 **/
AcceptSaleState WDAcceptSaleStatusFromSaleStatus(NSString *saleStatus);
/**
 *  @brief Get the Sale Status from Accept Sale Status code
 *  @param saleStatus Accept Sale Status code
 *  @return Sale State as string
 **/
NSString *const SaleStatusFromWDAcceptSaleStatus(AcceptSaleState saleStatus);

/**
 *  @brief get the Switch Payment Method and Transaction Type from Accept Payment Method and Transaction type
 *  @return Switch Payment Method and Transaction Type
 **/

NSString *const WDAPaymentMethodAndTransactionTypeFromAcceptPaymentMethodAndTransactionType(AcceptPaymentMethod paymentMethod, AcceptTransactionType transactionType);

/**
 *  @typedef BarCodeTypeCompletion
 *  @brief Callback to be executed at the end of the barcode type maintenance or query process
 *  @param barCodeTypes Supported BarCode types
 **/
typedef void (^BarCodeTypeCompletion)(NSArray <WDAcceptBarCodeType *>*_Nullable barCodeTypes, NSError* _Nullable error);

NS_ASSUME_NONNULL_END

#endif // WDA_DATA_TYPES
