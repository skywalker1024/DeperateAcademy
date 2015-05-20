//
//  PaymentUtil.mm
//  BraveFrontier
//
//  Created by 本山 順一 on 12/11/02.
//
//

#import "PaymentUtil.h"
#import "Reachability.h"

#import "GameConst.h"
//#import "SaveData.h"
#import "UserState.h"
#import "UserInfo.h"

#include "PurchaseMst.h"
#include "PurchaseMstList.h"

#import <TargetConditionals.h>
#import "CommonUtils.h"

@implementation PaymentUtil
static  NSString *iWantBuyKey = @"Buy";
static  NSMutableDictionary *iDic =  NULL;

/*
 * 未処理トランザクション有無
 */
- (bool)isUntreatedTransaction
{
    return [SKPaymentQueue defaultQueue].transactions.count > 0 ? YES : NO;
}


+(bool)isUntreatedTransaction2
{
    NSArray* transactions = [SKPaymentQueue defaultQueue].transactions;
    if (transactions.count > 0)
    {
        //检测是否有未完成的交易
        SKPaymentTransaction* transaction = [transactions firstObject];
        if (transaction.transactionState == SKPaymentTransactionStatePurchased)
        {
            [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
            return YES;
        }
    }
    return NO;
}


+ (bool)checkoutPaymentID:(NSString*)aPaymentID //订单优化
{
    bool iRes = NO;
    //数据安全性检测
    if (!iDic)
    {
        return iRes;
    }
    
    NSString *iPaymentID = aPaymentID;
    [iPaymentID retain];
    
    SKProduct *product = [iDic objectForKey:iPaymentID];
    if (product && [product isKindOfClass:[SKProduct class]] && [product.productIdentifier isEqualToString:aPaymentID] )
    {
        iRes = YES;
    }

    [iPaymentID release];
    return iRes;
    
}


/*
 * オブザーバー登録 
 6. 注册一个transaction observer到payment队列
 应用实例化一个transaction observer，并将其注册到payment队列。
 */
- (void) addObjsever
{
    // SKPaymentQueueのオブザーバーとして登録
    [[SKPaymentQueue defaultQueue]addTransactionObserver:self];
}

/*
 * 課金リクエスト開始----购买开始
 */
- (void) paymentRequest:(NSString *)productID
{
    NSLog(@"计费paymentRequest start [%@]", productID);
    
    // 課金通信フラグをONに
    UserState::shared()->setPurchaseConnectFlg( true );
    
    // ネットワーク判定(通信ができる状態かどうか)
    Reachability* curReach = [Reachability reachabilityForInternetConnection];
    NSParameterAssert([curReach isKindOfClass:[Reachability class]]);
    
    if ([curReach currentReachabilityStatus] == NotReachable) {
        // 通信不能
        
        // エラーの為、戻す
        UserState::shared()->setPurchaseConnectFlg( false );
        
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@""
                                                        message:@"无法连接到网络"//ネットワークに接続出来ません
                                                       delegate:self
                                              cancelButtonTitle:@"YES"
                                              otherButtonTitles:nil];
        alert.tag = 1;
        [alert show];
        [alert release];
        return;
    }
    
    // アプリ内課金が許可されているかを確認   -----   检查应用程序内结算被授权（确定系统能够处理支付）
    if ([SKPaymentQueue canMakePayments] == NO) {
        // 設定にて許可されていない
        
        // エラーの為、戻す
        UserState::shared()->setPurchaseConnectFlg( false );
        
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil
                                                        message:@"应用程序内购买被禁用"//アプリ内課金が許可されていません
                                                       delegate:self
                                              cancelButtonTitle:@"OK"
                                              otherButtonTitles:nil];
        [alert show];
        [alert release];
        return;
    }
    
    // 端末状態を保存
    UserInfo::shared()->setPurchaseModelStatus( PURCHASE_MODEL_STATUS_PRODUCT_CHECK_BEFORE );
    //SaveData::shared()->saveKeyChain();
    
    // 通信中を表すアイコンを表示
    [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // プロダクト情報の取得開始----4. 获取products的信息
    NSSet *productids = NULL;//[NSSet setWithObject:productID];  modify by wcx
    SKProductsRequest* skProductRequest = NULL;
    
    if ([productID isEqualToString:@"check"])
    {
        int iCount = PurchaseMstList::shared()->getCount();
        if (!iDic)
        {
            iDic = [[NSMutableDictionary alloc]initWithCapacity:iCount];
        }
        
        NSMutableArray *iArr = [[NSMutableArray alloc] init];

        for(int i =0; i < iCount ; ++i )
        {
            PurchaseMst* iMst = PurchaseMstList::shared()->getObject(i);
            if (!iMst) { continue; }
            
            NSString *iProductIDStr = [NSString stringWithFormat:@"%s" ,iMst->getProductId().c_str()];
            [iDic setObject:[[SKProduct alloc] init] forKey:iProductIDStr];
            [iArr addObject:iProductIDStr];
        }
        productids = [NSSet setWithArray:iArr];
        
        skProductRequest = [[SKProductsRequest alloc] initWithProductIdentifiers:productids];
        skProductRequest.delegate = self;
        [skProductRequest start];
    }

    [iDic setObject:productID forKey:iWantBuyKey]; //把想要买的 值放到字典中去
    
    if (![productID isEqualToString:@"check"]) // 这个"check" 字符串不能随便改
    {
        SKProduct *product = [iDic objectForKey:productID];
        if (product && [product isKindOfClass:[SKProduct class]] && [product.productIdentifier isEqualToString:productID] )
        {
            SKPayment *payment = [SKPayment paymentWithProduct:product];
            [[SKPaymentQueue defaultQueue] addPayment:payment];
            
            // 端末状態を保存
            UserInfo::shared()->setPurchaseModelStatus( PURCHASE_MODEL_STATUS_PRODUCT_STORE_KIT_PUSH_AFTER );
            //SaveData::shared()->saveKeyChain();
        }
        else
        {
            if (!skProductRequest)
            {
                NSSet *productids = [NSSet setWithObject:productID];
                skProductRequest = [[SKProductsRequest alloc] initWithProductIdentifiers:productids];
                skProductRequest.delegate = self;
                [skProductRequest start];
            }
        }
    }
}

