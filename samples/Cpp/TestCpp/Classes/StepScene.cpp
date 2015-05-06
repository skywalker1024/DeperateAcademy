//
//  StepScene.cpp
//  BraveFrontier

//  Created by WillArk on 11/13/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "StepScene.h"
#include "ConnectRequestList.h"
#include "NetworkManager.h"
#include "CommonUtils.h"
#include "RegisterScene.h"
#include "UserInfo.h"
#include "DialogLayer.h"
#include "TitleScene.h"
/*
 * コンストラクタ。
 */
StepScene::StepScene()
{
    connectIndex = 0;
    state = STATE_CONNECT_INIT;
    m_isFinish = false;
}

/*
 * デストラクタ。
 */
StepScene::~StepScene()
{
    ConnectRequestList::shared()->removeAllObjects();
}

CCScene * StepScene::scene(){
    CCScene* scene = CCScene::create();
    scene->addChild(StepScene::create());
    return scene;
}

bool StepScene::init(){
    if (!BaseScene::init()) {
        return false;
    }
    return true;
}

void StepScene::onEnter(){
    BaseScene::onEnter();
}

void StepScene::onExit(){
    BaseScene::onExit();
}
/*
 * 定期更新処理。
 */
void StepScene::draw()
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
            CCLOG( "StepScene::accessPho" );
            
            BaseRequest* req = ConnectRequestList::shared()->getObject( connectIndex );
            
            NetworkManager::sharedInstance()->NetworkRequestPost(req->getFullUrl(), req->getFullData(), "", this, httpresponse_selector(StepScene::ResponseParse));
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
        CCDirector::sharedDirector()->popScene();
    }
}

SEL_HttpResponse StepScene::ResponseParse(CCHttpClient* client, CCHttpResponse* response){

        
    if (!response->isSucceed()) {
        CCLog("not succeed");
        if (response->getResponseCode() == 500) {
            //test
            DialogLayer::showDialog("服务器出错，将回到登录界面。", 1, this, callfunc_selector(StepScene::backToTitle), NULL, NULL, "", "");
        }else{
            DialogLayer::showDialog("通讯不良，请重试", 1, this, callfunc_selector(StepScene::retry), NULL, NULL, "", "");
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
                DialogLayer::showDialog(responseJson["error"].asCString(), 1, this, callfunc_selector(StepScene::backToTitle), NULL, NULL, "", "");
            }else{ //去register
                CCDirector::sharedDirector()->popScene();
                changeScene(RegisterScene::scene());
            }
        }else{
            DialogLayer::showDialog(responseJson["error"].asCString(), 1, this, callfunc_selector(StepScene::backToTitle), NULL, NULL, "", "");
        }
        return NULL;
    }
    
    if (!responseJson["notice"].isNull()) {
        DialogLayer::showDialog(responseJson["notice"].asCString(), 1, this, callfunc_selector(StepScene::noticeConfirm), NULL, NULL, "", "");
        return NULL;
    }
    
    if (!responseJson["user_info"].isNull()) {
        UserInfo::shared()->updateWithJson(responseJson["user_info"]);
    }
    
    m_isFinish = true;
    return NULL;
    //CCLog("responseData=%s", responseJson);
}

void StepScene::backToTitle(){
    CCDirector::sharedDirector()->popScene();
    changeScene(TitleScene::scene());
}

void StepScene::retry(){
    state = STATE_CONNECT_INIT;
}

void StepScene::noticeConfirm(){
    //提示一下就继续
    m_isFinish = true;
}