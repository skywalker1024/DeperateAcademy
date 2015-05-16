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
#include "UserInfo.h"
#include "DialogLayer.h"
MapScene::MapScene()
{
    m_missionButtonList = new CCMutableArray<CCControlButton*>();
    m_mapList = new CCMutableArray<CCSprite*>();
    m_prevPos = CCPointZero;
    m_currentMap = 0;
}

MapScene::~MapScene(){
    CC_SAFE_RELEASE_NULL(m_missionButtonList);
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
    
    m_mapLayer = CCLayer::create();
    m_mapLayer->setPosition(CCPointZero);
    this->addChild(m_mapLayer);
    int screenWidth = CommonUtils::getScreenWidth();
    int screenHeight = CommonUtils::getScreenHeight();
    
    //添加map
    std::vector<int>mapList;
    int max_mission_id = 0;
    for (int i=0; i<UserInfo::shared()->getClearMissionId().size(); i++) {
        int mission_id = UserInfo::shared()->getClearMissionId()[i];
        MissionMst * missionMst = MissionMstList::shared()->getObject(mission_id);
        int mapId = missionMst->getMapId();
        bool hasMap = false;
        for (int j=0; j<mapList.size(); j++) {
            if (mapList[j] == mapId) {
                hasMap = true;
                break;
            }
        }
        if (!hasMap) {
            mapList.push_back(mapId);
        }
        
        if (mission_id > max_mission_id) {
            max_mission_id = mission_id;
        }
    }
    int next_mission_id = max_mission_id + 1;
    MissionMst * missionMst = MissionMstList::shared()->getObject(next_mission_id);
    if (missionMst) {
        int  mapId = missionMst->getMapId();
        m_currentMap = mapId - 1;
        bool hasMap = false;
        for (int j=0; j<mapList.size(); j++) {
            if (mapList[j] == mapId) {
                hasMap = true;
                break;
            }
        }
        if (!hasMap) {
            mapList.push_back(mapId);
        }
    }else{
        next_mission_id = 0;
        
        MissionMst * missionMst = MissionMstList::shared()->getObject(max_mission_id);
        m_currentMap = missionMst->getMapId() - 1;
    }
    
    std::sort(mapList.begin(), mapList.end());
    std::vector<int>::iterator it;
    it = mapList.begin();
    
    while (it != mapList.end())
    {
        int mapId = *it;
        string mapName = CCString::createWithFormat("img/map_%d.jpg", mapId - 1)->m_sString;
        CCSprite *mapSprite = CCSprite::create(mapName.c_str());
        CCSize size = mapSprite->getContentSize();
        mapSprite->setScaleX(screenWidth / size.width);
        mapSprite->setScaleY(screenHeight / size.height);
        mapSprite->setAnchorPoint(CCPointZero);
        mapSprite->setPosition(ccp(screenWidth * (mapId - 1), 0));
        m_mapLayer->addChild(mapSprite);
        m_mapList->addObject(mapSprite);
        it++;
    }
    
    for (int i=0; i<UserInfo::shared()->getClearMissionId().size(); i++) {
        int mission_id = UserInfo::shared()->getClearMissionId()[i];
        MissionMst * missionMst = MissionMstList::shared()->getObject(mission_id);
        int mapId= missionMst->getMapId();
        //在map上添加missionBtn
        CCControlButton * missionBtn = CCControlButton::create(missionMst->getName(), DEFAULT_FONT_NAME, 60);
        m_mapLayer->addChild(missionBtn);
        missionBtn->setPosition(ccp((mapId - 1) * screenWidth + missionMst->getPosX(), missionMst->getPosY()));
        missionBtn->setTag(missionMst->getId());
        missionBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MapScene::onMissionClick), CCControlEventTouchUpInside);
        m_missionButtonList->addObject(missionBtn);
    }
    //添加下一个mission
    if (next_mission_id) {
        MissionMst * missionMst = MissionMstList::shared()->getObject(next_mission_id);
        int mapId= missionMst->getMapId();
        //在map上添加missionBtn
        CCControlButton * missionBtn = CCControlButton::create(missionMst->getName(), DEFAULT_FONT_NAME, 60);
        m_mapLayer->addChild(missionBtn);
        missionBtn->setPosition(ccp((mapId - 1) * screenWidth + missionMst->getPosX(), missionMst->getPosY()));
        missionBtn->setTag(missionMst->getId());
        missionBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MapScene::onMissionClick), CCControlEventTouchUpInside);
        m_missionButtonList->addObject(missionBtn);
    }
    m_mapLayer->setPositionX(-screenWidth * m_currentMap);
    setBackBtn();
    
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
    if (m_backBtn->ccTouchBegan(pTouch, pEvent)) {
        return false;
    }
    for (int i=0; i<m_missionButtonList->count(); i++) {
        CCControlButton *missionBtn = m_missionButtonList->getObjectAtIndex(i);
        if (missionBtn->ccTouchBegan(pTouch, pEvent)) {
            return false;
        }
    }
    m_prevPos = pTouch->getLocation();
    CCLog("m_prevPos x=%f y=%f", m_prevPos.x, m_prevPos.y);
    return true;
}

void MapScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    CCPoint nowPos = pTouch->getLocation();
    int screenWidth = CommonUtils::getScreenWidth();
    float distance = nowPos.x - m_prevPos.x;
    bool isLeft = distance < 0 ;
    if (( isLeft && m_currentMap + 1 >= m_mapList->count() )||( !isLeft && m_currentMap < 1 )){//左右极限
    }else{
        m_mapLayer->setPositionX( -m_currentMap * screenWidth + distance);
    }
    CCLog("ccTouchMoved x=%f y=%f", pTouch->getLocation().x, pTouch->getLocation().y);
}
void MapScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    moveMap(pTouch);
    CCLog("ccTouchEnded x=%f y=%f", pTouch->getLocation().x, pTouch->getLocation().y);
}
void MapScene::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){
    moveMap(pTouch);
    CCLog("ccTouchCancelled x=%f y=%f", pTouch->getLocation().x, pTouch->getLocation().y);
}

void MapScene::onBackClick(){
    changeScene(HomeScene::scene());
}

void MapScene::onMissionClick(CCObject * sender, CCControlEvent controlEvent){
    int missionId = dynamic_cast<CCControlButton*>(sender)->getTag();
    MissionMst *missionMst = MissionMstList::shared()->getObject(missionId);
    if (UserInfo::shared()->getActionP() < missionMst->getActionP()) {
        if (UserInfo::shared()->getDiamond() < 100) {
            DialogLayer::showDialog("不足100钻补足体力，要去钻石商场买吗？", 2, this, callfunc_selector(MapScene::goToShop));
        }else{
            DialogLayer::showDialog("体力不足，花100钻补满吗？", 2, this, callfunc_selector(MapScene::buyActionP));
        }
        return;
    }

    MissionInfo::shared()->setCurrentMissionId(missionId);
    MissionInfo::shared()->setIsArena(false);
    changeScene(Battle::scene());
}

void MapScene::moveMap(CCTouch *pTouch){
    int screenWidth = CommonUtils::getScreenWidth();
    if(fabs(m_prevPos.x - pTouch->getLocation().x) < 10){
        m_mapLayer->runAction(CCMoveTo::create(.1f, ccp(-screenWidth * m_currentMap, 0)));
        return;
    }
    CCLog("moveMap x=%f y=%f", pTouch->getLocation().x, pTouch->getLocation().y);

    bool isLeft = m_prevPos.x - pTouch->getLocation().x > 0;
    if (isLeft) {
        if (m_currentMap + 1 < m_mapList->count()) {//右边还有
            m_mapLayer->runAction(CCMoveTo::create(.1f, ccp(-screenWidth * (m_currentMap + 1), 0)));
            m_currentMap += 1;
        }
    }else{
        if (m_currentMap > 0) {//左边还有
            m_mapLayer->runAction(CCMoveTo::create(.1f, ccp(-screenWidth * (m_currentMap - 1), 0)));
            m_currentMap -= 1;
        }
    }
}

void MapScene::buyActionP(){
    pushStepScene("buy_action_p.php", "", MapScene::scene());
}

void MapScene::goToShop(){//TODO
    //changeScene(ShopScene::scene());
}
