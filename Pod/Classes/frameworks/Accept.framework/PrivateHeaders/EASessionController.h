//
//  Accept for iOS
//
//  Created by Radoslav Danko and Francisco Fortes.
//  Copyright (c) 2016 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ExternalAccessory/ExternalAccessory.h>


@interface EASessionController : NSObject<EAAccessoryDelegate, NSStreamDelegate>

- (void) open:(EAAccessory*)accessory protocol:(NSString*)protocol completion:(void(^)(BOOL, NSError*))completion;
- (void) close;
- (void) write:(NSData *)data;
- (void) discardContentOfReadBuffer;

@property (nonatomic, strong) void (^dataProcessor)(NSMutableData*);

@end
