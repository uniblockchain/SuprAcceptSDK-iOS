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
 *  @class WDAcceptSaleItemCore
 *  @discussion Sale Item details Core class
 **/
@interface WDAcceptSaleItemCore : WDAcceptObject <NSCopying,NSCoding>
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
@property (nonatomic, strong) NSString * _Nullable itemDescription;
/**
 */
@property (nonatomic, strong) NSDecimalNumber * _Nonnull unitPrice;
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
 */
@property (nonatomic, readonly) NSDecimalNumber* itemTotal;
/**
 */
+ (NSString *)typeAsStringFromEnum:(AcceptSaleItemType)type;

@end

/**
 *  @class WDAcceptSaleItem
 *  @discussion Sale Item details
 **/
@interface WDAcceptSaleItem : WDAcceptSaleItemCore
/**
 */
@property (nonatomic, strong) NSString * _Nullable externalProductId;
/**
 */
@property (nonatomic, strong, readonly) NSDecimalNumber * _Nullable unitPriceModified;
/**
 * If product ID is set for this item then item can't be edited by Merchant as all details of the item are defined in the inventory
 */
@property (nonatomic, readonly) BOOL editable;
/**
 * @brief Percentage rate to base the unitPrice calculation on - applicable for Item Discount
 */
@property (nullable, nonatomic, strong) NSDecimalNumber *discountRate;
/**
 * discounted total price
 */
@property (nonatomic, readonly) NSDecimalNumber* itemTotalDiscounted;

@end

/**
 *  @class WDAcceptSaleServiceCharge
 *  @discussion Sale Service Charge details
 **/
@interface WDAcceptSaleServiceCharge : WDAcceptSaleItemCore
/**
 * @brief Percentage rate to base the unitPrice calculation on - applicable for Service charge
 */
@property (nullable, nonatomic, strong) NSDecimalNumber *serviceChargeRate;
@end

/**
 *  @class WDAcceptSaleFlatDiscount
 *  @discussion Sale Flat Discount details
 **/
@interface WDAcceptSaleFlatDiscount : WDAcceptSaleItemCore
/**
 * @brief Percentage rate to base the unitPrice calculation on - applicable for Item Discount
 */
@property (nullable, nonatomic, strong) NSDecimalNumber *discountRate;
@end

/**
 *  @class WDAcceptSaleCoupon
 *  @discussion Sale Coupon details
 **/
@interface WDAcceptSaleCoupon : WDAcceptSaleItemCore
/**
 */
@property (nonatomic, strong) NSString * _Nullable couponId;
@end

NS_ASSUME_NONNULL_END
