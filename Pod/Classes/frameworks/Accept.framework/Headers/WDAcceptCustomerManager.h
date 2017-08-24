//
//  WDAcceptCustomerManager.h
//  acceptSDK
//
//  Created by Danko, Radoslav on 19/10/16.
//  Copyright © 2016 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WDADataTypes.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  @class WDAcceptCustomerManager
 *  @brief Customer Management
 */
@interface WDAcceptCustomerManager : NSObject
-(instancetype )initWithSDK:(id)sdk;
#pragma mark - Member information
/**
 *  @brief Retrieve members information - based on the search criteria
 *  @param memberId - search by MemberID
 *  @param surname - search by Surname (Family Name)
 *  @param firstName - search by First Name or any other known names
 *  @param exactMatch - exact match (whole string) for the query parameters is used
 *  @param completion Block executed at the end of the member information method
 **/
-(void)memberInformation:(NSString * _Nullable)memberId
                 surname:(NSString * _Nullable)surname
               firstName:(NSString * _Nullable)firstName
              exactMatch:(BOOL)exactMatch
              completion:(MembersCompletion _Nonnull)completion;


@end

NS_ASSUME_NONNULL_END
