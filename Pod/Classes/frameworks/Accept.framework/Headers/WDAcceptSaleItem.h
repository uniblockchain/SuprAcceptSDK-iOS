//
//  WDAcceptSaleItem.h
//  acceptSDK
//
//  Created by Danko, Radoslav on 16/02/16.
//  Copyright © 2016 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WDAcceptObject.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  @brief AcceptSaleItemType
 *  @discussion Enumerator with the Item types.
 **/
typedef NS_ENUM(NSInteger, AcceptSaleItemType ) {
    AcceptSaleItemTypePurchase = 0,
    AcceptSaleItemTypeGratuity ,
    AcceptSaleItemTypeServiceCharge,
    AcceptSaleItemTypeDiscount,
    AcceptSaleItemTypeCoupon
};

/**
 *  @class WDAcceptSaleItem
 *  @discussion Sale Item details
 **/
@interface WDAcceptSaleItem : WDAcceptObject <NSCopying,NSCoding>
/// Default NSObject init is unavailable
-(nonnull instancetype)init __attribute__((unavailable("use initForSale")));
/**
 */
- (id)initWithCoder:(NSCoder *)decoder NS_DESIGNATED_INITIALIZER;
/**
 */
-(instancetype)initForSale:(id)sale NS_DESIGNATED_INITIALIZER;
/**
 */
@property (nonatomic, strong) NSString * _Nullable externalProductId;
/**
 */
@property (nonatomic, strong) NSString * _Nullable itemDescription;
/**
 */
@property (nonatomic, strong) NSDecimalNumber * _Nonnull unitPrice;
/**
 */
@property (nonatomic, strong) NSDecimalNumber * _Nullable unitPriceModified;
/**
 */
@property (nonatomic) NSInteger quantity; 
/**
 */
@property (nonatomic, strong) NSDecimalNumber * _Nonnull taxRate;
/**
 */
@property (nonatomic) AcceptSaleItemType itemType;
/**
 * If product ID is set for this item then item can't be edited by Merchant as all details of the item are defined in the inventory
 */
@property (nonatomic, readonly) BOOL editable;
/**
 * If product ID is set for this item then item can't be edited by Merchant as all details of the item are defined in the inventory
 */
@property (nonatomic, readonly) BOOL discountModified;
/**
 * @brief Percentage rate to base the unitPrice calculation on - applicable for Service charge and Discount
 */
@property (nullable, nonatomic, strong) NSDecimalNumber *itemRate;
/**
 */
-(NSDecimalNumber *)itemTotal;
/**
 */
-(NSDecimalNumber *)itemTotalDiscounted;
/**
 */
+ (NSString *)typeAsStringFromEnum:(AcceptSaleItemType)type;

@end
NS_ASSUME_NONNULL_END
