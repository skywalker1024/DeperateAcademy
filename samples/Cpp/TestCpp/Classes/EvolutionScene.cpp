//
//  EvolutionScene.cpp
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//


#include "EvolutionScene.h"
#include "GameConst.h"
#include "GraphicUtils.h"
#include "Battle.h"
#include "UserInfo.h"
#include "SoldierMstList.h"
#include "EvoMstList.h"
#include "DialogLayer.h"
#include "LevelMstList.h"
#include "MapScene.h"
#include "HomeScene.h"
#include "WallMstList.h"
EvolutionScene::EvolutionScene()
{
}

EvolutionScene::~EvolutionScene(){
}

CCScene * EvolutionScene::scene(){
    CCScene* scene = CCScene::create();
    scene->addChild(EvolutionScene::create());
    return scene;
}

bool EvolutionScene::init(){
    if (!BaseScene::init()) {
        return false;
    }
    
    return true;
}

void EvolutionScene::onEnter(){
    BaseScene::onEnter();
    setHeader();
    setBackBtn();
    int screenWidth = CommonUtils::getScreenWidth();
    int screenHeight = CommonUtils::getScreenHeight();
   
    int start_y = screenHeight - 600;
    int fontSize = 60;
    //升级城墙
    int wallLv = UserInfo::shared()->getWallLv();
    {
        int WALL_START_Y = start_y + 100;
        WallMst * wallMst = WallMstList::shared()->getObject(wallLv);
        GraphicUtils::drawString(this, wallMst->getName(), 100, WALL_START_Y, getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_LEFT_MIDDLE, fontSize);
        WallMst * nextWallMst = WallMstList::shared()->getObject(wallLv + 1);
        if (nextWallMst) {
            GraphicUtils::drawString(this, nextWallMst->getName(), 300, WALL_START_Y, getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_LEFT_MIDDLE, fontSize);
            
            GraphicUtils::drawString(this, CommonUtils::IntToString( nextWallMst->getCost() ).append("钻"), 500, WALL_START_Y, getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_LEFT_MIDDLE, fontSize);
            
            CCLabelTTF * questLabel = CCLabelTTF::create("升级", DEFAULT_FONT_NAME, 60);
            CCControlButton * button = CCControlButton::create(questLabel, CCScale9Sprite::create("img/button.png") );
            button->setBackgroundSpriteForState(CCScale9Sprite::create("img/buttonHighlighted.png"), CCControlStateHighlighted);//按下后的图片
            button->addTargetWithActionForControlEvents(this, cccontrol_selector(EvolutionScene::onWallClick), CCControlEventTouchUpInside);
            button->setPosition(ccp(700, WALL_START_Y - 116));
            button->setAnchorPoint(ccp(0, 0.5));
            this->addChild(button);
        }else{
            GraphicUtils::drawString(this, "已到顶级", 300, WALL_START_Y, getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_LEFT_MIDDLE, fontSize);
        }
    }
    
    
    map<int, int>userSoldierMap = UserInfo::shared()->m_soldierMap;
    for(int i=1; i<userSoldierMap.size() + 1; i++){
        int soldierId = userSoldierMap[i];
        
        SoldierMst * soldierMst = SoldierMstList::shared()->getObject(soldierId);
        //beforeLabel
        GraphicUtils::drawString(this, soldierMst->getName(), 100, start_y - 100 * i, getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_LEFT_MIDDLE, fontSize);
        
        EvoMst * evoMst = EvoMstList::shared()->getObjectByBeforeId(soldierId);
        if ( evoMst ) {//还没到顶级
            int afterId = evoMst->getAfterId();
            SoldierMst * soldierMst = SoldierMstList::shared()->getObject(afterId);
            GraphicUtils::drawString(this, soldierMst->getName(), 300, start_y - 100 * i, getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_LEFT_MIDDLE, fontSize);
     
            GraphicUtils::drawString(this, CommonUtils::IntToString( evoMst->getCost() ).append("钻"), 500, start_y - 100 * i, getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_LEFT_MIDDLE, fontSize);
            
            CCLabelTTF * questLabel = CCLabelTTF::create("升级", DEFAULT_FONT_NAME, 60);
            CCControlButton * button = CCControlButton::create(questLabel, CCScale9Sprite::create("img/button.png") );
            button->setBackgroundSpriteForState(CCScale9Sprite::create("img/buttonHighlighted.png"), CCControlStateHighlighted);//按下后的图片
            button->addTargetWithActionForControlEvents(this, cccontrol_selector(EvolutionScene::onEvoClick), CCControlEventTouchUpInside);
            button->setPosition(ccp(700, start_y - 116 - 100 * i));
            button->setTag(evoMst->getId());
            button->setAnchorPoint(ccp(0, 0.5));
            this->addChild(button);
        }else{
            GraphicUtils::drawString(this, "已到顶级", 300, start_y - 100 * i, getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_LEFT_MIDDLE, fontSize);
        }
    }
}

void EvolutionScene::onExit(){
    BaseScene::onExit();
}

bool EvolutionScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    BaseScene::ccTouchBegan(pTouch, pEvent);
    return false;
}

void EvolutionScene::onEvoClick(CCObject * sender, CCControlEvent controlEvent){
    //判断钻石够不
    int evoId = dynamic_cast<CCControlButton*>(sender)->getTag();
    EvoMst *evoMst = EvoMstList::shared()->getObject(evoId);
    int cost = evoMst->getCost();
    if (cost > UserInfo::shared()->getDiamond()) {
        DialogLayer::showDialog("钻石不足", 2, this, callfunc_selector(EvolutionScene::goToShop), NULL, NULL, "钻石商店", "");
        return;
    }
    //判断等级够不
    LevelMst *levelMst = LevelMstList::shared()->getObjectByUnLockSoldierId(evoMst->getAfterId());
    if (UserInfo::shared()->getLv() < levelMst->getLv()) {
        CCString *notice = CCString::createWithFormat("等级不足%d级",levelMst->getLv());
        DialogLayer::showDialog(notice->getCString(), 2, this, callfunc_selector(EvolutionScene::goToMission), NULL, NULL, "出征", "");
        return;
    }
    //添加request
    string postData = string("evo_id=").append(CommonUtils::IntToString(evoId));
    pushStepScene("evolution.php", postData, EvolutionScene::scene());
}

void EvolutionScene::onWallClick(){
    int wallLv = UserInfo::shared()->getWallLv();
    WallMst *wallMst = WallMstList::shared()->getObject(wallLv + 1);
    if (wallMst) {
        int cost = wallMst->getCost();
        if (cost > UserInfo::shared()->getDiamond()) {
            DialogLayer::showDialog("钻石不足", 2, this, callfunc_selector(EvolutionScene::goToShop), NULL, NULL, "钻石商店", "");
            return;
        }
        //判断等级够不
        LevelMst *levelMst = LevelMstList::shared()->getObjectByUnLockWallLv(wallMst->getLv());
        if (UserInfo::shared()->getLv() < levelMst->getLv()) {
            CCString *notice = CCString::createWithFormat("等级不足%d级",levelMst->getLv());
            DialogLayer::showDialog(notice->getCString(), 2, this, callfunc_selector(EvolutionScene::goToMission), NULL, NULL, "出征", "");
            return;
        }
            
        
        pushStepScene("evolution_wall.php", "", EvolutionScene::scene());
    }
}
void EvolutionScene::goToShop(){
    CCLog("goto shop");//TODO
}

void EvolutionScene::goToMission(){
    changeScene(MapScene::scene());
}

void EvolutionScene::onBackClick(){
    changeScene(HomeScene::scene());
}
