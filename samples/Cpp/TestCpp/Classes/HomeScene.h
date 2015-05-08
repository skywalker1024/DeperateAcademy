//
//  HomeScene.h
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//

#ifndef __TestCpp__HomeScene__
#define __TestCpp__HomeScene__
#include "BaseScene.h"

class HomeScene : public BaseScene{
public:
    static CCScene * scene();
    HomeScene();
    virtual ~HomeScene();
    CREATE_FUNC(HomeScene);
    virtual bool init();

    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
private:
    void onQuestClick();
    void onEvoClick();
};


#endif /* defined(__TestCpp__HomeScene__) */
