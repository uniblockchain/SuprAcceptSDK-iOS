//
//  NSFileManager+Helpers.h
//  acceptSDK
//
//  Created by Danko, Radoslav on 11/11/15.
//  Copyright © 2015 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSFileManager (Helpers)
+(BOOL)deleteDirectory:(NSString *)directoryPath error:(NSError **)error;
@end
