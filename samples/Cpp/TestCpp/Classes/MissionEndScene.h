//
//  MissionEndScene.h
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//

#ifndef __TestCpp__MissionEndScene__
#define __TestCpp__MissionEndScene__
#include "BaseScene.h"

class MissionEndScene : public BaseScene{
public:
    static CCScene * scene();
    MissionEndScene();
    virtual ~MissionEndScene();
    CREATE_FUNC(MissionEndScene);
    virtual bool init();

    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
private:
};


#endif /* defined(__TestCpp__MissionEndScene__) */
