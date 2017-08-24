//
//  TestUtils.h
//  acceptSDK
//
//  Created by Danko, Radoslav on 17/10/15.
//  Copyright © 2015 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Accept/Accept.h>
#import <UIKit/UIKit.h>


@interface TestUtils : NSObject
+(NSString *)basicAuthenticationFromConfig;
+(NSDictionary *)defaultAcceptEnvironment;
+(NSString *)uniqueID;
+ (UIImage *) signatureImageFromText:(NSString *)signatureText;
+ (UIImage *) signatureImageFromText:(NSString *)signatureText withSize:(CGSize)imageSize;

@end
