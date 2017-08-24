//
//  WDAcceptExtensionProtocols.h
//  acceptSDK
//
//  Created by Marek Timko on 05/12/2016.
//
//

#import "WDADataTypes.h"
#import "WDAcceptProtocols.h"
#import <ExternalAccessory/ExternalAccessory.h>

NS_ASSUME_NONNULL_BEGIN

@class WDAcceptCard;
@class WDAcceptExtensionInformation;

#pragma mark - Blocks
/**
 *  @brief PaymentCompletion
 *  @discussion Callback to be executed upon payment completion
 **/
typedef void (^SaleInternalCompletion)(WDAcceptSaleResponse* _Nullable ,WDAcceptExtendedProcessingInfo * _Nullable , NSError* _Nullable );

/**
 *  @brief PaymentOnlinePorcessorCompletion
 *  @discussion Used by PaymentFlow to inform the Extension about the result of processing the card transaction
 *  @param saleResponse Sale response returned by backend after processing the card data supplied by the Extension
 *  @param processorError error encountered during the backend card transaction processing
 **/
typedef void(^PaymentOnlinePorcessorCompletion)(WDAcceptSaleResponse *_Nullable saleResponse,  NSError* _Nullable  processorError);
/**
 *  @brief PaymentOnlineProcessor
 *  @discussion Used by extension to inform the Payment Flow about the card data, signature requested and additional details about the terminal and card transaction processing on the terminal
 *  @param cardData supplied by the extension
 *  @param signature signature image in the case terminal invoked signature request previously
 *  @param acceptTerminalInfo supplied by the extension - populated in various steps of obtaining firmware version, serial number etc
 *  @param extendedInfo supplied by the extension - populated in various steps in terminal specific payment flow (gratuity amount as captured on terminal, app cryptogram, encrypted pin etc.)
 *  @param onlineProcessorCompletion executed by the PaymentFlow at the end of the processing the card transaction
 **/
typedef void(^PaymentOnlineProcessor)(WDAcceptCard *_Nullable cardData, UIImage* _Nullable signature, WDAcceptExtensionInformation* _Nullable acceptTerminalInfo, WDAcceptExtendedProcessingInfo * _Nullable extendedInfo, PaymentOnlinePorcessorCompletion onlineProcessorCompletion);

/**
 *  @brief WDAcceptTerminalAIDConfigurationCompletion
 *  @discussion The callback to report the device AID configuration
 *  @param terminalAIDConfiguration the AID configuration for this terminal
 *  @param terminalConfigurationError error obtaining the AID configuration for this terminal
 **/
typedef void (^WDAcceptTerminalAIDConfigurationCompletion)(WDAcceptTerminalAIDConfiguration * _Nullable terminalAIDConfiguration, NSError  * _Nullable terminalConfigurationError);
/**
 *  @brief WDAcceptTerminalAIDConfiguration
 *  @discussion Used by extension to obtain the Terminal configuration from the Payment Flow based on supplied details from the terminal
 *  @param terminalSerialNumber as obtained from the terminal
 *  @param terminalModel as obtained from the terminal
 *  @param completion as passed back from the payment flow in the case of failures in obtaining the terminal configuration from hte backend
 *                                    or during the extension communication
 **/
typedef void (^PaymentTerminalConfiguration)(NSString* _Nullable terminalSerialNumber, NSString* _Nullable terminalModel, WDAcceptTerminalAIDConfigurationCompletion completion);

/**
 *  @brief UpdateSignatureContactless
 *  @discussion The callback to pass to startPay function with the result of Customer signature verification
 *  @param saleResponse sale response from the payment flow
 *  @param signatureImage captured Customers signature
 **/
typedef BOOL (^UpdateSignatureContactless)(WDAcceptSaleResponse* _Nullable saleResponse, UIImage* _Nullable signatureImage);

/**
 *  @brief RKIRequestCompletion
 *  @discussion Callback to present the RKIRequest details
 **/
typedef void (^RKIRequestCompletion)(WDAcceptTerminalRKIRequest* _Nullable , NSError* _Nullable );

#pragma mark - Extension protocols -

@protocol WDAcceptExtensionDelegate <NSObject>

@required
/**
 *  @brief Notification about current device connection status changes.
 *  @param  status Device's new connection status.
 **/
- (void)device:(WDAcceptTerminal*)device connectionStatusDidChange:(AcceptExtensionConnectionStatus)status;

/**
 *  @brief Notification that battery level of the connected device has changed
 *  @param batteryLevel Battery level in range from 0% to 100 % as integer
 **/
- (void)device:(WDAcceptTerminal*)device batteryLevelDidChange:(NSInteger)batteryLevel;

