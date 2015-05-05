//
//  LevelMst.h
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_LevelMst_h
#define BraveFrontier_LevelMst_h

#include "cocos2d.h"

USING_NS_CC;

class LevelMst : public CCObject
{
public:
    // コンストラクタ
    LevelMst();
    // デストラクタ
    ~LevelMst();
    void initWithArray(CCDictionary * list);
private:
    CC_SYNTHESIZE(int, m_lv, Lv);
    CC_SYNTHESIZE(int, m_exp, Exp);
    CC_SYNTHESIZE(int, m_actionP, ActionP);
    CC_SYNTHESIZE(int, unlock_soldier_id, UnlockSoldierId);

};

#endif
