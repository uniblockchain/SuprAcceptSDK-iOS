//
//  WDALogger.h
//  acceptSDK
//
//  Created by Timko, Marek on 29/12/2016.
//  Copyright © 2016 Wirecard. All rights reserved.
//

#ifndef WDALogger_h
#define WDALogger_h

#import <CocoaLumberjack/CocoaLumberjack.h>
#import <CocoaLumberjack/DDDispatchQueueLogFormatter.h>

#define LOG_ASYNC_ENABLED YES
#define WDA_LOG_CONTEXT 1001

extern DDLogLevel wdaLogLevel;

#define WDALogError(frmt, ...)   LOG_MAYBE(NO,                wdaLogLevel, DDLogFlagError,   WDA_LOG_CONTEXT, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define WDALogWarn(frmt, ...)    LOG_MAYBE(LOG_ASYNC_ENABLED, wdaLogLevel, DDLogFlagWarning, WDA_LOG_CONTEXT, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define WDALogInfo(frmt, ...)    LOG_MAYBE(LOG_ASYNC_ENABLED, wdaLogLevel, DDLogFlagInfo,    WDA_LOG_CONTEXT, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define WDALogDebug(frmt, ...)   LOG_MAYBE(LOG_ASYNC_ENABLED, wdaLogLevel, DDLogFlagDebug,   WDA_LOG_CONTEXT, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define WDALogVerbose(frmt, ...) LOG_MAYBE(LOG_ASYNC_ENABLED, wdaLogLevel, DDLogFlagVerbose, WDA_LOG_CONTEXT, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)

@interface WDALogFormatter : DDDispatchQueueLogFormatter

- (NSString *)formatLogMessage:(DDLogMessage *)logMessage;

@end

#endif /* WDALogger_h */
