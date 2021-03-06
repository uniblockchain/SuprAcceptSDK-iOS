//
//  WDAcceptLocalizationManager.h
//  Accept
//
//  Created by Danko, Radoslav on 28/11/2017.
//  Copyright © 2017 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

extern const int64_t kWDLANGUAGE_BUNDLE_KEY;

/**
 *  @class WDAcceptLocalizationManager
 *  @brief Localize Receipt and Z-Reports produced from SDK
 **/
@interface WDAcceptLocalizationManager : NSObject

/// List of supported languages - for Receipt | Z-Report  localization
- (NSArray<NSString *> *)supportedLanguages;
/// Set the required language - for Receipt | Z-Report  localization
- (void)setLanguage:(NSString *)language;
@end


NSString* WDLocalizedString(NSString *key);

