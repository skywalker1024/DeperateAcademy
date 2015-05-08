//
//  MissionMst.h
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_MissionMst_h
#define BraveFrontier_MissionMst_h

#include "cocos2d.h"

USING_NS_CC;

class MissionMst : public CCObject
{
public:
    // コンストラクタ
    MissionMst();
    // デストラクタ
    ~MissionMst();
    void initWithArray(CCDictionary * list);
private:
    CC_SYNTHESIZE(int, m_id, Id);
    CC_SYNTHESIZE(string, m_name, string);
    CC_SYNTHESIZE(int, m_actionP, ActionP);
    CC_SYNTHESIZE(int, m_exp, Exp);

};

#endif
