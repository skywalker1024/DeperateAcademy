//
//  MapScene.h
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//

#ifndef __TestCpp__MapScene__
#define __TestCpp__MapScene__
#include "BaseScene.h"

class MapScene : public BaseScene{
public:
    static CCScene * scene();
    MapScene();
    virtual ~MapScene();
    CREATE_FUNC(MapScene);
    virtual bool init();

    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
private:
    virtual void onBackClick();
    void onMissionClick(CCObject * sender, CCControlEvent controlEvent);
    CCMutableArray<CCControlButton *> * m_missionButtonList;
    CCMutableArray<CCSprite *> * m_mapList;
    CCLayer * m_mapLayer;
    CCPoint m_prevPos;
    void moveMap(CCTouch *pTouch);
    int m_currentMap;
    void buyActionP();
    void goToShop();
};


#endif /* defined(__TestCpp__MapScene__) */