/**
 *  @brief Request the current device connection status.
 *  @param completion Block that will receive the device connection status.
 **/
- (void)connectionStatus:(DeviceConnectionStatusCompletion)completion;

/**
 *  @brief Request the battery level of the connected device. NOTE: this function should NOT be called if an operation in the device is ongoing (ie startPay has not finished)
 *  @param completion Block that will receive the battery level as a signed integer. If negative, then it indicates an error between three possible cases: "-1" for showing that the selected terminalID is wrong or that the device does not support battery level info. "-2" for indicating that the device does not respond (not ready or not connected). "-3" for indicating that the device is currently charging through a cable.
 **/
- (void)percentageBatteryRemaining:(BatteryLevelCallback)completion;

@end

#pragma mark External Accessory notifications protocol

@protocol WDAcceptExtensionEAAccessoryDelegate <NSObject>

@required
- (void)eaAccessoryDidConnect:(EAAccessory*)accessory;
- (void)eaAccessoryDidDisconnect:(EAAccessory*)accessory;

@end

#pragma mark PaymentTerminal protocol

@protocol WDAcceptPaymentTerminal <NSObject>
@required
/**
 *  @brief Start the payment process
 *  @discussion The blocks are used to intercept the Payment Flow:
 *      - *completion*: can be used to add terminal initialization errors to the completion block
 *      - *progress*: update the Payment Flow with the terminal progress (e.g. send the progress "Insert the card", "Enter PIN" etc.)
 *      - *onlineProcessor*: is used to process the Sale (Payment Flow) based on the card data supplied by terminal
 *      - *signature*: in the case the signature is needed if extension detects CVM requiring the signature collection the extension needs to invoke this callback with the WDAcceptSignatureRequest details so that the
 * Payment Flow asks the client app for signature collection
 *      - *appSelection*: in the case extension intercepts multiple ICC application on the card chip it can invoke this callback so that the Payment Flow asks the client app for ICC Application Selection
 *  @param completion Block that will be called at the very end of payment flow. It provides an AcceptTransaction object (that may be nil if unauthorised), AcceptExtendedProcessingInfo giving additional payment flow related information or a descriptive error
 *  @param progress Block with info to update the UI in base of alerts, errors or general info messages. Pure feedback for the user
 *  @param onlineProcessor Block returning the processed sale based on provided cardData, signatureImage, terminal information, extended processing info and passing back error - these are used by PaymentFlow to create the transaction to be submitted to backend
 *  @param configuration Block returning the terminal configuration  based on the terminal serial number and model , error is passed back- these are used by PaymentFlow to obtain the terminal configuration from backend
 *  @param signature Block providing AcceptSignatureRequest with relevant Cardholder data and expecting the callback (submitted by the client app) to provide the captured signature image
 *  @param appSelection Block informs that an application selection is needed with the chip card inserted.
 **/
- (void) startPay:(WDAcceptPaymentConfig* _Nonnull)config
         progress:(PaymentProgress _Nonnull)progress
  onlineProcessor:(PaymentOnlineProcessor _Nonnull)onlineProcessor
    configuration:(PaymentTerminalConfiguration _Nonnull)configuration
        signature:(PaymentSignature _Nonnull)signature
     appSelection:(PaymentCardApplicationSelectionRequest _Nonnull)appSelection
       completion:(SaleInternalCompletion _Nonnull)completion;

/**
 *  @brief Cancel the payment - close the terminal communication
 **/
- (void) cancelPay;

/**
 *  @brief Does this terminal support confirming the signature verification status by pressing X or O buttons ?
 *  @retun YES if extension supports verification confirmation
 **/
- (BOOL)canConfirmSignature;

@end

#pragma mark Updateable PaymentTerminal protocol

@protocol WDAcceptUpdateableTerminal
@required
/**
 *  @brief Upload the Configuration files or Firmware to this terminal
 *  @discussion The updateTerminal method in the SDK will download the necessary config or firmware files and invokes this method
 * which needs to implement upload of the binary files known to it.
 * The files are stored in the app documents directory/config for Configuraiton files upload or /firmware subdirectory for firmware upload and named in the terminal naming convention
 *  @param newTerminalInformation Terminal information
 *  @param updateType Update type Config | Firmware | CAKeys as invoked by client
 *  @param progress Update Progress to report back to the client
 *  @param completion Block that will report the terminal update status
 **/
- (void) updateTerminal:(WDAcceptTerminalHardwareInformation* _Nonnull)newTerminalInformation
             updateType:(AcceptTerminalUpdateTypeMask)updateType
               progress:(UpdateConfigurationProgress _Nonnull)progress
             completion:(UpdateTerminalCompletion _Nonnull)completion;

