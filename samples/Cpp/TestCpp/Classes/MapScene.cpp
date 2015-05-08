//
//  MapScene.cpp
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//


#include "MapScene.h"
#include "GameConst.h"
#include "GraphicUtils.h"
#include "HomeScene.h"
#include "CommonUtils.h"
#include "DialogBaseLayer.h"
#include "MissionInfo.h"
#include "Battle.h"
MapScene::MapScene()
{
}

MapScene::~MapScene(){
}

CCScene * MapScene::scene(){
    CCScene* scene = CCScene::create();
    scene->addChild(MapScene::create());
    return scene;
}

bool MapScene::init(){
    if (!BaseScene::init()) {
        return false;
    }
    int screenHeight = CommonUtils::getScreenHeight();
    //返回按钮
    CCControlButton * backBtn = CCControlButton::create("返回", DEFAULT_FONT_NAME, 60);
    addChild(backBtn);
    backBtn->setPosition(ccp(0, screenHeight - 100));
    backBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MapScene::onBack), CCControlEventTouchDown);
    
    //mission按钮
    CCControlButton * missionBtn = CCControlButton::create("虎牢关", DEFAULT_FONT_NAME, 60);
    addChild(missionBtn);
    missionBtn->setPosition(ccp(200, 200));
    missionBtn->setTag(1);
    missionBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MapScene::onBack), CCControlEventTouchDown);
    
    CCLog("width =%d height =%d", CommonUtils::getScreenWidth(), CommonUtils::getScreenHeight());
    StringLabelList *test = GraphicUtils::drawString(this, "MapScene", 250, 250, 710, 10, getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_RIGHT_MIDDLE, 100);
    CCLog("test %f %f", test->getPositionX(), test->getPositionY());
    
    return true;
}

void MapScene::onEnter(){
    BaseScene::onEnter();
}

void MapScene::onExit(){
    BaseScene::onExit();
}

bool MapScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    
    pushStepScene("get_user_info.php", "", HomeScene::scene());
    return true;
}

void MapScene::onBack(){
    changeScene(HomeScene::scene());
}

void MapScene::onMissionClick(CCObject * sender, CCControlEvent controlEvent){
    MissionInfo::shared()->setCurrentMissionId(dynamic_cast<CCControlButton*>(sender)->getTag());
    changeScene(Battle::scene());
}

