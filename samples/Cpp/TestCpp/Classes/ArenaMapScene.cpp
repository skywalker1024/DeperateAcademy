//
//  ArenaMapScene.cpp
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//


#include "ArenaMapScene.h"
#include "GameConst.h"
#include "GraphicUtils.h"
#include "HomeScene.h"
#include "CommonUtils.h"
#include "DialogBaseLayer.h"
#include "MissionInfo.h"
#include "Battle.h"
#include "UserInfo.h"
#include "DialogLayer.h"
#include "ArenaInfoList.h"
ArenaMapScene::ArenaMapScene()
{
}

ArenaMapScene::~ArenaMapScene(){
}

CCScene * ArenaMapScene::scene(){
    CCScene* scene = CCScene::create();
    scene->addChild(ArenaMapScene::create());
    return scene;
}

bool ArenaMapScene::init(){
    if (!BaseScene::init()) {
        return false;
    }
    
    setBackBtn();
    int screenWidth = CommonUtils::getScreenWidth();
    int screenHeight = CommonUtils::getScreenHeight();

    string mapName = "img/map_0.jpg";
    CCSprite *mapSprite = CCSprite::create(mapName.c_str());
    CCSize size = mapSprite->getContentSize();
    mapSprite->setScaleX(screenWidth / size.width);
    mapSprite->setScaleY(screenHeight / size.height);
    mapSprite->setAnchorPoint(CCPointZero);
    mapSprite->setPosition(CCPointZero);
    this->addChild(mapSprite);
    
    
    
    CCLog("width =%d height =%d", CommonUtils::getScreenWidth(), CommonUtils::getScreenHeight());
    StringLabelList *test = GraphicUtils::drawString(this, "ArenaMapScene 每次5体力，胜利可以获得10钻", 250, 250, 710, 10, getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_RIGHT_MIDDLE, 60);
    CCLog("test %f %f", test->getPositionX(), test->getPositionY());
    
    //排行榜button
    return true;
}

void ArenaMapScene::onEnter(){
    BaseScene::onEnter();
    
    std::map<int, CCPoint>arena_pos;
    
    arena_pos[0] = ccp(100,500);
    arena_pos[1] = ccp(400,600);
    arena_pos[2] = ccp(600,600);
    arena_pos[3] = ccp(600,800);
    arena_pos[4] = ccp(650,900);
    for (int i=0; i<ArenaInfoList::shared()->getCount(); i++) {
        ArenaInfo * info = ArenaInfoList::shared()->getObject(i);
        //在map上添加arenaBtn
        //CCString * btnString = CCString::createWithFormat("%s 三国武力排名第%d", info->getName().c_str(), info->getRank());
        CCControlButton * missionBtn = CCControlButton::create(info->getName(), DEFAULT_FONT_NAME, 60);
        this->addChild(missionBtn);
        missionBtn->setPosition(arena_pos[i]);
        missionBtn->setTag(i);
        missionBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(ArenaMapScene::onArenaClick), CCControlEventTouchUpInside);
    }
}

void ArenaMapScene::onExit(){
    BaseScene::onExit();
}

void ArenaMapScene::onBackClick(){
    changeScene(HomeScene::scene());
}

void ArenaMapScene::onArenaClick(CCObject * sender, CCControlEvent controlEvent){
    
    if (UserInfo::shared()->getActionP() < 5) {
        if (UserInfo::shared()->getDiamond() < 100) {
            DialogLayer::showDialog("不足100钻补足体力，要去钻石商场买吗？", 2, this, callfunc_selector(ArenaMapScene::goToShop));
        }else{
            DialogLayer::showDialog("体力不足，花100钻补满吗？", 2, this, callfunc_selector(ArenaMapScene::buyActionP));
        }
        return;
    }
    
    int arenaIndex = dynamic_cast<CCControlButton*>(sender)->getTag();
    MissionInfo::shared()->setIsArena(true);
    MissionInfo::shared()->setCurrentArenaId(arenaIndex);
    changeScene(Battle::scene());
}

void ArenaMapScene::buyActionP(){
    pushStepScene("buy_action_p.php", "", NULL);
}

void ArenaMapScene::goToShop(){//TODO
    //changeScene(ShopScene::scene());
}

bool ArenaMapScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    BaseScene::ccTouchBegan(pTouch, pEvent);
    return false;
}
