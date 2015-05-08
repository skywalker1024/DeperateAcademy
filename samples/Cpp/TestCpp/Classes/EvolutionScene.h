//
//  EvolutionScene.h
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//

#ifndef __TestCpp__EvolutionScene__
#define __TestCpp__EvolutionScene__
#include "BaseScene.h"

class EvolutionScene : public BaseScene{
public:
    static CCScene * scene();
    EvolutionScene();
    virtual ~EvolutionScene();
    CREATE_FUNC(EvolutionScene);
    virtual bool init();

    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
private:
    void onEvoClick(CCObject * sender, CCControlEvent controlEvent);
    void goToShop();
    void goToMission();
protected:
    virtual void onBackClick();
};


#endif /* defined(__TestCpp__EvolutionScene__) */