/*
 * プロダクト情報確認通信のレスポンス処理----产品信息确认通信响应处理
 */
- (void) productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
    if (response == nil)
    {
        // レスポンスなし
        NSLog(@"计费Product Response is nil");
    }
    else
    {
        // レスポンスあり
        NSLog(@"计费Product Response OK");
        NSLog(@"计费Product Response invalidProductIdentifiers count: %d", [response.invalidProductIdentifiers count]);
        
        // 端末状態を保存
        UserInfo::shared()->setPurchaseModelStatus( PURCHASE_MODEL_STATUS_PRODUCT_CHECK_AFTER );
        //SaveData::shared()->saveKeyChain();
        
        for (NSString *identifier in response.invalidProductIdentifiers) {
            NSLog(@"计费invalid product identifier: [%@]", identifier);
        }
        NSLog(@"Products count in received response: %d", [response.products count]);
        
        
        NSString *iWantBuyId =  [iDic objectForKey:iWantBuyKey];
        
        for (SKProduct *product in response.products)
        {
            [iDic setObject:product forKey:product.productIdentifier];

            if (iWantBuyId && [iWantBuyId isEqualToString:product.productIdentifier] )
            {
                // productを元にした購入オブジェクトをキューに入れて購入手続きに入ります（进入购买放在一个队列即买即根据产品对象）
                NSLog(@"计费valid product identifier: %@", product.productIdentifier);
                SKPayment *payment = [SKPayment paymentWithProduct:product]; /*你就可以显示用户界面。当用户在Store中选择一项时，应用就创建一个payment对象，并将其添加到payment队列中。*/
                [[SKPaymentQueue defaultQueue] addPayment:payment];
                
                // 端末状態を保存
                UserInfo::shared()->setPurchaseModelStatus( PURCHASE_MODEL_STATUS_PRODUCT_STORE_KIT_PUSH_AFTER );
                //SaveData::shared()->saveKeyChain();
            }
        }
    }
}

/**
 * 購入手続きのトランザクション処理----购买交易处理
 */
