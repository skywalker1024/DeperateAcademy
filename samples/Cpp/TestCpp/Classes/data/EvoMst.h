//
//  EvoMst.h
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_EvoMst_h
#define BraveFrontier_EvoMst_h

#include "cocos2d.h"

USING_NS_CC;

class EvoMst : public CCObject
{
public:
    // コンストラクタ
    EvoMst();
    // デストラクタ
    ~EvoMst();
    void initWithArray(CCDictionary * list);
private:
    CC_SYNTHESIZE(int, m_id, Id);
    CC_SYNTHESIZE(int, m_beforeId, BeforeId);
    CC_SYNTHESIZE(int, m_afterId, AfterId);
    CC_SYNTHESIZE(int, m_cost, Cost);
};

#endif
