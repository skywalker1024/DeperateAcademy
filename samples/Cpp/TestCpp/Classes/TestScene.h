//
//  TestScene.h
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//

#ifndef __TestCpp__TestScene__
#define __TestCpp__TestScene__
#include "BaseScene.h"

class TestScene : public BaseScene{
public:
    static CCScene * scene();
    TestScene();
    virtual ~TestScene();
    CREATE_FUNC(TestScene);
    virtual bool init();

    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
private:
    void onQuestClick();
    void onEvoClick();
    void onArenaClick();
};


#endif /* defined(__TestCpp__TestScene__) */
