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
    
    std::map<int, int> getSoldierMap();
private:
    std::map<int, int>m_soldierMap;
    CC_SYNTHESIZE(int, m_id, Id);
    CC_SYNTHESIZE(string, m_name, string);
    CC_SYNTHESIZE(int, m_actionP, ActionP);
    CC_SYNTHESIZE(int, m_exp, Exp);
    CC_SYNTHESIZE(int, m_posX, PosX);
    CC_SYNTHESIZE(int, m_posY, PosY);
    CC_SYNTHESIZE(int, m_minNum, MinNum);
    CC_SYNTHESIZE(int, m_maxNum, MaxNum);
    CC_SYNTHESIZE(int, m_minTimer, MinTimer);
    CC_SYNTHESIZE(int, m_maxTimer, MaxTimer);
    CC_SYNTHESIZE(string, m_soldier_id, SoldierId);
    
    
};

#endif
