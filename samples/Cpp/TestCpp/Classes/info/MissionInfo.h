//
//  MissionInfo.h
//  BraveFrontier

//  Created by WillArk on 5/10/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_MissionInfo_h
#define BraveFrontier_MissionInfo_h

#include "cocos2d.h"

USING_NS_CC;

class MissionInfo : public CCObject
{
public:
    // インスタンスの取得
    static MissionInfo* shared();
    static void destroy();
private:
    // コンストラクタ
    MissionInfo();
    // デストラクタ
    ~MissionInfo();
    CC_SYNTHESIZE(int, m_currentMissionId, CurrentMissionId);
    CC_SYNTHESIZE(bool, m_isFirstClear, IsFirstClear);
};

#endif
