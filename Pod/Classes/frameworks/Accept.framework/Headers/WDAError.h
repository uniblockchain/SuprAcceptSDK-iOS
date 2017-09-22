//
//  WDSError.h
//  acceptSDK
//
//  Created by Danko, Radoslav on 18/10/15.
//  Copyright © 2015 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
/**
 *  @brief WDSError
 *  @discussion Enumerator of acceptSDK errors
 **/
typedef NS_ENUM(NSInteger, AcceptSDKError ) {
    AcceptSDKErrorBackendReturnedJSONDoesNotMatchMappedClass,
    AcceptSDKErrorUnauthorizedUser,
    AcceptSDKErrorUserPasswordExpired,
    AcceptSDKErrorUserAccessForbidden,
    AcceptSDKErrorResourceNotFound,
    AcceptSDKErrorSessionExpired,
    AcceptSDKErrorRequestTimeOut,
    AcceptSDKErrorRequestNoProperResponse,
    AcceptSDKErrorRequestParameterRequired,
    AcceptSDKErrorRequestedResourceNotFound,
    AcceptSDKErrorRequestFailedValidation,//10
    AcceptSDKErrorPlugInTimeout ,
    AcceptSDKErrorSignatureTimeout,
    AcceptSDKErrorInitialization,
    AcceptSDKErrorLowBatteryLevel,
    AcceptSDKErrorSwipeTimeout,
    AcceptSDKErrorBadSwipe,
    AcceptSDKErrorNotSupportedCardType,
    AcceptSDKErrorDataProcessing,
    AcceptSDKErrorOnlineProcessing,
    AcceptSDKErrorTransactionNotApproved,//20
    AcceptSDKErrorHardwareAccessPermission,
    AcceptSDKErrorTokenExpired,
    AcceptSDKErrorConnection,
    AcceptSDKErrorSignatureRequired,
    AcceptSDKErrorCantLoadTerminalConfiguration,
    AcceptSDKErrorCantLoadSwiperTerminalConfiguration,
    AcceptSDKErrorTerminalDamaged,
    AcceptSDKErrorNoDUKPT,
    AcceptSDKErrorFailedToStartEMV,
    AcceptSDKErrorFailedToSendOfflineEMV,//30
    AcceptSDKErrorFailedToSendOnlineEMV,
    AcceptSDKErrorTerminalNotSetInMerchant,
    AcceptSDKErrorResponseLost,
    AcceptSDKErrorTransactionTerminated,
    AcceptSDKErrorTransactionDeclined,
    AcceptSDKErrorTransactionFailure,
    AcceptSDKErrorBlockedCardType,
    AcceptSDKErrorFailedBluetoothConnection,
    AcceptSDKErrorFailedPrinterBluetoothConnection,
    AcceptSDKErrorFailedTerminalBluetoothConnection,//40
    AcceptSDKErrorFailedDrawerBluetoothConnection,
    AcceptSDKErrorFailedPistolBluetoothConnection,
    
    AcceptSDKErrorTerminalNotReady,
    AcceptSDKErrorTerminalCommunication,
    AcceptSDKErrorTerminalTimeoutApplicationSelection,
    AcceptSDKErrorTerminalFailedToGetICCApplicationsList,
    AcceptSDKErrorTerminalFailedToTerminateCurrentTerminalPaymentFlow,
    AcceptSDKErrorLowPowerInAudioJack,
    AcceptSDKErrorMonoAudioEnabled,
    AcceptSDKErrorTerminalCommandTimeOut,//50
    AcceptSDKErrorTerminalTimeOut,
    AcceptSDKErrorTerminalCancelledFileUpload,

    AcceptSDKErrorWrongUserNameOrPassword,
    AcceptSDKErrorVendorNotFound,
    AcceptSDKErrorExternalAccessoriesProtocolInvalid,          // some extensions requires additional configuration changes in host application .plist file.
    AcceptSDKErrorExternalIdNotFound,                   // there is no user/merchant with given external id. ( HTTP 422 )
    AcceptSDKErrorChangePasswordCriteriaNotMet,                  //password change criteria not met
    AcceptSDKErrorQueryStatsTokenExpired,
    AcceptSDKErrorForgotExternalIdNotFound,             // there is no user/merchant with given email address. ( HTTP 422 )
    
    AcceptSDKErrorConfigFilesInfoTimeout,//60
    AcceptSDKErrorConfigFilesZipDownload,
    AcceptSDKErrorTerminalDisconnected,
    AcceptSDKErrorConfigFilesTerminalMayNotBeSet,
    AcceptSDKErrorConfigFilesTerminalCancelledFileDownload,
    AcceptSDKErrorConfigFilesProductionFirmwareOnDevelopmentTerminal,
    AcceptSDKErrorConfigFilesDevelopmentFirmwareOnProductionTerminal,
    AcceptSDKErrorConfigFilesTerminalUnsupported,
    AcceptSDKErrorConfigFilesTokenExpired,
    AcceptSDKErrorInventoryNoData,
    AcceptSDKErrorConfigFilesTerminalFirmwareDoesNotExist,//70
    AcceptSDKErrorConfigFilesReading,
    
    AcceptSDKErrorPrinterTimeout,
    AcceptSDKErrorPrinterInitialization,
    AcceptSDKErrorPrinterLowBatteryLevel,
    AcceptSDKErrorPrinterNotConnected,
    AcceptSDKErrorPrinterOperation,
    AcceptSDKErrorPrinterUnsupportedDevice,
    AcceptSDKErrorDeviceDoesNotSupportPrinting,
    AcceptSDKErrorPrinterPaperLow,
    
    AcceptSDKErrorSignatureRejectedFromTerminal,//80
    AcceptSDKErrorInvalidPaymentConfiguration,
    AcceptSDKErrorInvalidAIDConfiguration,
    
    AcceptSDKErrorTransactionReversalRequired,
    AcceptSDKErrorTransactionReversedByTerminal,
    AcceptSDKErrorTransactionReversalFailed,
    AcceptSDKErrorTransactionUpdateFailed,
    
    AcceptSDKErrorExtensionClassDoesNotExist,
    AcceptSDKErrorExtensionDoesNotSupportMethod,
    AcceptSDKErrorInvalidParameter,
    AcceptSDKErrorDeviceRooted,
    
    AcceptSDKErrorActiveTerminalNotSet,// 90
    AcceptSDKErrorActiveScanPistolNotSet,
    AcceptSDKErrorActivePrinterNotSet,
    AcceptSDKErrorPinLocked,
    AcceptSDKErrorPinInvalid,
    AcceptSDKErrorGeneral
};


