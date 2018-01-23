//
//  WDAMiuraLocalizationManager.h
//  WDAMiuraExtension
//
//  Created by Pawel Grzmil on 29/03/2017.
//  Copyright © 2017 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum WDAMiuraTextId : NSUInteger {
    WDAMiuraTextIdSwipeOrInsert,
    WDAMiuraTextIdUseChip,
    WDAMiuraTextIdUseMagStripe,
    WDAMiuraTextIdSignatureCheck,
    WDAMiuraTextIdSignatureVerified,
    WDAMiuraTextIdSignatureRejected,
    WDAMiuraTextIdRemoveCard,
    WDAMiuraTextIdProcessing,
    WDAMiuraTextIdOnlinePinSuccess,
    WDAMiuraTextIdOnlinePinFailed,
    WDAMiuraTextIdTransactionApproved,
    WDAMiuraTextIdTransactionDeclined
} WDAMiuraTextId;

@interface WDAMiuraLocalizationManager : NSObject

- (void)setLanguage:(NSString *)currentLanguage;
- (NSString *)getText:(WDAMiuraTextId)iid;
- (NSString *)currentLanguagePreference;

@end
