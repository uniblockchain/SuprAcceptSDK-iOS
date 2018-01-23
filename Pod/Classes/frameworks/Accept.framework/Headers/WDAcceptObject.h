//
//  WDAcceptObject.h
//  acceptSDK
//
//  Created by Danko, Radoslav on 30/08/16.
//  Copyright © 2016 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  @class WDAcceptObject
 *  @brief Accept custom object
 *  @discussion Accept Generic Object - supports runtime object [property/values] description
 **/
@interface WDAcceptObject : NSObject

- (nullable instancetype)initWithCoder:(nonnull NSCoder *)coder NS_UNAVAILABLE;

/**
 *  @brief Returns value for property named 'key'
 *  @param key Name of the property
 *  @return value as id
 **/
- (nullable id)safeValueForKey:(nonnull NSString*)key notFoundValue:(nullable id)defaultValue;

@end
