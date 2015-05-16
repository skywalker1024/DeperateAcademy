//
//  ArenaInfo.h
//  BraveFrontier

//  Created by WillArk on 5/10/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_ArenaInfo_h
#define BraveFrontier_ArenaInfo_h

#include "cocos2d.h"

USING_NS_CC;
#include "json.h"
class ArenaInfo : public CCObject
{
public:
    // インスタンスの取得
    static ArenaInfo* shared();
    static void destroy();
    void updateWithJson(Json::Value json);
    // コンストラクタ
    ArenaInfo();
    // デストラクタ
    ~ArenaInfo();
private:
    CC_SYNTHESIZE(int, m_userId, UserId);
    CC_SYNTHESIZE(int, m_minNum, MinNum);
    CC_SYNTHESIZE(int, m_maxNum, MaxNum);
    CC_SYNTHESIZE(int, m_minTimer, MinTimer);
    CC_SYNTHESIZE(int, m_maxTimer, MaxTimer);
    CC_SYNTHESIZE(int, m_rank, Rank);
    CC_SYNTHESIZE(int, m_wallLv, WallLv);
    CC_SYNTHESIZE(string, m_name, Name);
    CC_SYNTHESIZE(string, m_soldier, Soldier);
};

#endif
