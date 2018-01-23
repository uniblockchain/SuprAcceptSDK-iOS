//
//  AcceptSDK.h
//  AcceptSDK
//
//  Created by Danko, Radoslav on 15/10/15.
//  Copyright © 2015 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "WDAcceptEnvironment.h"
#import "WDAError.h"
#import "WDAcceptExtensionManager.h"
#import "WDAcceptUserManager.h"
#import "WDAcceptCashManager.h"
#import "WDAcceptSaleManager.h"
#import "WDAcceptProductCatalogueManager.h"
#import "WDAcceptCustomerManager.h"

NS_ASSUME_NONNULL_BEGIN

/**
  @brief Implement it if you would like to receive HTTP errors from web services
 */
@protocol AcceptSDKDelegate <NSObject>

@optional
/// HTTP errors from Client/Server communication
-(void)errorDidOccur:(NSError *)error;

@end

/**
 * @class AcceptSDK
 * @brief Wirecard Payment Acceptance SDK
 *
 * @discussion Enables your solution to Accept a wide range of Payment Methods (Cash, Card, Alipay, WeChat, Coupon) and offers advanced functionality to support your business
 * 
 * @b Sale @b Management  - WDAcceptSaleManager - Sales, Payments, Refunds, Sales history, Sale Statistics, Receipts
 *
 * @b Cash @b Management - WDAcceptCashManager - Cash flow, Shifts, Cash Registers, Z-Reports
 *
 * @b Device @b Management - WDAcceptTerminalManager, WDAcceptPrinterManager, WDAcceptCashDrawerManager, WDAcceptScannerManager - Devices support
 *
 * @b Inventory @b Management - WDAcceptProductCatalogueManager - Product Catalogues, Prices, Stocks, SAP ByDesign integration
 *
 * @b User @b Management - WDAcceptUserManager - Current User, Credential management
 *
 * @b Customer @b Management - WDAcceptCustomerManager - Members information
 * @remark Easy to integrate into your Mobile Payment application
 */
@interface AcceptSDK : NSObject

#pragma mark - SDK Initialisation
/// Default NSObject init is unavailable
- (nonnull instancetype)init __attribute__((unavailable("use [AcceptSDK sharedInstance] setupWithEnvironment:username:password:]")));
//Default NSObject new is unavailable
+ (nonnull instancetype)new __attribute__((unavailable("use [AcceptSDK sharedInstance] setupWithEnvironment:username:password:]")));

+ (AcceptSDK *)sharedInstance;

/**
 *  @brief Default constructor for acceptSDK
 *  @param environment backend config
 *  @param username username to login to the environment
 *  @param password password to login to the environment
 *  @param completion block called after the credentials (if existing) were validated
 **/
- (void)setupWithEnvironment:(AcceptEnvironment )environment
                    username:(NSString * _Nullable)username
                    password:(NSString * _Nullable)password
                  completion:(CurrentUserCompletion _Nullable)completion;

/**
 *  @brief Alternative constructor for acceptSDK - target custom instance (local installation) of Switch backend
 * This will work only after adding the server public certificate into SDK trusted certificates pool - ask mPOS support to include your custom certificate and obtain the SDK with your certificate built in
 * create the development version of SDK with required certificate
 *
 *  @param url backend url
 *  @param username username to login to the environment
 *  @param password password to login to the environment
 *  @param completion block called after the credentials (if existing) were validated
 **/
- (void)setupWithCustomURL:(NSString *)url
                  username:(NSString *)username
                  password:(NSString *)password
                completion:(CurrentUserCompletion _Nullable)completion;

/**
 *  @brief Setting "developer mode" as enabled shows more debug info, and also generates a text file in your app's document folder with details about the transaction (EMV data, etc). Any payment-critical content in this text files is encrypted, but it will show as plain text privacy-critical content, as cardholder name. You should never set this as TRUE in your official releases.
 *  @param isDevMode as YES for enabling it
 **/
- (void)setDevMode:(BOOL)isDevMode;

/**
 *  @brief Add the delegate to receive the notifications from the SDK
 *  @param delegate - object to receive the notifications
 **/
- (void)addDelegate:(id<AcceptSDKDelegate>)delegate ;

/**
 *  @brief Remove the delegate to stop receive the notifications from the SDK
 *  @param delegate - object to receive the notifications
 **/
- (void)removeDelegate:(id<AcceptSDKDelegate>)delegate;

+ (NSUInteger)ddLogLevel;

+ (void)ddSetLogLevel:(NSUInteger)logLevel;

#pragma mark - SDK Information
/**
 *  @brief Gets the current SDK version
 *  @returns SDK version
 **/
+ (NSString *)sdkVersion;

/**
 *  @brief Retrieve the version of Accept SDK
 **/
+ (NSString*)getVersion;

/**
 *  @brief Retrieve the dictionary of supported backends
 **/
+ (NSArray <WDAcceptEnvironmentConfiguration*>*)getSupportedEnvironments;

/**
 *  @brief Retrieve the version of Accept SDK and all available extensions
 **/
+ (NSDictionary*)getVersions;

#pragma mark - Current User
/// User whos credentials were used to setup the environment
@property (nonatomic,readonly,nullable) WDAcceptMerchantUser *authenticatedUser;
/// Cashier details for the authenticated user
@property (nonatomic,readonly,nullable) WDAcceptMerchantCashier *cashier;

#pragma mark - Device management
/**
 *  @brief Printer Manager - supports Printer related functions
 **/
@property (nonatomic,readonly) WDAcceptPrinterManager *printerManager;

/**
 *  @brief Terminal Manager - supports Terminal related functions
 **/
@property (nonatomic,readonly) WDAcceptTerminalManager * terminalManager;

/**
 *  @brief Cash Drawer Manager - supports Cash Drawer related functions
 **/
@property (nonatomic,readonly) WDAcceptCashDrawerManager *cashDrawerManager;

/**
 *  @brief Pistol Scanner Manager - supports Pistol Scanner related functions
 **/
@property (nonatomic,readonly) WDAcceptScannerManager *scannerManager;

#pragma mark - User management
/**
 *  @brief User management functionality
 */
@property (nonatomic,readonly) WDAcceptUserManager *userManager;

#pragma mark - Cash management
/**
 *  @brief Cash management functionality
 */
@property (nonatomic,readonly) WDAcceptCashManager *cashManager;

#pragma mark - Sale
/**
 *  @brief Sale functionality
 */
@property (nonatomic,readonly) WDAcceptSaleManager *saleManager;

#pragma mark - Inventory
/**
 *  @brief Inventory functionality
 */
@property (nonatomic,readonly) WDAcceptProductCatalogueManager *inventoryManager;

#pragma mark - Customer management
/**
 *  @brief Customer management functionality
 */
@property (nonatomic,readonly) WDAcceptCustomerManager *customerManager;
@end

NS_ASSUME_NONNULL_END