/**
 *  @brief Report the configuration updates status of the active terminal
 * If the update of the firmware or configuration was performed then the returned object holds the information
 * about the version firmware version and configuration version
 **/
- (WDAcceptTerminalHardwareInformation *)configurationUpdates;

/**
 *  @discussion Obtain the information from the terminal -  to be implemented by extension
 *  @param completion Reports serial number, version information as obtained from the terminal
 **/
-(void)getTerminalInformation:(void (^)(WDAcceptTerminalHardwareInformation*, NSError *))completion;

@end

#pragma mark WDAcceptRKI
/**
 * @brief WDAcceptRKI
 *  @discussion The extension object - terminal that supports Remote Key Injection
 **/
@protocol WDAcceptRKI <NSObject>
@required
/**
 *  @brief Does the extension require keys to be injected
 **/
-(void)isKeyExchangeNeeded:(void(^)(BOOL))completion;

/**
 *  @brief Extension provides request details for RKI
 *  @param completion Contains the RKI Request object and error
 **/
-(void)rkiRequest:(RKIRequestCompletion)completion;

/**
 *  @brief Extension processes the RKI data as provided by backend
 *  @param rkiArtifact - Remote Key details to be injected
 *  @param completion - to inform about the result of this operation
 **/
-(void)processRKIArtifact:(WDAcceptTerminalRKI*)rkiArtifact
               completion:(UpdateTerminalCompletion _Nonnull)completion;

@end

#pragma mark WDAcceptExtensionPrinting

@protocol WDAcceptExtensionPrinting <NSObject>

@required

/**
 *  @brief Print the receipt
 *  @param config print configuration
 *  @param progress printing progress
 *  @param completion Block executed at the end of the  method
 */
- (void)print:(WDAcceptPrinterConfig*)config
     progress:(PrinterStateUpdate)progress
   completion:(PrintCompletion)completion;

@optional
/**
 *  @brief Printer's paper status
 */
- (AcceptPrinterPaperStatus)printerPaperStatus;

@end

@protocol WDAcceptManagerPrinting <NSObject>
@required

/**
 *  @brief Print the receipt
 *  @param config print configuration
 *  @param progress printing progress
 *  @param completion Block executed at the end of the  method
 */
- (void)print:(WDAcceptPrinterConfig*)config
     progress:(PrinterStateUpdate)progress
   completion:(PrintCompletion)completion;

/**
 *  @brief Subscribe to printer updates. Manager holds weak reference.
 *  @param delegate Instance which conforms to WDAcceptPrinting protocol
 *  @param printer Printer device to subscribe to
 */
- (void)addPrinterManagerDelegate:(id<WDAcceptPrinting>)delegate forPrinter:(WDAcceptTerminal*)printer;

/**
 *  @brief Unsubscribe to printer status updates.
 *  @param delegate Instance used in addPrintingDelegate:forPrinter:
 */
- (void)removePrinterManagerDelegate:(id<WDAcceptPrinting>)delegate forPrinter:(WDAcceptTerminal*)printer;

@end

#pragma mark WDAcceptExtensionCashDrawerOperations

@protocol WDAcceptExtensionCashDrawerOperations <NSObject>
@required
/**
 *  @brief Open the cash drawer of the extension that supports it
 *  @param completion Block that informs about the command status
 **/
- (void)openCashDrawer:(ExtensionCommandCompletion)completion;

@end

@protocol WDAcceptCashDrawerManagerOperations <NSObject>
@required

/**
 *  @brief Open the cash drawer of the extension that supports it
 *  @param terminal The terminal with barcode scanner to which to connect to
 *  @param completion Block that informs about the command status
 **/
- (void)openCashDrawer:(WDAcceptTerminal*)terminal completion:(ExtensionCommandCompletion)completion;

@end

#pragma mark WDAcceptExtensionScanning

@protocol WDAcceptExtensionScanning <NSObject>
@required
- (void) connectBarcodeScannerWithCompletion:(ExtensionCommandCompletion)completion;

- (void) disconnectBarcodeScanner;

@end

@protocol WDAcceptManagerScanning <NSObject>
@required

/**
 *  @brief Subscribe to scanner notifications. Manager holds weak reference.
 *  @param delegate Instance which conforms to WDAcceptScanning protocol
 *  @param scanner Scanner device to subscribe to
 */
- (void)addScannerManagerDelegate:(id<WDAcceptScanning>)delegate forScanner:(WDAcceptTerminal*)scanner;

/**
 *  @brief Unsubscribe to scanner notifications.
 *  @param delegate Instance used in addScannerDelegate:forScanner
 */
- (void)removeScannerManagerDelegate:(id<WDAcceptScanning>)delegate forScanner:(WDAcceptTerminal*)scanner;

@end

NS_ASSUME_NONNULL_END
