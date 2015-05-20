//
//  PaymentUtil.h
//  BraveFrontier
//
//  Created by 本山 順一 on 12/11/02.
//
//
#ifndef BraveFrontier_PaymentUtil_h
#define BraveFrontier_PaymentUtil_h

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

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

#else

// iOS以外の課金関数

class PaymentUtil {
public:
	//課金シーンに入る時の初期化
	static void storeOpening();
	//課金シーンから出る時の終了処理
	static void storeClosing();

	//アイテム値段、現在の有効transactionsの同期（ゲームに入る時に呼ぶべき）
	static void syncItemPricesAndPurchases();
	//課金開始
	static void paymentRequest(std::string productId);

	//課金が行われた時のコールバック
	static void onPurchaseStateChanged(std::string signedData, std::string signature);

	//課金サーバサイド処理後消耗品消費リクエスト
	static void consumePurchase(std::string signedData, std::string signature);
};

#endif

#endif
