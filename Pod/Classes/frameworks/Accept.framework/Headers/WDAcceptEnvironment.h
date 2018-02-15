//
//  AcceptEnvironment.h
//  acceptSDK
//
//  Created by Danko, Radoslav on 15/12/15.
//  Copyright © 2015 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
NS_ASSUME_NONNULL_BEGIN
/**
 *  @brief Accept Environments enumerator
 **/
typedef NS_ENUM(NSUInteger, AcceptEnvironment) {
    AcceptEnvironmentUnknown = 0,
    AcceptEnvironmentDevelopment = 1,
    AcceptEnvironmentDevelopment1 = 2,
    AcceptEnvironmentQA_STK03 = 3,
    AcceptEnvironmentQA = 4,
    AcceptEnvironmentTEST = 5,
    AcceptEnvironmentPublicTest = 6,
    AcceptEnvironmentProd = 7
};

/**
 *  @brief Accept Environment Types enumerator
 **/
typedef NS_ENUM(NSUInteger, AcceptEnvironmentType) {
    AcceptEnvironmentTypeUnknown = 0,
    AcceptEnvironmentTypeDEV = 1,
    AcceptEnvironmentTypeQA = 2,
    AcceptEnvironmentTypeTEST = 3,
    AcceptEnvironmentTypePUBLICTEST = 4,
    AcceptEnvironmentTypePROD = 5
};

/**
 *  @class WDAcceptEnvironmentConfiguration
 *  @brief Wirecard Accept Environment configuration 
 *  @discussion Accept Environment to be used for ReST services \n
 *  AcceptEnvironmentPublicTest to be used for Integration Tests and Development \n
 *  AcceptEnvironmentTypePROD to be used for Production application
 **/
@interface WDAcceptEnvironmentConfiguration : NSObject
/// Default NSObject init is unavailable
-(nonnull instancetype)init __attribute__((unavailable("use initWithUrl")));
/// environment as one of AcceptEnvironment
@property (nonatomic,readonly) AcceptEnvironment environment;
/// environmentType type as one of AcceptEnvironmentType
@property (nonatomic, readonly) AcceptEnvironmentType environmentType;
/// url of this environment
@property (nonatomic,strong,readonly) NSString *url;
/// Create the enironment from known URL
-(instancetype _Nullable)initWithUrl:(NSString *_Nonnull)url NS_DESIGNATED_INITIALIZER;
@end

/**
 *  @brief Get URL for the specified Accept Environment
 *  @param environment one of AcceptEnvironment environments
 **/
NSString *AcceptEnvironmentGetBackendUrl(AcceptEnvironment environment);

/**
 *  @brief Get AcceptEnvironment for the specified URL
 *  @param url of the Accept backend
 **/
AcceptEnvironment AcceptEnvironmentFromUrl(NSString *url);

/**
 *  @brief Get list of supported Accept Environments as array of WDAcceptEnvironmentConfiguration
 **/
NSArray <WDAcceptEnvironmentConfiguration *>* AcceptEnvironments(void);

NS_ASSUME_NONNULL_END