- (void) paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    BOOL purchasing = YES;
    NSLog(@"paymentQueue start");
    
    //CommonUtils::setIsCall3PayStatus(false); //add by wcx
    
    for (SKPaymentTransaction *transaction in transactions) {
        switch (transaction.transactionState) {
                // 購入中
            case SKPaymentTransactionStatePurchasing: {
                NSLog(@"Payment Transaction Purchasing");

                break;
            }
                // 購入成功
            case SKPaymentTransactionStatePurchased: {
                NSLog(@"Payment Transaction END Purchased: %@", transaction.transactionIdentifier);

                purchasing = NO;
                
                // フラグ制御
                {
                    // 購入成功
                    UserInfo::shared()->setPurchaseRstFlg( VALID );
                    // レシート設定
                    UserInfo::shared()->setPurchaseReceipt( [ [ transaction.transactionReceipt base64String ] cStringUsingEncoding: [NSString defaultCStringEncoding] ] );
                    // 課金処理未完了へ
                    UserInfo::shared()->setPurchaseFixFlg( INVALID );
                    // 端末状態を保存
                    UserInfo::shared()->setPurchaseModelStatus( PURCHASE_MODEL_STATUS_PRODUCT_STORE_KIT_RECIEVE );
                    
                    // 課金通信終了
                    UserState::shared()->setPurchaseConnectFlg( false );
                    
                    // キーチェーン保存
                    //SaveData::shared()->saveKeyChain();
                }
                
                // キューから削除
                {
                    [queue finishTransaction:transaction];/*处理还原购买，结束交易*/
                }
                // smac
                
                break;
            }
                // 購入失敗
            case SKPaymentTransactionStateFailed: {
                NSLog(@"Payment Transaction END Failed: %@ %@", transaction.transactionIdentifier, transaction.error);

                purchasing = NO;
                
                // 購入失敗におけるアラート
                
                // フラグ制御
                {
                    // 購入失敗
                    UserInfo::shared()->setPurchaseRstFlg( INVALID );
                    // レシート設定（空）
                    UserInfo::shared()->setPurchaseReceipt( "" );
                    // 課金処理未完了へ
                    UserInfo::shared()->setPurchaseFixFlg( INVALID );
                    // 端末状態を保存
                    UserInfo::shared()->setPurchaseModelStatus( PURCHASE_MODEL_STATUS_PRODUCT_STORE_KIT_RECIEVE );
                    
                    // 課金通信終了
                    UserState::shared()->setPurchaseConnectFlg( false );
                    
                    // キーチェーン保存
                    //SaveData::shared()->saveKeyChain();
                }
                
                // キューから削除
                {
                    [queue finishTransaction:transaction];
                }

                break;
            }
                // 購入履歴復元---购买历史复原
            case SKPaymentTransactionStateRestored: {
                NSLog(@"Payment Transaction END Restored: %@", transaction.transactionIdentifier);
                // 売り切りのプロダクトしかないため
                // 本来ここに到達しない
                purchasing = NO;
                
                // フラグ制御
                {
                    // 購入失敗
                    UserInfo::shared()->setPurchaseRstFlg( INVALID );
                    // レシート設定（空）
                    UserInfo::shared()->setPurchaseReceipt( "" );
                    // 課金処理未完了へ
                    UserInfo::shared()->setPurchaseFixFlg( VALID );
                    // 端末状態を保存
                    UserInfo::shared()->setPurchaseModelStatus( PURCHASE_MODEL_STATUS_PRODUCT_STORE_KIT_RECIEVE );
                    
                    // 課金通信終了
                    UserState::shared()->setPurchaseConnectFlg( false );
                    
                    // キーチェーン保存
                    //SaveData::shared()->saveKeyChain();
                }
                
                // キューから削除
                {
                     [queue finishTransaction:transaction];
                }
                
                break;
            }
                // Ask To Buy: 承認待ち移行
            case SKPaymentTransactionStateDeferred: {
                
                purchasing = NO;
                
                // 購入失敗におけるアラート
            
                // フラグ制御
                {
                    // 購入承認待ち
                    UserInfo::shared()->setPurchaseRstFlg( PURCHASE_STATE_DEFERRED );
                    // レシート設定（空）
                    UserInfo::shared()->setPurchaseReceipt( "" );
                    // 課金処理未完了へ
                    UserInfo::shared()->setPurchaseFixFlg( INVALID );
                    // 端末状態を保存
                    UserInfo::shared()->setPurchaseModelStatus( PURCHASE_MODEL_STATUS_PRODUCT_STORE_KIT_RECIEVE );
                    
                    // 課金通信終了
                    UserState::shared()->setPurchaseConnectFlg( false );
                    
                    // キーチェーン保存
                    //SaveData::shared()->saveKeyChain();
                }
                
                // キューから削除
                {
                    [queue finishTransaction:transaction];
                }
                
                break;
            }
        }
    }
    
    if (purchasing == NO) {
        [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
    }
}

@end
