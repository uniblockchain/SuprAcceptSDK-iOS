//
//  UserTestsSwift.swift
//  DemoAcceptSDK
//
//  Created by Fortes, Francisco on 7/25/17.
//  Copyright © 2017 Wirecard. All rights reserved.
//

import Foundation
import XCTest
import Accept

class CatalogueTestsSwift: XCTestCase, AcceptSDKDelegate
{
    var returnedErr : Error!
    var expectation : XCTestExpectation!
    var sdk : AcceptSDK!
    var loggedUser : WDAcceptMerchantUser?
    var resultStatus : AcceptResultStatus?
    var successfulDownload : Bool?
    var serviceGroup : DispatchGroup!
    
    override func setUp()
    {
        super.setUp()
        self.continueAfterFailure = false
        sdk = AcceptSDK.sharedInstance()
        expectation = self.expectation(description: "Setup")
        self.serviceGroup = DispatchGroup()
        weak var welf = self
        
        sdk.setup(with: .development, username: KUSERNAME, password: KPASSWORD, completion:{( currentUser:WDAcceptMerchantUser? , cashier:WDAcceptMerchantCashier?, error:Error?) in
            
            welf?.sdk.add(self)
            welf?.sdk.setDevMode(true) //Setting dev mode as enabled will write logs in your app's document folder and fill the console log with debug messages - Do not forget to disable it before releasing your app to the public!!
            AcceptSDK.ddSetLogLevel(DDLogLevel.info.rawValue)
            welf?.expectation.fulfill()
        })
        
        self.waitForExpectations(timeout: 25, handler: nil)
    }
    
    override func tearDown()
    {
        super.tearDown()
    }
  
    func testCatalogue()
    {
        //PART 1: We log-in and request user data
        //--------------------------------------
        expectation = self.expectation(description: "Requesting User Data")
        self.loginAndGetUserData()
        self.waitForExpectations(timeout: 100, handler: nil)
        if (loggedUser == nil || (loggedUser?.isKind(of: WDAcceptMerchantUser.self)) == false)
        {
            XCTFail("Error, did not return Merchant User. Are your credentials correct? Try login into the backend through internet browser.")
        }

        //PART 2: We request catalogue data
        //--------------------------------------
        expectation = self.expectation(description: "Requesting Catalogue Data")
        self.requestCatalogueData()
        if self.successfulDownload == nil || self.successfulDownload == false
        {
            XCTFail("Error while downloading catalogue data. Chances are there was a timeout on backend or your connection got interrupted. In any case, you may retry.")
        }
    }
    
    func loginAndGetUserData()
    {
        loggedUser = nil
        weak var welf = self
        sdk.userManager.currentUser({(merchantUser : WDAcceptMerchantUser?, error: Error?) in
            NSLog("err:%@",[error])
            welf?.loggedUser = merchantUser
            welf?.returnedErr = error
            welf?.expectation.fulfill()
        })
    }
    
    func requestCatalogueData()
    {
        self.successfulDownload = true
        weak var welf = self
        
        let completionProductCatalogue : ProductCatalogueCompletion = {(arrCatalogues : [WDAcceptProductCatalogue]?, error : Error?) in
            welf?.returnedErr = error
            welf?.successfulDownload = error == nil
            if let arrCatalogues = arrCatalogues
            {
                if arrCatalogues.count == 0
                {
                    //No catalogues, so we finish the test. But for fully testing, please create a catalogue with categories and products in backend
                    welf?.expectation.fulfill()
                }
                else
                {
                    for catalogue in arrCatalogues
                    {
                        if welf?.successfulDownload == true
                        {
                            self.loadContentForCatalogue(catalogue: catalogue)
                        }
                    }
                }
            }
            welf?.serviceGroup.leave()
        }
        self.serviceGroup.enter()
        
        sdk.inventoryManager.productCatalogues((self.loggedUser?.merchant?.merchantId)!, completion: completionProductCatalogue)
        
        self.serviceGroup?.notify(queue: DispatchQueue.main, execute: {
                welf?.expectation.fulfill()
        })
    }
    
