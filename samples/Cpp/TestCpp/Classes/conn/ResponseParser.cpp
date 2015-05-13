//
//  ResponseParser.cpp
//  BraveFrontier

//  Created by WillArk on 11/13/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "ResponseParser.h"
#include "DialogLayer.h"
#include "UserInfo.h"
#include "RegisterScene.h"
#include "MissionInfo.h"
#include "LoadingLayer.h"
/*
 * コンストラクタ。
 */
ResponseParser::ResponseParser()
{
}

/*
 * デストラクタ。
 */
ResponseParser::~ResponseParser()
{
}

bool ResponseParser::init(){
    return true;
}

void ResponseParser::ResponseParse(CCHttpClient* client, CCHttpResponse* response){
    if (!response->isSucceed()) {
        CCLog("not succeed");
        if (response->getResponseCode() == 500) {
            //test
            DialogLayer::showDialog("服务器出错，将回到登录界面。", 1, LoadingLayer::shared(), callfunc_selector(LoadingLayer::backToTitle), NULL, NULL, "", "");
        }else{
            DialogLayer::showDialog("通讯不良，请重试", 1, LoadingLayer::shared(), callfunc_selector(LoadingLayer::retry), NULL, NULL, "", "");
        }
        return;
    }
    Json::Value responseJson;
    CommonUtils::ReadIntoJson(response->getResponseData(), responseJson, true);
    
    //check error
    if (!responseJson["error"].isNull()) {
        //show dialog and exit todo
        if (responseJson["error"].asString().find("no user") != string::npos) {
            if (UserInfo::shared()->existUser()) {//出错
                //test
                DialogLayer::showDialog(responseJson["error"].asCString(), 1, LoadingLayer::shared(), callfunc_selector(LoadingLayer::backToTitle), NULL, NULL, "", "");
            }else{ //去register
                LoadingLayer::shared()->getPrevScene()->changeScene(RegisterScene::scene());
            }
        }else{
            DialogLayer::showDialog(responseJson["error"].asCString(), 1, LoadingLayer::shared(), callfunc_selector(LoadingLayer::backToTitle), NULL, NULL, "", "");
        }
        return;
    }
    
    if (!responseJson["notice"].isNull()) {
        DialogLayer::showDialog(responseJson["notice"].asCString(), 1, LoadingLayer::shared(), callfunc_selector(LoadingLayer::noticeConfirm), NULL, NULL, "", "");
        return;
    }
    
    if (!responseJson["user_info"].isNull()) {
        UserInfo::shared()->updateWithJson(responseJson["user_info"]);
    }
    
    if (!responseJson["user_soldier"].isNull()) {
        UserInfo::shared()->updateSoldierInfo(responseJson["user_soldier"]);
    }
    
    if (!responseJson["is_first_clear"].isNull()) {
        MissionInfo::shared()->setIsFirstClear( responseJson["is_first_clear"].asBool() );
    }
    
    if (!responseJson["user_clear_mission"].isNull()) {
        UserInfo::shared()->updateClearMission( responseJson["user_clear_mission"] );
    }
    
    if (!responseJson["is_lvup"].isNull()) {
        UserInfo::shared()->setIsLvup( responseJson["is_lvup"].asBool() );
    }
    
    if (!responseJson["arena_info"].isNull()) {
        UserInfo::shared()->updateArenaInfo( responseJson["arena_info"] );
    }
    
    LoadingLayer::shared()->setIsFinished(true);
    return;
    //CCLog("responseData=%s", responseJson);
}