/**
 *  @class WDAError
 *  @brief Accept Error object
 *  @discussion Error helper methods
 **/
@interface WDAError : NSObject

/**
 *  @brief Error constructor - uses the errorCode to add the default error code description
 *  @param errorCode Error code
 *  @return Error object
 **/
+(NSError *)error:(AcceptSDKError)errorCode;

/**
 *  @brief Error constructor  - uses the errorCode to add the default error code description and appends the custom reason
 *  @param errorCode Error code
 *  @param reason Error reason
 *  @return Error object
 **/
+(NSError *)error:(AcceptSDKError)errorCode andCustomReason:(NSString *)reason;

/**
 *  @brief Error constructor
 *  @param errorCode Error code
 *  @param description Error description
 *  @return Error object
 **/
+(NSError *)error:(AcceptSDKError)errorCode withDescription:(NSString*)description;

/**
 *  @brief Error constructor
 *  @param errorCode Error code
 *  @param andUnderlyingError underlying Error
 *  @return Error object
 **/
+(NSError *)error:(AcceptSDKError)errorCode andUnderlyingError:(NSError*)andUnderlyingError;

/**
 *  @brief Error constructor
 *  @param errorCode Error code
 *  @param description Error description
 *  @param reason Error reason
 *  @param underlyingError underlying error
 *  @return Error object
 **/
+(NSError *)error:(AcceptSDKError)errorCode withDescription:(NSString*)description andReason:(NSString *)reason  andUnderlyingError:(NSError *)underlyingError;
    
/**
 *  @brief Get the default description linked to this error code
 *  @param errorCode Error code
 *  @return Error description
 **/
+(NSString *)defaultDescriptionOfErrorCode:(AcceptSDKError)errorCode;

/**
 *  @brief Get the dictionary of error codes and their descriptions
 *  @return Dictionary of error codes and linked descriptions
 **/
+(NSDictionary *)errorCodesDescriptions;

/**
 *  @brief Collate underlying reasons into the array of strings
 *  @param reason add reason into the array of reason - recursively
 *  @param reasons array of reasons
 **/
+(void)underlyingReasons:(NSError *)reason reasons:(NSMutableArray *)reasons;
@end
