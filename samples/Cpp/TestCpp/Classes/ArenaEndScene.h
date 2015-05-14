//
//  ArenaEndScene.h
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//

#ifndef __TestCpp__ArenaEndScene__
#define __TestCpp__ArenaEndScene__
#include "BaseScene.h"

class ArenaEndScene : public BaseScene{
public:
    static CCScene * scene();
    ArenaEndScene();
    virtual ~ArenaEndScene();
    CREATE_FUNC(ArenaEndScene);
    virtual bool init();

    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
private:
};


#endif /* defined(__TestCpp__ArenaEndScene__) */
