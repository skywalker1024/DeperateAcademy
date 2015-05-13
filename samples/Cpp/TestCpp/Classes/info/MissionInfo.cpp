//
//  MissionInfo.cpp
//  BraveFrontier

//  Created by WillArk on 5/10/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "MissionInfo.h"
#include "CommonUtils.h"
// シングルトンインスタンス
MissionInfo* MissionInfoInstance = NULL;

/**
 * シングルトンインスタンスを取得。
 */
MissionInfo* MissionInfo::shared()
{
    if( MissionInfoInstance == NULL )
    {
        MissionInfoInstance = new MissionInfo();
    }
    
    return MissionInfoInstance;
}


/*
 * コンストラクタ。
 */
MissionInfo::MissionInfo()
{
    m_currentMissionId = 0;
    m_isFirstClear = false;
    m_isArena = false;
    m_currentArenaId = 0;
}

/*
 * デストラクタ。
 */
MissionInfo::~MissionInfo()
{
}