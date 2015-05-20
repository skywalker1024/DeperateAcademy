//
//  ShopScene.cpp
//  BraveFrontier

//  Created by WillArk on 11/2/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "ShopScene.h"
#include "PurchaseMst.h"
#include "PurchaseMstList.h"
#include "CommonUtils.h"
#include "HomeScene.h"
#include "UserInfo.h"
#include "UserState.h"
#include "BuyCoinInfo.h"
#include "DialogLayer.h"
#import "PaymentUtil.h"


//peiyang vip
static bool vipStatus = false;
//end

/*
 * コンストラクタ。
 */
ShopScene::ShopScene()
{
    _PaymentIDCheckedALL = true; //add by wcx
    _startTime = CommonUtils::getCurrentTime();
    
    selectPurchaseMst = NULL;
    m_purchaseStatus = PURCHASE_WAIT;
    
}

/*
 * デストラクタ。
 */
ShopScene::~ShopScene()
{

}


/*
 * 初期化処理。
 */
void ShopScene::onEnter()
{
    BaseScene::onEnter();
    { /*add by wcx*/
        int icout = PurchaseMstList::shared()->getCount();
        for (int i=0; i < icout; ++i)
        {
            PurchaseMst* iMst = PurchaseMstList::shared()->getObject(i);
            if (!iMst) { continue; }
            
            _PaymentIDCheckedALL =  CommonUtils::checkoutPaymentID(iMst->getProductId()); // false 为没有经过检测，需要重新检测
            
            if (!_PaymentIDCheckedALL)
            {
                CommonUtils::startCheckID();
                break;
            }
        }
    }
    
    // ヘッダー更新
    setHeader();
    setBackBtn();
    int screenWidth = CommonUtils::getScreenWidth();
    int screenHeight = CommonUtils::getScreenHeight();
    //渲染coinList
    for (int i=0; i<PurchaseMstList::shared()->getCount(); i++) {
        PurchaseMst * purchaseMst = PurchaseMstList::shared()->getObject(i);
        
        CCString * diamondStr = CCString::createWithFormat("钻石%d个", purchaseMst->getDiamond());
        GraphicUtils::drawString(this, diamondStr->m_sString, 50, 100 + 100 * i, getSystemColor(COLOR_KEY_ATK), TEXT_ALIGN_LEFT_MIDDLE, 40);
        
        CCString * amountStr = CCString::createWithFormat("RMB %d", purchaseMst->getAmount());

        GraphicUtils::drawString(this, amountStr->m_sString, 250, 100 + 100 * i, getSystemColor(COLOR_KEY_ATK), TEXT_ALIGN_LEFT_MIDDLE, 40);
        
        CCLabelTTF * questLabel = CCLabelTTF::create("购买", DEFAULT_FONT_NAME, 60);
        CCControlButton * button = CCControlButton::create(questLabel, CCScale9Sprite::create("img/button.png") );
        button->setBackgroundSpriteForState(CCScale9Sprite::create("img/buttonHighlighted.png"), CCControlStateHighlighted);
        button->setPosition(ccp(350, 100 + 100 * i));
        button->setTag(purchaseMst->getId());
        button->addTargetWithActionForControlEvents(this, cccontrol_selector(ShopScene::onBuyClick), CCControlEventTouchUpInside);
        this->addChild(button);
    }
}

void ShopScene::onBackClick(){
    changeScene(HomeScene::scene());
}

void ShopScene::onBuyClick(CCObject * sender, CCControlEvent controlEvent){
    int purchaseId = dynamic_cast<CCControlButton*>(sender)->getTag();
    m_purchaseStatus = START_PURCHASE;
    
    // 課金マスタ
    selectPurchaseMst = PurchaseMstList::shared()->getObjectById( purchaseId );
    // 設定
    UserInfo::shared()->setPurchaseId( purchaseId );
    
    UserInfo::shared()->setPurchasePayAmount( selectPurchaseMst->getAmount() );
}

/*
 * 定期更新処理。
 */
