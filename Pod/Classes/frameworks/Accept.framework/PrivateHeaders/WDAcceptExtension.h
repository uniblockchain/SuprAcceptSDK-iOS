//
//  acceptSDK
//
//  Created by Danko, Radoslav on 15/10/15.
//  Copyright © 2015 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ExternalAccessory/EAAccessory.h>
#import "WDAError.h"
#import "WDAcceptExtensionProtocols.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - Constants

#define BatteryLevelUnsupported                         -1
#define BatteryLevelUnknown                             -2
#define kUISupportedExternalAccessoryProtocols          @"UISupportedExternalAccessoryProtocols"
#define kAcceptExtensionEAAccessoryKey                  @"EAAccessory"

#pragma mark - EAAccessory Helper Category

@interface EAAccessory (WDAcceptExtension)
@property (nonatomic, readonly, strong) NSString *wdaef_serialNumber;
@end

#pragma mark - WDAcceptExtension

/**
 *  @class WDAcceptExtension
 *  @discussion The extension object - all basic terminal methods
 **/
@interface WDAcceptExtension : NSObject

@property (nonnull, nonatomic, readonly) WDAcceptTerminal *terminal;
@property (nullable, nonatomic, weak, readonly) id delegate;
@property (nonatomic) BOOL isDevMode;
/// Default NSObject init is unavailable
-(nonnull instancetype)init __attribute__((unavailable("use initWithTerminal:delegate:")));
//Default NSObject new is unavailable
+(nonnull instancetype)new __attribute__((unavailable("use initWithTerminal:delegate:")));
/**
 *  @brief Initialize the extension
 *  @param terminal terminal with which to initialize the extension
 **/
-(instancetype _Nullable)initWithTerminal:(WDAcceptTerminal * _Nullable)terminal delegate:(id _Nullable)delegate NS_DESIGNATED_INITIALIZER;

/**
 *  @brief Request the battery level of the connected terminal. NOTE: this function should NOT be called if an operation in the terminal is ongoing (ie startPay has not finished)
 *  @param completion Block that will receive the battery level as a signed integer. If negative, then it indicates an error between three possible cases: "-1" for showing that the selected terminalID is wrong or that the terminal does not support battery level info. "-2" for indicating that the terminal does not respond (not ready or not connected). "-3" for indicating that the terminal is currently charging through a cable.
 **/
- (void)percentageBatteryRemaining:(BatteryLevelCallback _Nonnull)completion;

/**
 *  @brief Request the current terminal connection status.
 *  @param completion Block that will receive the device connection status.
 **/
- (void)connectionStatus:(DeviceConnectionStatusCompletion _Nonnull)completion;

#pragma mark Support functions

/**
 *  @brief Is the extension supported by SDK
 **/
+ (BOOL)isSupported;

/**
 *  @brief Helper method: Is the extension enabled in configuration xml
 **/
+ (BOOL)isEnabled:(NSString * _Nonnull)keyPath;
/**
 *  @brief Get extension alternative name
 **/
+ (NSString * _Nullable)getExtensionAlternativeName:(NSString * _Nonnull)keyPath;

#pragma mark Info functions
/**
 *  @brief Report the current terminal model name
 **/
- (NSString* _Nullable) getModelName; //TODO: change to @property (nullable, nonatomic, readonly) NSString *modelName ?
/**
 *  @brief Report the extension version
 **/
+ (NSString* _Nonnull)getVersion;
/**
 *  @brief Report the extension vendor
 **/
+ (WDAcceptVendor * _Nullable)extensionVendor;

@end

#pragma mark - WDAcceptEAAccessoryExtension

/**
 *  @class WDAcceptEAAccessoryExtension
 *  @discussion The extension object for BT accessories - all basic Extension + BT accessory methods
 **/
@interface WDAcceptEAAccessoryExtension : WDAcceptExtension <WDAcceptExtensionEAAccessoryDelegate>

@property (nullable, nonatomic, readonly) EAAccessory* accessory;
/// Default NSObject init is unavailable
-(nonnull instancetype)init __attribute__((unavailable("use initWithTerminal:delegate:")));
//Default NSObject new is unavailable
+(nonnull instancetype)new __attribute__((unavailable("use initWithTerminal:delegate:")));

/**
 *  @brief Initialize the extension
 *  @param terminal terminal with which to initialize the extension
 **/
-(instancetype _Nullable)initWithTerminal:(WDAcceptTerminal * _Nullable)terminal delegate:(id _Nullable)delegate NS_DESIGNATED_INITIALIZER;

#pragma mark Support functions

/**
 *  @brief Acquire an array of available terminals
 *  @param accessories Connected external accessories from [EAAccessoryManager sharedAccessoryManager]
 *  @return The array of terminals found - objects of class WDAcceptTerminal
 **/
+ (NSArray<WDAcceptTerminal*>*)supportedDevicesForAccessories:(NSArray<EAAccessory*>*)accessories;

/**
 *  @brief Accessory's Protocol which is supported by the extension. Returns nil if no external accessory is used (Not a BT device)
 **/
+ (NSArray<NSString *> * _Nullable)supportedAccessoryProtocol;

@end

#pragma mark - WDAcceptUpdateablePaymentTerminalExtension

/**
 *  @class WDAcceptUpdateablePaymentTerminalExtension
 *  @discussion The extension object for payment terminals that supports firmware updates
 **/
@interface WDAcceptUpdateableTerminalExtension : WDAcceptEAAccessoryExtension<WDAcceptUpdateableTerminal>

@end

NS_ASSUME_NONNULL_END
