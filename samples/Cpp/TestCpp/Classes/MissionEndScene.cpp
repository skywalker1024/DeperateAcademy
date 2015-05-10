//
//  MissionEndScene.cpp
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//


#include "MissionEndScene.h"
#include "GameConst.h"
#include "GraphicUtils.h"
#include "MapScene.h"
#include "EvolutionScene.h"
#include "MapScene.h"
#include "MissionInfo.h"
#include "UserInfo.h"
MissionEndScene::MissionEndScene()
{
}

MissionEndScene::~MissionEndScene(){
}

CCScene * MissionEndScene::scene(){
    CCScene* scene = CCScene::create();
    scene->addChild(MissionEndScene::create());
    return scene;
}

bool MissionEndScene::init(){
    if (!BaseScene::init()) {
        return false;
    }
    
    return true;
}

void MissionEndScene::onEnter(){
    BaseScene::onEnter();
    setHeader();
    
    if (MissionInfo::shared()->getIsFirstClear()) {
        int screenWidth = CommonUtils::getScreenWidth();
        int screenHeight = CommonUtils::getScreenHeight();
        
        GraphicUtils::drawString(this, "首次通关获得100钻！", screenWidth/2, screenHeight/ 2, getSystemColor(COLOR_KEY_HP), TEXT_ALIGN_CENTER_MIDDLE, 60);
    }
    
    if (UserInfo::shared()->getIsLvup()) {
        int screenWidth = CommonUtils::getScreenWidth();
        int screenHeight = CommonUtils::getScreenHeight();
        
        string lvStr = CCString::createWithFormat("%d => %d 升级!", UserInfo::shared()->getLv() - 1, UserInfo::shared()->getLv())->m_sString;
        GraphicUtils::drawString(this, lvStr, screenWidth/2, screenHeight/ 2 + 100, getSystemColor(COLOR_KEY_HP), TEXT_ALIGN_CENTER_MIDDLE, 60);
    }
    
}

void MissionEndScene::onExit(){
    BaseScene::onExit();
}

bool MissionEndScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    BaseScene::ccTouchBegan(pTouch, pEvent);
    changeScene(MapScene::scene());
    return false;
}

