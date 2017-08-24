//
//  NSBundle+Language.h
//  iCashier
//
//  Created by Fortes, Francisco on 2/26/15.
//  Copyright (c) 2015 andromeda. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSBundle(Language)
+(void)setLanguage:(NSString*)language;
+(void)setLanguage:(NSString*)language sourceBundleName:(NSString *)sourceBundleName;
@end
