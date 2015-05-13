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

LoadingLayer * loadingLayerInstance = NULL;
/*
 * コンストラクタ。
 */
LoadingLayer::LoadingLayer()
{
    m_responseParser = NULL;
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
    //CC_SAFE_RELEASE_NULL(m_responseParser);
}

LoadingLayer * LoadingLayer::shared(){
    if (!loadingLayerInstance) {
        loadingLayerInstance = new LoadingLayer();
        loadingLayerInstance->init();
    }
    return loadingLayerInstance;
}
bool LoadingLayer::init(){
    if (!DialogBaseLayer::init()) {
        return false;
    }
    return true;
}
void LoadingLayer::clear(){
    connectIndex = 0;
    state = STATE_CONNECT_INIT;
    m_isFinished = false;
    m_nextScene = NULL;
    m_prevScene = NULL;
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
            CCLog( "LoadingLayer::accessPho connectIndex=%d", connectIndex );
            
            BaseRequest* req = ConnectRequestList::shared()->getObject( connectIndex );
            
            ResponseParser *responseParser = new ResponseParser();
            m_responseParser = NULL;//这行很重要，下面的set会release上一个的m_responseParser，但是上一个是个空指针，会crash
            this->setResponseParser(responseParser);
            NetworkManager::sharedInstance()->NetworkRequestPost(req->getFullUrl(), req->getFullData(), "", this->getResponseParser(), httpresponse_selector(ResponseParser::ResponseParse));
            m_isFinished = false;
            state = STATE_CONNECT_LOOP;
        }
    }

    // 通信終了待ち
    if( state == STATE_CONNECT_LOOP )
    {
        if( m_isFinished )
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

void LoadingLayer::backToTitle(){
    m_prevScene->changeScene(TitleScene::scene());
}

void LoadingLayer::retry(){
    state = STATE_CONNECT_INIT;
}

void LoadingLayer::noticeConfirm(){
    //提示一下就继续
    m_isFinished = true;
}

void LoadingLayer::changeNextScene(){
    if (getNextScene()) {
        m_prevScene->changeScene(getNextScene());
    }else{
        this->removeFromParent();
    }
}