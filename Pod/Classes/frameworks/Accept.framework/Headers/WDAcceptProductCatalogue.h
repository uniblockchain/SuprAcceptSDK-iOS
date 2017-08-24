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
 *  @discussion  Product Catalogue core object
 **/
@interface WDAcceptProductCatalogueCore : NSObject <NSCoding>
@property (nullable, nonatomic, retain) NSString *productCatalogueId;
@property (nullable, nonatomic, retain) NSNumber *version;
@end

/**
 *  @class WDAcceptProductCatalogue
 *  @discussion  Product Catalogue object
 **/
@interface WDAcceptProductCatalogue : WDAcceptProductCatalogueCore
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

@property (nullable,nonatomic, retain) NSString *merchantId;
@property (nullable,nonatomic, retain) NSString *productCatalogueName;
@property (nullable,nonatomic, retain) NSString *productCatalogueDescription;
@property (nullable,nonatomic, retain) NSDate *upsertDate;
@end

/**
 *  @class WDAcceptProductCatalogueCategory
 *  @discussion  Product Catalogue Category object
 **/
@interface WDAcceptProductCatalogueCategory : NSObject <NSCoding>
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

@property (nullable, nonatomic, retain) NSString *categoryId;
@property (nullable, nonatomic, retain) NSString *parentCategoryId;
@property (nullable, nonatomic, retain) NSString *categoryName;
@property (nullable, nonatomic, retain) NSNumber *displayOrder;
@property (nullable, nonatomic, retain) NSNumber *version;
@property (nullable, nonatomic, retain) NSArray <WDAcceptProductCatalogueCategory *> *subcategories;
@end

/**
 *  @class WDAcceptBarCodeType
 *  @discussion  Bar Code type
 **/
@interface WDAcceptBarCodeType : NSObject <NSCoding>
@property (nonatomic, retain) NSString *barCodeTypeId;
@property (nonatomic, retain) NSString *barCodeTypeName;
@end

/**
 *  @class WDAcceptProductCatalogueProduct
 *  @discussion Product details
 **/
@interface WDAcceptProductCatalogueProduct: NSObject <NSCoding>
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

@property (nullable, nonatomic, retain) WDAcceptBarCodeType *barCodeType;
@property (nullable, nonatomic, retain) NSString *barCodeValue;
@property (nullable, nonatomic, retain) NSString *externalId;
@property (nullable, nonatomic, retain) NSString *imageId;
@property (nullable, nonatomic, retain) NSString *productId;
@property (nullable, nonatomic, retain) NSString *productName;
@property (nullable, nonatomic, retain) NSArray <WDAcceptProductCatalogueCategory*> *productCategories;
@property (nonatomic, retain) NSArray <WDAcceptUnitPrice*> *productUnitPrices;
@property (nonatomic, retain) WDAcceptTaxCategory *taxCategory;
@property (nonatomic, retain) NSNumber *version;
@end

/**
 *  @class WDAcceptProductAvailability
 *  @discussion Product availability
 **/
@interface WDAcceptProductAvailability: NSObject <NSCoding>
@property (nonatomic, retain) NSString *externalProductId;
@property (nonatomic, retain) NSNumber *stockQuantity;
@end

/**
 *  @class WDAcceptProductStock
 *  @discussion Product stocks
 **/
@interface WDAcceptProductStock: NSObject <NSCoding>
@property (nonatomic, retain) NSArray <WDAcceptProductAvailability*>* productsAvailability;
@property (nonatomic, retain) NSString *siteId;
@property (nonatomic, retain) WDAcceptAddress *address;
@end

/**
 *  @class WDAcceptProductCatalogueDiscount
 *  @discussion Product Catalogue discount - flat discount
 **/
@interface WDAcceptProductCatalogueDiscount: NSObject <NSCoding>
@property (nullable,nonatomic, retain) NSNumber *flatDiscount;
@end

/**
 *  @class WDAcceptProductPrice
 *  @discussion ERP product price information
 **/
@interface WDAcceptProductPrice : WDAcceptObject<NSCoding>
/**
 */
@property (nullable, nonatomic, retain) NSString *currencyCode;
/**
 */
@property (nullable, nonatomic, retain) NSString *externalProductId;
/**
 */
@property (nullable, nonatomic, retain) NSDecimalNumber *unitPrice;

@end

NS_ASSUME_NONNULL_END
