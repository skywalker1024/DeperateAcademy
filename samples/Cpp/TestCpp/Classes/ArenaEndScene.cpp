//
//  ArenaEndScene.cpp
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//


#include "ArenaEndScene.h"
#include "GameConst.h"
#include "GraphicUtils.h"
#include "MapScene.h"
#include "EvolutionScene.h"
#include "ArenaMapScene.h"
#include "MissionInfo.h"
#include "UserInfo.h"
#include "MissionMstList.h"
ArenaEndScene::ArenaEndScene()
{
}

ArenaEndScene::~ArenaEndScene(){
}

CCScene * ArenaEndScene::scene(){
    CCScene* scene = CCScene::create();
    scene->addChild(ArenaEndScene::create());
    return scene;
}

bool ArenaEndScene::init(){
    if (!BaseScene::init()) {
        return false;
    }
    
    return true;
}

void ArenaEndScene::onEnter(){
    BaseScene::onEnter();
    setHeader();
    
    int screenWidth = CommonUtils::getScreenWidth();
    int screenHeight = CommonUtils::getScreenHeight();
    if (UserInfo::shared()->getIsArenaWin()) {
        GraphicUtils::drawString(this, "获得10钻!", screenWidth/2, screenHeight/ 2 + 100, getSystemColor(COLOR_KEY_HP), TEXT_ALIGN_CENTER_MIDDLE, 60);
    }else{
        GraphicUtils::drawString(this, "主公，别气馁，胜败兵家常事", screenWidth/2, screenHeight/ 2 + 100, getSystemColor(COLOR_KEY_HP), TEXT_ALIGN_CENTER_MIDDLE, 60);
    }

}

void ArenaEndScene::onExit(){
    BaseScene::onExit();
}

bool ArenaEndScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    BaseScene::ccTouchBegan(pTouch, pEvent);
    pushStepScene("get_arena_list.php", "", ArenaMapScene::scene());
    return false;
}

