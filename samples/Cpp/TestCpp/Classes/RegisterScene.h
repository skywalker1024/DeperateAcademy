//
//  RegisterScene.h
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//

#ifndef __TestCpp__RegisterScene__
#define __TestCpp__RegisterScene__
#include "BaseScene.h"

class RegisterScene : public BaseScene{
public:
    static CCScene * scene();
    RegisterScene();
    virtual ~RegisterScene();
    CREATE_FUNC(RegisterScene);
    virtual bool init();

    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

};


#endif /* defined(__TestCpp__RegisterScene__) */
