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
    for (int i=0; i<2; i++) {
        string mapName = CCString::createWithFormat("img/map_%d.jpg", i)->m_sString;
        CCSprite *mapSprite = CCSprite::create(mapName.c_str());
        CCSize size = mapSprite->getContentSize();
        mapSprite->setScaleX(screenWidth / size.width);
        mapSprite->setScaleY(screenHeight / size.height);
        mapSprite->setAnchorPoint(CCPointZero);
        mapSprite->setPosition(ccp(screenWidth*i, 0));
        m_mapLayer->addChild(mapSprite);
        m_mapList->addObject(mapSprite);
        
        //在map上添加missionBtn
        CCControlButton * missionBtn = CCControlButton::create("虎牢关", DEFAULT_FONT_NAME, 60);
        m_mapLayer->addChild(missionBtn);
        missionBtn->setPosition(ccp(i*screenWidth + 800, 800));
        missionBtn->setTag(1);
        missionBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MapScene::onMissionClick), CCControlEventTouchDown);
        m_missionButtonList->addObject(missionBtn);
    }
    
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
    MissionInfo::shared()->setCurrentMissionId(dynamic_cast<CCControlButton*>(sender)->getTag());
    changeScene(Battle::scene());
}

void MapScene::moveMap(CCTouch *pTouch){
    bool isLeft = m_prevPos.x - pTouch->getLocation().x > 0;
    int screenWidth = CommonUtils::getScreenWidth();
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