void ShopScene::draw()
{
    BaseScene::draw();
    
    
    // 課金処理開始
    if( m_purchaseStatus == START_PURCHASE )
    {
        CCLog("ShopScene - startPurchase");
        
        string postData = CCString::createWithFormat("purchase_id=%d", selectPurchaseMst->getId())->m_sString;
        pushStepScene("buy_coin_start.php", postData, NULL);
        
        // フラグを落とす
        m_purchaseStatus = START_PURCHASE_WAITING;
        
        return;
    }
    
    // StoreKit処理開始
    if( m_purchaseStatus == START_STORE_KIT )
    {
        CCLog("ShopScene - startStoreKit");
        CommonUtils::paymentRequest(selectPurchaseMst->getProductId());
        
        // フラグを落とす
        m_purchaseStatus = START_STORE_KIT_WAITING;
        
        return;
    }
    
    if(m_purchaseStatus == START_STORE_KIT_WAITING && !UserState::shared()->getPurchaseConnectFlg()){
        m_purchaseStatus = START_END;
    }
    // 終了処理開始
    if( m_purchaseStatus == START_END )
    {
        //发送
    	CCLog("ShopScene - startEnd");
        
        //postData
    
        int purchase_state = 0;
        if( UserInfo::shared()->getPurchaseRstFlg() == VALID )
        {
            // 成功
            purchase_state = PURCHASE_STATE_COMPLETE;
            CCLog("PURCHASE_STATE_COMPLETE");
        }
        else if( UserInfo::shared()->getPurchaseRstFlg() == INVALID )
        {
            // 失敗（キャンセル）
            purchase_state = PURCHASE_STATE_CANCEL;
            CCLog("PURCHASE_STATE_CANCEL");
        }
        else if( UserInfo::shared()->getPurchaseRstFlg() == PURCHASE_STATE_GIVEUP )
        {
            // ギブアップ
            purchase_state = PURCHASE_STATE_GIVEUP;
            CCLog("PURCHASE_STATE_GIVEUP");
        }
        else if( UserInfo::shared()->getPurchaseRstFlg() == PURCHASE_STATE_DEFERRED )
        {
            // Ask to Buy
            purchase_state = PURCHASE_STATE_DEFERRED;
            CCLog("PURCHASE_STATE_DEFERRED");
        }
        CCString * postString = CCString::createWithFormat("purchase_id=%d&purchase_receipt=%s&purchase_state=%d",selectPurchaseMst->getId(), UserInfo::shared()->getPurchaseReceipt().c_str(), purchase_state);
        pushStepScene("buy_coin.php", postString->m_sString, NULL, "正在完成购买，请稍等");
        
        // フラグを落とす
        m_purchaseStatus = START_END_WAITING;
        
        return;
    }
    
    // 購入処理後
    if( m_purchaseStatus == START_AFTER_PROC )
    {
        CCLog("ShopScene - startAfterProc");
        
        
        int purchaseState = BuyCoinInfo::shared()->getPurchaseState();
        
        if( purchaseState == PURCHASE_STATE_COMPLETE )
        {
            DialogLayer::showDialog("已经完成购买手续。", 1);
        }
        else if( purchaseState == PURCHASE_STATE_CANCEL )
        {
            // キャンセル
            DialogLayer::showDialog("您的购买被取消了。", 1);
        }
        else if( purchaseState == PURCHASE_STATE_RECEIPT_NG )
        {
            // レシートNG
            DialogLayer::showDialog("无法执行购买。", 1);
        }
        else if( purchaseState == PURCHASE_STATE_GIVEUP )
        {
            // ギブアップ
            DialogLayer::showDialog("已中断购买钻石的程序。有问题请联系客服", 1);
        }
        else if( purchaseState == PURCHASE_STATE_DEFERRED )
        {
            // Ask to Buy
            DialogLayer::showDialog("购买请示会发送至监护人。", 1);
        }
        else
        {
            DialogLayer::showDialog("您的购买被取消了。", 1);
        }
        
        m_purchaseStatus = PURCHASE_WAIT;
        
        return;
    }
    
}

//end
