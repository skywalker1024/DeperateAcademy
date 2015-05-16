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
#include "MissionMstList.h"
#include "LevelMstList.h"
#include "SoldierMstList.h"
#include "WallMstList.h"
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
        int y = screenHeight/ 2 + 300;
        GraphicUtils::drawString(this, lvStr, screenWidth/2, y, getSystemColor(COLOR_KEY_HP), TEXT_ALIGN_CENTER_MIDDLE, 60);
        //查看是否解锁城墙和兵种
        LevelMst * levelMst = LevelMstList::shared()->getObject(UserInfo::shared()->getLv());
        int unlock_solder_id = levelMst->getUnlockSoldierId();
        int unlock_wall_id = levelMst->getUnlockWallLv();
        
        if (unlock_solder_id > 0) {
            y -= 100;
            SoldierMst * soldierMst = SoldierMstList::shared()->getObject(unlock_solder_id);
            string str = CCString::createWithFormat("恭喜主公解锁了%s", soldierMst->getName().c_str())->m_sString;
            GraphicUtils::drawString(this, str, screenWidth/2, y, getSystemColor(COLOR_KEY_HP), TEXT_ALIGN_CENTER_MIDDLE, 60);
        }
        
        if (unlock_wall_id > 0) {
            y -= 100;
            WallMst * wallMst = WallMstList::shared()->getObject(unlock_wall_id);
            string str = CCString::createWithFormat("恭喜主公解锁了%s", wallMst->getName().c_str())->m_sString;
            GraphicUtils::drawString(this, str, screenWidth/2, y, getSystemColor(COLOR_KEY_HP), TEXT_ALIGN_CENTER_MIDDLE, 60);
        }
        
        if (MissionInfo::shared()->getIsWin()) {
            GraphicUtils::drawString(this, "恭喜主公旗开得胜！", screenWidth/2, screenHeight/ 2 - 100, getSystemColor(COLOR_KEY_HP), TEXT_ALIGN_CENTER_MIDDLE, 60);
        }else{
            GraphicUtils::drawString(this, "主公，别气馁，胜败兵家常事", screenWidth/2, screenHeight/ 2 - 100, getSystemColor(COLOR_KEY_HP), TEXT_ALIGN_CENTER_MIDDLE, 60);
        }
    }
    
   
    
    //请玩家评价
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("app_url")) {
        MissionMst *mst = MissionMstList::shared()->getObject(MissionInfo::shared()->getCurrentMissionId());
        if (mst->getId() > 5) {
            CommonUtils::showAlert();
            CCUserDefault::sharedUserDefault()->setBoolForKey("app_url", true);
        }
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

