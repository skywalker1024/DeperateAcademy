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
private:
    void onBack();
    void onMissionClick(CCObject * sender, CCControlEvent controlEvent);
};


#endif /* defined(__TestCpp__MapScene__) */
