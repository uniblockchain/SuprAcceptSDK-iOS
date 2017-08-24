//
//  WDAcceptSaleManager.h
//  acceptSDK
//
//  Created by Timko, Marek on 02/03/2017.
//  Copyright © 2017 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WDADataTypes.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  @class WDAcceptSaleManager
 *  @brief Sale Management
 */
@interface WDAcceptSaleManager : NSObject

/**
 *  @brief Start the payment process
 *  @param saleConfiguration Configuration to be used to perform this payment
 *  @param progress Block bearing the information about the payment process progress
 *  @param collectSignature Block that needs to execute the option to capture a signature and return the signature data
 *  @param verifySignature Block that informs that a signature needs to be verified. This is done after the transaction has been already send to background, but the final approval depends on the merchant. Only
 * terminals with signature verification built it (i.e. Spire Posmate) requires actions here. And signatureVerification block can be handled in the same way as the completion block, as indicates a completion itself
 * (just lacking the second generate AC)
 *  @param cardApplication Block informs that an application selection is needed with the chip card inserted.
 *  @param completion Block that will be called at the very end of payment flow. It provides an AcceptTransaction object (that may be nil if unauthorised) or a descriptive error
 **/
- (void)pay:(WDAcceptPaymentConfig* )saleConfiguration
   progress:(PaymentProgress )progress
collectSignature:(SignatureRequiredRequest )collectSignature
verifySignature:(SignatureVerificationRequest )verifySignature
cardApplication:(PaymentCardApplicationSelectionRequest )cardApplication
 completion:(SaleCompletion )completion;

/**
 *  @brief Cancel the payment flow. This is usually called from UI (cancel button when available) or some error from signature or completion block. Notice that an improper usage of this function (for example during online communication or level 2 flow in terminal) can produce unexpected errors
 **/
- (void) cancelPay;

#pragma mark - Transaction history and statistics

/**
 *  @brief Retrieve the sales statistics based on the search criteria
 *  @param query Statistics query parameters
 *  @param completion Block executed at the end of the login method - provides Array of one element EMAIL or SMS to confirm which method for sending the Receipt was used
 */
-(void)salesStatistics:(WDAcceptStatisticsQuery*)query
            completion:(SaleStatisticsCompletion _Nonnull)completion;

/**
 *  @brief Retrieve the sales for the merchant user based on the search criteria
 *  @param searchCriteria Definition of search criteria in AcceptTransactionsQuery instance
 *  @param completion SaleQueryResponse block executed at the end of the method - provides Array of WDAcceptSales
 */
-(void)querySales:(WDAcceptSalesQuery*)searchCriteria
       completion:(SaleQueryResponse)completion;

#pragma mark - Transaction management

/**
 *  @brief Reverse the sale
 *  @param internalId unique sale id - internal
 *  @param cashRegisterId cash register id - if exist and is needed for the merchant
 *  @param message detailed information to be set for this action
 *  @param completion Block executed at the end of the  method
 */
-(void)reverseSale:(NSString * _Nonnull)internalId cashRegisterId:(NSString * _Nullable)cashRegisterId message:(NSString *_Nullable)message completion:(SaleUpdateCompletion _Nonnull)completion;

/**
 *  @brief Refund the sale
 *  @param sale original sale to refund
 *  @param message detailed information to be set for this action
 *  @param completion Block executed at the end of the  method
 */
-(void)refundSale:(WDAcceptSaleRequest * )sale
          message:(NSString *)message
       completion:(SaleUpdateCompletion )completion;

/**
 *  @brief Send Receipt to Email  or Phone
 *  @param saleId Sale id for which the Receipt should be sent
 *  @param saleState state (AcceptSaleStateCompleted, AcceptSaleStateReturned, AcceptSaleStateCancelled, ...)
 *  @param emailOrPhone Email address or Phone number to which to send the Receipt
 *  @param completion Block executed at the end of the login method - provides Array of one element EMAIL or SMS to confirm which method for sending the Receipt was used
 */
-(void)sendReceiptForSale:(NSString *)saleId
            saleState:(AcceptSaleState)saleState
                  byEmailOrPhone:(NSString *)emailOrPhone
                      completion:(SendReceiptCompletion)completion;

@end

NS_ASSUME_NONNULL_END
