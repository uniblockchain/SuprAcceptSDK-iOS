//
//  WDAProtocols.h
//  acceptSDK
//
//  Created by Timko, Marek on 05/12/2016.
//
//
#import "WDADataTypes.h"

NS_ASSUME_NONNULL_BEGIN

/**
  @brief Device Manager Delegation
 */
@protocol WDAcceptManagerDelegate <NSObject>
@optional

/**
 *  @brief Notification about current device connection status changes.
 *  @param device Device description.
 *  @param status Device's new connection status.
 **/
- (void)device:(WDAcceptTerminal*)device connectionStatusDidChange:(AcceptExtensionConnectionStatus)status;

/**
 *  @brief Notification that battery level of the connected device has changed
 *  @param device Device description.
 *  @param batteryLevel Battery level in range from 0% to 100 % as integer
 **/
- (void)device:(WDAcceptTerminal*)device batteryLevelDidChange:(NSInteger)batteryLevel;

@end

/**
  @brief Print Manager Delegation
 */
@protocol WDAcceptPrinting <WDAcceptManagerDelegate>
@optional

/**
 *  @brief Called when printer's paper status change is detected
 *  @param device Device description.
 *  @param status The new printer's paper status
 */
- (void)device:(WDAcceptTerminal*)device paperStatusUpdated:(AcceptPrinterPaperStatus)status;

@end

/**
  @brief Scanner Manager Delegation
 */
@protocol WDAcceptScanning <WDAcceptManagerDelegate>
@optional

/**
 *  @brief Called when printer's paper status change is detected
 *  @param device Device description.
 *  @param barcodeReceived Data received from the scanner
 *  @param symbology Scanned barcode data symbology
 */
- (void)device:(WDAcceptTerminal*)device barcodeReceived:(NSString *)barcodeReceived symbology:(AcceptBarcodeSymbology)symbology;

@end

/**
 *   @brief Sale Manager Payment Delegation
 *   @discussion Implement Payment flow Delegate methods to receive events from Payment Flow
 */
@protocol WDAcceptPaymentDelegate <NSObject>
@optional
/**
 * @brief Information about the payment process progress
 * @param paymentProgress progress enumerator
 **/
-(void)progress:(AcceptStateUpdate) paymentProgress;
/**
 * @brief In case of payment which requires capturing of a customer signature and return the signature data
 * @param signatureRequest is sent to caller and requires sending of collected signature image in sendCollectedSignature callback
 **/
-(void)collectSignature:(WDAcceptSignatureRequest * _Nonnull ) signatureRequest;
/**
 * @brief In case of payment which requires customer payment confirmation
 * @param confirmationType designates the type of customer's confirmation Signature | WeChat password ...
 * @param paymentConfirmationResult is provided by caller and carries the customer's confirmation Yes/No
 **/
-(void)confirm:(AcceptPaymentConfirmationType )confirmationType
paymentConfirmationResult:(PaymentConfirmationResult   _Nullable )paymentConfirmationResult;
/**
 * @brief In case of Card payment which requires customer selection of Card application
 * @param appSelectionRequest is sent to caller and requires sending of selected card application in selectCardApplication callback
 **/
-(void)cardApplication:(WDAcceptAppSelectionRequest * _Nonnull )appSelectionRequest;
@required
/**
 * @brief The event sent at the end of the payment flow
 * @param saleResponse contains the completed Sale
 * @param saleResponseError contains the error occured during the payment flow
 **/
-(void)completion:(WDAcceptSaleResponse* _Nullable) saleResponse
saleResponseError:(NSError* _Nullable) saleResponseError;
@end
NS_ASSUME_NONNULL_END
