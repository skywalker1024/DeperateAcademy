//
//  UserInfo.cpp
//  BraveFrontier

//  Created by WillArk on 5/10/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "UserInfo.h"
#include "CommonUtils.h"
// シングルトンインスタンス
UserInfo* userInfoInstance = NULL;

/**
 * シングルトンインスタンスを取得。
 */
UserInfo* UserInfo::shared()
{
    if( userInfoInstance == NULL )
    {
        userInfoInstance = new UserInfo();
    }
    
    return userInfoInstance;
}


/*
 * コンストラクタ。
 */
UserInfo::UserInfo()
{
    m_channel_user_id = CommonUtils::getChannelUserId();
    m_action_p = 0;
    m_max_action_p = 0;
    m_name = "";
    m_diamond = 0;
    m_exp = 0;
    m_lv = 0;
    m_user_id = 0;
}

/*
 * デストラクタ。
 */
UserInfo::~UserInfo()
{
}

/*
 * ユーザーが存在するか。
 */
bool UserInfo::existUser()
{
    if (m_user_id == 0) {
        return false;
    }
    
    return true;
}