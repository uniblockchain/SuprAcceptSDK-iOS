//
//  ViewController.m
//  eClear
//
//  Created by Danko, Radoslav on 15/12/2017.
//  Copyright © 2017 Wirecard. All rights reserved.
//

#import "ViewController.h"
#import "AppDelegate.h"
#import "eClear-Swift.h"
#import <AcceptUI/WDAcceptSaleManagerUI.h>

typedef NS_ENUM(NSUInteger, PaymentType) {
    PaymentTypeAmountCash = 1,
    PaymentTypeAmountCard,
    PaymentTypeNoAmountCardAndCash,
    PaymentTypeNoAmountQRCode,
    PaymentTypeNoAmountNoPaymentMethod
};

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UIButton *btnPayCashCard;
@property (strong, nonatomic) AppDelegate* app;
@property (strong, nonatomic) WDAcceptSaleResponse* sale;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.app = (AppDelegate*)[[UIApplication sharedApplication] delegate];
    self.btnPayCashCard.titleLabel.lineBreakMode = NSLineBreakByWordWrapping;
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    if (!self.app.sdk) {
        [self showLogin];
    }
}
-(void)viewWillDisappear:(BOOL)animated{
    [super viewWillDisappear:animated];
//    [self.navigationController setNavigationBarHidden:YES animated:YES];
}
#pragma mark - Custom Methods
-(void)showLogin{
   LoginVC *loginVC = (LoginVC*)[[UIStoryboard storyboardWithName:@"Main" bundle:nil] instantiateViewControllerWithIdentifier:@"LoginVC"];
    [self.navigationController presentViewController:loginVC animated:YES completion:nil];
}

-(void)pay:(NSDecimalNumber *)amount paymentMethod:(AcceptPaymentMethodMask)paymentMethod{
    
    WDAcceptSaleManagerUI *ui = [WDAcceptSaleManagerUI sharedInstance] ;
    
    WDAcceptSaleConfiguration *config = [[WDAcceptSaleConfiguration alloc]
                                         initWithAmount:amount
                                         currency: (paymentMethod == AcceptPaymentMethodMaskQR) ? @"USD" : @"EUR"
                                         taxRate:[NSDecimalNumber decimalNumberWithString:@"0.19"]
                                         paymentMethods:paymentMethod];
    
    //set the Localisation for the UI component [en, de, es] defaults to en if not set
    config.language = ((AppDelegate *)[UIApplication sharedApplication].delegate).language;
    
    [ui pay:config
   progress:^(AcceptStateUpdate paymentProgress) {
       NSLog(@"progress =%ld",(long)paymentProgress);
   } completion:^(WDAcceptSaleResponse * _Nullable saleResponse, NSError * _Nullable saleResponseError) {
       if (saleResponseError) {
           NSLog(@"saleResponseError:%@",saleResponseError);
           [self.app showError:@"Sale" text:saleResponseError.localizedDescription];
       }
       else{
           if ([saleResponse allPaymentsApproved]) {
               [self.app showSuccess:@"Sale" text:@"Payment processed successfully"];
           }
           else{
               [self.app showInfo:@"Sale" text:@"Payment failed" ] ;
           }
           [self showReceipt:saleResponse];
       }
       NSLog(@"saleResponse:%@",saleResponse);
   }];
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    ReceiptVC *receiptVC = (ReceiptVC*) segue.destinationViewController;
    receiptVC.sale = self.sale;
}

-(void)showReceipt:(WDAcceptSaleResponse *)sale{
    self.sale = sale;
//    ReceiptVC *receiptVC = (ReceiptVC*)[[UIStoryboard storyboardWithName:@"Main" bundle:nil] instantiateViewControllerWithIdentifier:@"ReceiptVC"];
//    receiptVC.sale = sale;
//    [self.navigationController showViewController:receiptVC sender:nil];
//    [self.navigationController setNavigationBarHidden:NO animated:YES];
    [self performSegueWithIdentifier:@"receiptSeque" sender:nil];
}

#pragma mark - Custom Actions
- (IBAction)onTapPay:(id)sender {
    UIButton *btn = (UIButton *) sender;
    switch (btn.tag) {
        case PaymentTypeAmountCash:
            [self pay:[NSDecimalNumber decimalNumberWithString:@"10"] paymentMethod:AcceptPaymentMethodMaskCashOnly];
            break;
        case PaymentTypeAmountCard:
            [self pay:[NSDecimalNumber decimalNumberWithString:@"10"] paymentMethod:AcceptPaymentMethodMaskCardOnly];
            break;
        case PaymentTypeNoAmountCardAndCash:
            [self pay:nil paymentMethod:AcceptPaymentMethodMaskStandard];
            break;
        case PaymentTypeNoAmountQRCode:
            [self pay:nil paymentMethod:AcceptPaymentMethodMaskQR];
            break;
        case PaymentTypeNoAmountNoPaymentMethod:
            [self pay:nil paymentMethod:AcceptPaymentMethodMaskAll];
            break;

        default:
            break;
    }
}
- (IBAction)onTapLogout:(id)sender {
    [self showLogin];
}
@end
