//
//  WDAcceptProductCatalogue.h
//  acceptSDK
//
//  Created by Danko, Radoslav on 22/01/16.
//  Copyright © 2016 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "WDAcceptObject.h"

@class WDAcceptUnitPrice,WDAcceptTaxCategory, WDAcceptAddress;

NS_ASSUME_NONNULL_BEGIN
/**
 *  @class WDAcceptProductCatalogueCore
 *  @brief  Product Catalogue core object
 **/
@interface WDAcceptProductCatalogueCore : WDAcceptObject <NSCoding>
@property (nullable, nonatomic, strong) NSString *productCatalogueId;
@property (nullable, nonatomic, strong) NSString *name;
@property (nullable, nonatomic, strong) NSDecimalNumber *discount;
@property (nullable, nonatomic, strong) NSNumber *version;
@end

/**
 *  @class WDAcceptProductCatalogue
 *  @discussion  Product Catalogue object
 **/
@interface WDAcceptProductCatalogue : WDAcceptProductCatalogueCore

@property (nullable, nonatomic, strong) NSString *merchantId;
@property (nullable, nonatomic, strong) NSString *optionalDescription;
@property (nullable, nonatomic, strong) NSDate *upsertDate;
@property (nullable, nonatomic, strong) NSString *type;

/**
 *  @brief Create Product Catalogue
 *  @param merchantId Merchant ID for under which to create the product catalogue
 *  @param name Product Catalogue name
 *  @param description Product Catalogue description
 *  @return new Product Catalogue
 **/
-(instancetype)initWithMerchantId:(NSString *)merchantId
                             name:(NSString *)name
                      description:(NSString *)description;

/**
 *  @brief Create Product Catalogue
 *  @param merchantId Merchant ID for under which to create the product catalogue
 *  @param name Product Catalogue name
 *  @param description Product Catalogue description
 *  @param discount Product Catalogue discount
 *  @return new Product Catalogue
 **/
-(instancetype)initWithMerchantId:(NSString *)merchantId
                             name:(NSString *)name
                      description:(nullable NSString *)description
                         discount:(nullable NSDecimalNumber *)discount;
@end

/**
 *  @class WDAcceptProductCatalogueCategory
 *  @brief  Product Catalogue Category object
 **/
@interface WDAcceptProductCatalogueCategory : WDAcceptProductCatalogueCore
/**
 *  @brief Create Product Category
 *  @param parentId Parent Category ID under which to create the new category - will become root category if nil specified
 *  @param name Product Category name
 *  @param displayOrder ordering sequence of the category - used when displaying the categories
 *  @return new Product Category
 **/
-(instancetype)initWithParentCategoryId:(nullable NSString *)parentId
                                   name:(NSString *)name
                           displayOrder:(NSNumber *)displayOrder;

/**
 *  @brief Create Product Category
 *  @param parentId Parent Category ID under which to create the new category - will become root category if nil specified
 *  @param name Product Category name
 *  @param discount discount Category discount to be applied on all subcategories and products
 *  @param displayOrder ordering sequence of the category - used when displaying the categories
 *  @return new Product Category
 **/
-(instancetype)initWithParentCategoryId:(nullable NSString *)parentId
                                   name:(NSString *)name
                               discount:(nullable NSDecimalNumber *)discount
                           displayOrder:(NSNumber *)displayOrder;

@property (nullable, nonatomic, strong) NSString *categoryId;
@property (nullable, nonatomic, strong) NSString *parentCategoryId;
@property (nullable, nonatomic, strong) NSNumber *displayOrder;
@property (nullable, nonatomic, strong) NSArray <WDAcceptProductCatalogueCategory *> *subcategories;
@end

/**
 *  @class WDAcceptBarCodeType
 *  @brief  Bar Code type
 **/
@interface WDAcceptBarCodeType : WDAcceptObject <NSCoding>
@property (nonatomic, strong) NSString *barCodeTypeId;
@property (nonatomic, strong) NSString *barCodeTypeName;
@end

/**
 *  @class WDAcceptProductCatalogueProduct
 *  @brief Product details
 **/
@interface WDAcceptProductCatalogueProduct: WDAcceptObject <NSCoding>
/**
 *  @brief Create Product
 *  @param name Product Name
 *  @param unitPrices the product Unit prices
 *  @param taxCategory Tax Category for this product
 *  @return new Product
 **/
