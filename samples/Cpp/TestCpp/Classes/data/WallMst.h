//
//  WallMst.h
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_WallMst_h
#define BraveFrontier_WallMst_h

#include "cocos2d.h"

USING_NS_CC;

class WallMst : public CCObject
{
public:
    // コンストラクタ
    WallMst();
    // デストラクタ
    ~WallMst();
    void initWithArray(CCDictionary * list);
private:
    CC_SYNTHESIZE(int, m_lv, Lv);
    CC_SYNTHESIZE(int, m_hp, Hp);
    CC_SYNTHESIZE(int, m_cost, Cost);
};

#endif
