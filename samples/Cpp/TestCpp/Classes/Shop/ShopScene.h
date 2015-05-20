//
//  ShopScene.h
//  BraveFrontier

//  Created by WillArk on 11/2/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_ShopScene_h
#define BraveFrontier_ShopScene_h

#include "cocos2d.h"

#include "PurchaseMst.h"
#include "BaseScene.h"
USING_NS_CC;

class ShopScene : public BaseScene
{
public:
    static CCScene * scene();
    CREATE_FUNC(ShopScene);
    virtual bool init();
    
    virtual void onEnter();
    // コンストラクタ
    ShopScene();
    // デストラクタ
    ~ShopScene();
    
    enum PURCHASE_STATUS
    {
        PURCHASE_WAIT = 0,
        START_PURCHASE = 1,
        START_PURCHASE_WAITING,
        START_STORE_KIT,
        START_STORE_KIT_WAITING,
        START_END,
        START_END_WAITING,
        START_AFTER_PROC,
        START_AFTER_PROC_WAITING,
        START_RESTART,
        START_RESTART_WAITING,
    };
protected:
    void draw();
    virtual void onBackClick();
private:
    bool _PaymentIDCheckedALL; //是否 检测完所有的
    long long _startTime; //起始的时间
    
    void onBuyClick(CCObject * sender, CCControlEvent controlEvent);
    
    // 選択情報
    PurchaseMst* selectPurchaseMst;
    

    CC_SYNTHESIZE(PURCHASE_STATUS, m_purchaseStatus, PurchaseStatus);
    
    
};

#endif