    func loadContentForCatalogue(catalogue : WDAcceptProductCatalogue)
    {
        weak var welf = self
        let completionCatalogue : ProductCatalogueCategoryCompletion = {(result : [WDAcceptProductCatalogueCategory]? , error : Error?) in
            
            let completionProductContent : ProductCatalogueProductCompletion = {(result : [WDAcceptProductCatalogueProduct]?, error : Error?) in
                if  error != nil || welf?.successfulDownload == false
                {
                    welf?.returnedErr = error
                    welf?.successfulDownload = false
                }
                else
                {
                    welf?.loadContentForProducts(products: result!, catalogueId: catalogue.productCatalogueId!, categoryId: "")
                }
                welf?.serviceGroup.leave()
            }

            let query : WDAcceptProductsQuery = WDAcceptProductsQuery.init(page: 0, pageSize: 20, catalogueId: catalogue.productCatalogueId!, productId: catalogue.productCatalogueId!)
            welf?.serviceGroup?.enter()
            welf?.sdk.inventoryManager.products(query, uncategorized: true, completion: completionProductContent)
            
            //Then we request categorized products
            for category : WDAcceptProductCatalogueCategory in result!
            {
                category.parentCategoryId = catalogue.productCatalogueId
                welf?.loadContentForCategory(category: category, catalogueId:catalogue.productCatalogueId!, dbVersion: Decimal(0))
                //Note: you may want to keep track of versions to compare to existing data in backend and do proper upsert in your app
            }
            
            self.serviceGroup.leave()
        }

        self.serviceGroup.enter()
        sdk.inventoryManager.productCategoriesTree(catalogue.productCatalogueId!, completion: completionCatalogue)
    }
    
    func loadContentForProducts(products : [WDAcceptProductCatalogueProduct], catalogueId : String, categoryId : String)
    {
        weak var welf = self
        if products.first != nil
        {
            self.serviceGroup.enter()
            var queries : [WDAcceptProductsQuery] = []
            for product : WDAcceptProductCatalogueProduct in products
            {
                if (product.imageId?.characters.count)! > 0
                {
                    let query : WDAcceptProductsQuery = WDAcceptProductsQuery.init(page: 0, pageSize: 20, catalogueId: catalogueId, productId: "")
                    query.productCategoryId = categoryId
                    queries.append(query)
                }
            }
            
            let completionImage : ProductCatalogueImageCompletion = {(prodsImage : [WDAcceptProductImage]?, error : Error?) in
                welf?.serviceGroup.leave()
            }
            
            if queries.count > 0 && self.successfulDownload == true
            {
                sdk.inventoryManager.productsImage(queries, completion: completionImage)
            }
            else
            {
                self.serviceGroup.leave()
            }
        }
        else if (products.count > 0)
        {
            self.successfulDownload = true
        }
    }
    
    func loadContentForCategory(category : WDAcceptProductCatalogueCategory?, catalogueId : String, dbVersion : Decimal)
    {
        weak var welf = self
        if let category = category
        {
            let completionGetProducts : ProductCatalogueProductCompletion = {(result : [WDAcceptProductCatalogueProduct]?, error : Error?) in
                if error != nil || welf?.successfulDownload == false
                {
                    welf?.returnedErr = error
                    welf?.successfulDownload = false
                }
                else
                {
                    self.loadContentForProducts(products: result!, catalogueId: catalogueId, categoryId: category.categoryId!)
                }
                welf?.serviceGroup.leave()
            }
            
            let query : WDAcceptProductsQuery = WDAcceptProductsQuery.init(page: 0, pageSize: 20, catalogueId: catalogueId, productId: category.categoryId!)
            for subcategory : WDAcceptProductCatalogueCategory in category.subcategories!
            {
                //Structure is 1 catalogue including 0 to many categories including zero to many products, and one product can belong to zero or many categories
                if category.categoryId != catalogueId && subcategory.parentCategoryId?.characters.count == 0
                {
                    subcategory.parentCategoryId = category.categoryId
                }
                self.loadContentForCategory(category: subcategory, catalogueId: catalogueId, dbVersion: dbVersion)
            }
            
            self.serviceGroup.enter()
            sdk.inventoryManager.products(query, uncategorized: false, completion: completionGetProducts)
        }
        else
        {
            self.successfulDownload = false
        }
    }
}
