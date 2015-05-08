//
//  UserInfo.h
//  BraveFrontier

//  Created by WillArk on 5/10/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_UserInfo_h
#define BraveFrontier_UserInfo_h

#include "cocos2d.h"

USING_NS_CC;
#include "json.h"
class UserInfo : public CCObject
{
public:
    // インスタンスの取得
    static UserInfo* shared();
    static void destroy();
    bool existUser();
    void updateWithJson(Json::Value json);
    map<int, int> m_soldierMap; //key是serieid 1~4 value是soldierId
    void updateSoldierInfo(Json::Value json);
private:
    // コンストラクタ
    UserInfo();
    // デストラクタ
    ~UserInfo();
    CC_SYNTHESIZE(int, m_user_id, UserId);
    CC_SYNTHESIZE(string, m_channel_user_id, ChannelUserId);
    CC_SYNTHESIZE(int, m_action_p, ActionP);
    CC_SYNTHESIZE(int, m_max_action_p, MaxActionP);
    CC_SYNTHESIZE(string, m_name, Name);
    CC_SYNTHESIZE(int, m_diamond, Diamond);
    CC_SYNTHESIZE(int, m_exp, Exp);
    CC_SYNTHESIZE(int, m_lv, Lv);
    
};

#endif
