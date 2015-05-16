//
//  ArenaMapScene.h
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//

#ifndef __TestCpp__ArenaMapScene__
#define __TestCpp__ArenaMapScene__
#include "BaseScene.h"

class ArenaMapScene : public BaseScene{
public:
    static CCScene * scene();
    ArenaMapScene();
    virtual ~ArenaMapScene();
    CREATE_FUNC(ArenaMapScene);
    virtual bool init();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void onEnter();
    virtual void onExit();

private:
    virtual void onBackClick();
    void onArenaClick(CCObject * sender, CCControlEvent controlEvent);
    void buyActionP();
    void goToShop();
};


#endif /* defined(__TestCpp__ArenaMapScene__) */
