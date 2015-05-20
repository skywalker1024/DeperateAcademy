//
//  PurchaseMst.h
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_PurchaseMst_h
#define BraveFrontier_PurchaseMst_h

#include "cocos2d.h"

USING_NS_CC;

class PurchaseMst : public CCObject
{
public:
    // コンストラクタ
    PurchaseMst();
    // デストラクタ
    ~PurchaseMst();
    void initWithArray(CCDictionary * list);
private:
    CC_SYNTHESIZE(int, m_id, Id);
    CC_SYNTHESIZE(string, m_name, Name);
    CC_SYNTHESIZE(string, m_productId, ProductId);
    CC_SYNTHESIZE(int, m_amount, Amount);
    CC_SYNTHESIZE(int, m_diamond, Diamond);
    CC_SYNTHESIZE(string, m_description, Description);
};

#endif
