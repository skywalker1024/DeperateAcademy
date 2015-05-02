//
//  SoldierMst.h
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_SoldierMst_h
#define BraveFrontier_SoldierMst_h

#include "cocos2d.h"

USING_NS_CC;

class SoldierMst : public CCObject
{
public:
    // コンストラクタ
    SoldierMst();
    // デストラクタ
    ~SoldierMst();
    void initWithArray(CCDictionary * list);
private:
    CC_SYNTHESIZE(int, m_id, Id);
    CC_SYNTHESIZE(string, m_name, Name);
    CC_SYNTHESIZE(int, m_series, Series);
    CC_SYNTHESIZE(int, m_hp, Hp);
    CC_SYNTHESIZE(int, m_atk, Atk);
    CC_SYNTHESIZE(int, m_moveSpeed, MoveSpeed);
    CC_SYNTHESIZE(int, m_atkRange, AtkRange);
};

#endif
