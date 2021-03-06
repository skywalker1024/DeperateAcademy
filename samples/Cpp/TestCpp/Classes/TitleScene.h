//
//  TitleScene.h
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//

#ifndef __TestCpp__TitleScene__
#define __TestCpp__TitleScene__
#include "BaseScene.h"

class TitleScene : public BaseScene{
public:
    static CCScene * scene();
    TitleScene();
    virtual ~TitleScene();
    CREATE_FUNC(TitleScene);
    virtual bool init();

    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

};


#endif /* defined(__TestCpp__TitleScene__) */
