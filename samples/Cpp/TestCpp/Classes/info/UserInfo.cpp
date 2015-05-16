//
//  UserInfo.cpp
//  BraveFrontier

//  Created by WillArk on 5/10/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "UserInfo.h"
#include "CommonUtils.h"
#include "GameConst.h"
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
    m_isLvup = false;
    m_arenaPoint = 0;
    m_arenaRank = 0;
    m_appUrl = "";
    m_isArenaWin = false;
    m_wallLv = 0;
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

void UserInfo::updateWithJson(Json::Value json){
    m_channel_user_id = json["channel_user_id"].asString();
    m_action_p = CommonUtils::StrToInt( json["action_p"].asString());
    m_max_action_p = CommonUtils::StrToInt( json["max_action_p"].asString() );
    m_name = json["name"].asString();
    m_diamond = CommonUtils::StrToInt( json["diamond"].asString());
    m_exp = CommonUtils::StrToInt( json["exp"].asString());
    m_lv = CommonUtils::StrToInt( json["lv"].asString());
    m_user_id = CommonUtils::StrToInt( json["id"].asString());
    m_wallLv = CommonUtils::StrToInt( json["wall_lv"].asString());
    
    setActionRestTimer(CommonUtils::StrToInt( json["action_rest_timer"].asString()));
}

void UserInfo::updateSoldierInfo(Json::Value json){
    m_soldierMap.clear();
    for (int i=0; i<json.size(); i++) {
        Json::Value userSoldier = json[i];
        int series = CommonUtils::StrToInt(userSoldier["series"].asString());
        int soldier_id = CommonUtils::StrToInt(userSoldier["soldier_id"].asString());
        m_soldierMap[series] = soldier_id;
    }
}

void UserInfo::updateClearMission(Json::Value json){
    m_clearMissionId.clear();
    for (int i=0; i<json.size(); i++) {
        Json::Value clearMission = json[i];
        int mission_id = CommonUtils::StrToInt(clearMission["mission_id"].asString());
        m_clearMissionId[i] = mission_id;
    }
}

map<int, int> UserInfo::getClearMissionId(){
    return m_clearMissionId;
}

void UserInfo::updateArenaInfo(Json::Value json){
    m_arenaPoint = CommonUtils::StrToInt(json["point"].asString());
    m_arenaRank = CommonUtils::StrToInt(json["rank"].asString());
}


/*
 * 行動力が最大になるまでの秒数を設定。
 */
void UserInfo::setActionRestTimer( int value )
{
    CCLog( " UserInfo::setActionRestTimer value=%d", value );
    
    actionRestTimer = value;
    
    actionReceiveTime = CommonUtils::getNowUnitxTime();
    
    CCLog( "UserInfo::setActionRestTimer actionReceiveTime=%l", actionReceiveTime );
}

/*
 * 行動力が最大になるまでの秒数を取得。
 */
int UserInfo::getActionRestTimer()
{
    return actionRestTimer;
}

/*
 * 行動力が最大になるまでの秒数を減らす。
 */
void UserInfo::decActionRestTimer()
{
    //CCLog( "action restTime=%d getRecoverTime=%d",actionRestTimer, DefineMst::shared()->getRecoverTimeAction() );
    
    if( actionRestTimer == 0 ) return;
    
    // 現在時間を取得
    long now_time = CommonUtils::getNowUnitxTime();
    
    // 経過秒数を取得
    int past_sec = ( now_time - actionReceiveTime );
    
    if( past_sec <= 0 ) return;
    
    for( int i = 0; i < past_sec; i++ )
    {
        actionRestTimer--;
        
        //CCLog( "time=%d", DefineMst::shared()->getRecoverTimeAction() );
        
        // 体力回復
        int time =  RECOVER_TIME;
        
        if( time > 0 )
        {
            if( actionRestTimer % time == 0 )
            {
                m_action_p++;
            }
        }
        
        if( m_action_p > m_max_action_p )
        {
            m_action_p = m_max_action_p;
        }
        
        if( actionRestTimer <= 0 ) break;
    }
    
    actionReceiveTime = now_time;
    
}