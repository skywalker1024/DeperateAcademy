//
//  ArenaInfo.cpp
//  BraveFrontier

//  Created by WillArk on 5/10/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "ArenaInfo.h"
#include "CommonUtils.h"
// シングルトンインスタンス
ArenaInfo* ArenaInfoInstance = NULL;

/**
 * シングルトンインスタンスを取得。
 */
ArenaInfo* ArenaInfo::shared()
{
    if( ArenaInfoInstance == NULL )
    {
        ArenaInfoInstance = new ArenaInfo();
    }
    
    return ArenaInfoInstance;
}


/*
 * コンストラクタ。
 */
ArenaInfo::ArenaInfo()
{
    m_rank = 0;
    m_name = "";
    m_soldier = "";
    m_minTimer = 0;
    m_maxTimer = 0;
    m_minNum = 0;
    m_maxNum = 0;
    m_userId = 0;
    m_wallLv = 0;
}

/*
 * デストラクタ。
 */
ArenaInfo::~ArenaInfo()
{
}

void ArenaInfo::updateWithJson(Json::Value json){
    m_rank = CommonUtils::StrToInt( json["rank"].asString() );
    m_name = json["name"].asString();
    m_soldier = json["user_soldier"].asString();
    m_minTimer = CommonUtils::StrToInt( json["min_timer"].asString() );
    m_maxTimer = CommonUtils::StrToInt( json["max_timer"].asString() );
    m_minNum = CommonUtils::StrToInt( json["min_num"].asString() );
    m_maxNum = CommonUtils::StrToInt( json["max_num"].asString() );
    m_userId = CommonUtils::StrToInt( json["user_id"].asString() );
    m_wallLv = CommonUtils::StrToInt( json["wall_lv"].asString() );
    
    m_minTimer = 1000;
    m_maxTimer = 2000;
}