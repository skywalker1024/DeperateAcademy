//
//  LoadingLayer.cpp
//  BraveFrontier

//  Created by WillArk on 11/13/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "LoadingLayer.h"
#include "ConnectRequestList.h"
#include "NetworkManager.h"
#include "CommonUtils.h"
#include "RegisterScene.h"
#include "UserInfo.h"
#include "DialogLayer.h"
#include "TitleScene.h"
#include "GraphicUtils.h"
#include "GameConst.h"
#include "MissionInfo.h"
/*
 * コンストラクタ。
 */
LoadingLayer::LoadingLayer()
{
    connectIndex = 0;
    state = STATE_CONNECT_INIT;
    m_isFinish = false;
    m_nextScene = NULL;
    m_prevScene = NULL;
}

/*
 * デストラクタ。
 */
LoadingLayer::~LoadingLayer()
{
    ConnectRequestList::shared()->removeAllObjects();
    if (m_nextScene) {
        CC_SAFE_RELEASE_NULL(m_nextScene);
    }
    CC_SAFE_RELEASE_NULL(m_prevScene);
}

bool LoadingLayer::init(){
    if (!DialogBaseLayer::init()) {
        return false;
    }
    return true;
}

void LoadingLayer::onEnter(){
    DialogBaseLayer::onEnter();
    
    //添加loading小人 和 通讯中字符串
    /*
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("ccs-res/armature/knight.png", "ccs-res/armature/knight.plist", "ccs-res/armature/knight.xml", this, NULL);
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("ccs-res/armature/weapon.png", "ccs-res/armature/weapon.plist", "ccs-res/armature/weapon.xml", this, NULL);

    CCArmature * armature = new cocos2d::extension::CCArmature();
    armature->init("Knight_f/Knight");
    armature->getAnimation()->playWithIndex(1);
    armature->setPosition(CommonUtils::getScreenWidth() / 2, CommonUtils::getScreenHeight() / 2);
    addChild(armature);
    armature->release();
    */
    std::vector<string>tips;
    tips.push_back("升级可以解锁更多兵种");
    tips.push_back("在竞技场取胜可以获得钻石");
    tips.push_back("战斗中点错方块会出现更多敌军");
    string str = tips[arc4random() % tips.size()].append("\n通讯中...");
    GraphicUtils::drawString(this, str, CommonUtils::getScreenWidth() / 2, CommonUtils::getScreenHeight() / 2 - 100, m_prevScene->getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_CENTER_MIDDLE, 60);
}

/*
 * 定期更新処理。
 */
void LoadingLayer::draw()
{
    // 通信初期化
    if( state == STATE_CONNECT_INIT )
    {
        if( connectIndex >= ConnectRequestList::shared()->getCount() )
        {
            state = STATE_NEXT;
        }
        else
        {
            CCLOG( "LoadingLayer::accessPho" );
            
            BaseRequest* req = ConnectRequestList::shared()->getObject( connectIndex );
            
            NetworkManager::sharedInstance()->NetworkRequestPost(req->getFullUrl(), req->getFullData(), "", this, httpresponse_selector(LoadingLayer::ResponseParse));
            m_isFinish = false;
            state = STATE_CONNECT_LOOP;
        }
    }

    // 通信終了待ち
    if( state == STATE_CONNECT_LOOP )
    {
        if( m_isFinish )
        {
            state = STATE_CONNECT_INIT;
            connectIndex++;
        }
    }
    
    // 次の画面へ
    if( state == STATE_NEXT )
    {
        changeNextScene();
    }
}

SEL_HttpResponse LoadingLayer::ResponseParse(CCHttpClient* client, CCHttpResponse* response){
    if (!response->isSucceed()) {
        CCLog("not succeed");
        if (response->getResponseCode() == 500) {
            //test
            DialogLayer::showDialog("服务器出错，将回到登录界面。", 1, this, callfunc_selector(LoadingLayer::backToTitle), NULL, NULL, "", "");
        }else{
            DialogLayer::showDialog("通讯不良，请重试", 1, this, callfunc_selector(LoadingLayer::retry), NULL, NULL, "", "");
        }
        
        return NULL;
    }
    Json::Value responseJson;
    CommonUtils::ReadIntoJson(response->getResponseData(), responseJson, true);
    
    //check error
    if (!responseJson["error"].isNull()) {
        //show dialog and exit todo
        if (responseJson["error"].asString().find("no user") != string::npos) {
            if (UserInfo::shared()->existUser()) {//出错
                //test
                DialogLayer::showDialog(responseJson["error"].asCString(), 1, this, callfunc_selector(LoadingLayer::backToTitle), NULL, NULL, "", "");
            }else{ //去register
                m_prevScene->changeScene(RegisterScene::scene());
            }
        }else{
            DialogLayer::showDialog(responseJson["error"].asCString(), 1, this, callfunc_selector(LoadingLayer::backToTitle), NULL, NULL, "", "");
        }
        return NULL;
    }
    
    if (!responseJson["notice"].isNull()) {
        DialogLayer::showDialog(responseJson["notice"].asCString(), 1, this, callfunc_selector(LoadingLayer::noticeConfirm), NULL, NULL, "", "");
        return NULL;
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
    
    m_isFinish = true;
    return NULL;
    //CCLog("responseData=%s", responseJson);
}

void LoadingLayer::backToTitle(){
    m_prevScene->changeScene(TitleScene::scene());
}

void LoadingLayer::retry(){
    state = STATE_CONNECT_INIT;
}

void LoadingLayer::noticeConfirm(){
    //提示一下就继续
    m_isFinish = true;
}

void LoadingLayer::changeNextScene(){
    if (getNextScene()) {
        m_prevScene->changeScene(getNextScene());
    }else{
        this->removeFromParent();
    }
}