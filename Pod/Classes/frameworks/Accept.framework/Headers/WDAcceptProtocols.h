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

NS_ASSUME_NONNULL_END