-(instancetype)initWithProductName:(NSString *)name
                        unitPrices:(NSArray <WDAcceptUnitPrice*> *)unitPrices
                       taxCategory:(WDAcceptTaxCategory*)taxCategory;

/**
 *  @brief Create Product
 *  @param name Product Name
 *  @param unitPrices the product Unit prices
 *  @param taxCategory Tax Category for this product
 *  @param externalId External ID - product id recognized in external system - ERP or other
 *  @return new Product
 **/
-(instancetype)initWithProductName:(NSString *)name
                        unitPrices:(NSArray <WDAcceptUnitPrice*> *)unitPrices
                       taxCategory:(WDAcceptTaxCategory*)taxCategory
                        externalId:(NSString*)externalId;

/**
 *  @brief Create Product
 *  @param name Product Name
 *  @param unitPrices the product Unit prices
 *  @param taxCategory Tax Category for this product
 *  @param productCategories Categorize this product - more than one category can be assigned
 *  @param externalId External ID - product id recognized in external system - ERP or other
 *  @return new Product
 **/
-(instancetype)initWithProductName:(NSString *)name
                        unitPrices:(NSArray <WDAcceptUnitPrice*> *)unitPrices
                       taxCategory:(WDAcceptTaxCategory*)taxCategory
                 productCategories:(NSArray <WDAcceptProductCatalogueCategory*> *)productCategories
                        externalId:(NSString*)externalId;

/**
 *  @brief Create Product
 *  @param name Product Name
 *  @param unitPrices the product Unit prices
 *  @param taxCategory Tax Category for this product
 *  @param productCategories Categorize this product - more than one category can be assigned
 *  @param externalId External ID - product id recognized in external system - ERP or other
 *  @param discount discount Product discount to be applied on certain product
 *  @return new Product
 **/
-(instancetype)initWithProductName:(NSString *)name
                        unitPrices:(NSArray <WDAcceptUnitPrice*> *)unitPrices
                       taxCategory:(WDAcceptTaxCategory*)taxCategory
                 productCategories:(NSArray <WDAcceptProductCatalogueCategory*> *)productCategories
                        externalId:(NSString*)externalId
                          discount:(nullable NSDecimalNumber *)discount;

@property (nullable, nonatomic, strong) WDAcceptBarCodeType *barCodeType;
@property (nullable, nonatomic, strong) NSString *barCodeValue;
@property (nullable, nonatomic, strong) NSString *externalId;
@property (nullable, nonatomic, strong) NSDecimalNumber *discount;
@property (nullable, nonatomic, strong) NSString *imageId;
@property (nullable, nonatomic, strong) NSString *productId;
@property (nullable, nonatomic, strong) NSString *productName;
@property (nullable, nonatomic, strong) NSArray <WDAcceptProductCatalogueCategory*> *productCategories;
@property (nonatomic, strong) NSArray <WDAcceptUnitPrice*> *productUnitPrices;
@property (nonatomic, strong) WDAcceptTaxCategory *taxCategory;
@property (nonatomic, strong) NSNumber *version;
@end

/**
 *  @class WDAcceptProductAvailability
 *  @brief Product availability
 **/
@interface WDAcceptProductAvailability: WDAcceptObject <NSCoding>
@property (nonatomic, strong) NSString *externalProductId;
@property (nonatomic, strong) NSNumber *stockQuantity;
@end

/**
 *  @class WDAcceptProductStock
 *  @brief Product stocks
 **/
@interface WDAcceptProductStock: WDAcceptObject <NSCoding>
@property (nonatomic, strong) NSArray <WDAcceptProductAvailability*>* productsAvailability;
@property (nonatomic, strong) NSString *siteId;
@property (nonatomic, strong) WDAcceptAddress *address;
@end

/**
 *  @class WDAcceptProductCatalogueDiscount
 *  @brief Product Catalogue discount - flat discount
 **/
@interface WDAcceptProductCatalogueDiscount: WDAcceptObject <NSCoding>
@property (nullable,nonatomic, strong) NSNumber *flatDiscount;
@end

/**
 *  @class WDAcceptProductPrice
 *  @brief ERP product price information
 **/
@interface WDAcceptProductPrice : WDAcceptObject <NSCoding>
/**
 */
@property (nullable, nonatomic, strong) NSString *currencyCode;
/**
 */
@property (nullable, nonatomic, strong) NSString *externalProductId;
/**
 */
@property (nullable, nonatomic, strong) NSDecimalNumber *unitPrice;

@end

NS_ASSUME_NONNULL_END
