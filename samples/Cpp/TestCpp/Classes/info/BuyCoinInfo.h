//
//  BuyCoinInfo.h
//  BraveFrontier

//  Created by WillArk on 5/10/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_BuyCoinInfo_h
#define BraveFrontier_BuyCoinInfo_h

#include "cocos2d.h"

USING_NS_CC;

class BuyCoinInfo : public CCObject
{
public:
    // インスタンスの取得
    static BuyCoinInfo* shared();
    static void destroy();
private:
    // コンストラクタ
    BuyCoinInfo();
    // デストラクタ
    ~BuyCoinInfo();
   
    CC_SYNTHESIZE(int, m_purchaseState, PurchaseState);
};

#endif
