//
//  PaymentUtil.h
//  BraveFrontier
//
//  Created by 本山 順一 on 12/11/02.
//
//
#ifndef BraveFrontier_PaymentUtil_h
#define BraveFrontier_PaymentUtil_h

// iOS系課金関数

#import <CoreFoundation/CoreFoundation.h>
#import <UIKit/UIKit.h>
#import <StoreKit/StoreKit.h>

#import "F8base64.h"

@interface PaymentUtil : NSObject <SKProductsRequestDelegate, SKPaymentTransactionObserver,UIAlertViewDelegate, UIActionSheetDelegate>
{
}

// 未処理トランザクション有無
- (bool)isUntreatedTransaction;
/*add by wcx 
iap计费回调没有返回的 判断
 */
+ (bool)isUntreatedTransaction2;
/*
 add by wcx 
 检测 货物列表的 ID的 效性
 return 
 false 含有，没有经过检测的 ID
 true  传入的ID已经经过的 检测
 */
+ (bool)checkoutPaymentID:(NSString*)aPaymentId;

// オブザーバー登録
- (void)addObjsever;
// 課金リクエスト開始
- (void)paymentRequest:(NSString*)productID;

@end

#endif
