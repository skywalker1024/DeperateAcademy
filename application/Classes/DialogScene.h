//
//  DialogScene.h
//  TestCpp
//
//  Created by 龚畅优 on 13-9-16.
//
//

#ifndef __TestCpp__DialogScene__
#define __TestCpp__DialogScene__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class DialogScene : public CCLayer, public CCBMemberVariableAssigner{
public:
    DialogScene();
    virtual ~DialogScene();
    static CCScene* scene();
    virtual bool init();
    virtual void onEnter();
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
    CREATE_FUNC(DialogScene);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher();
    void npcAction();
    void showDialog();
private:
    CCLabelTTF *m_dialog;
    CCSprite *m_leftNPC;
    CCSprite *m_rightNPC;
};
#endif /* defined(__TestCpp__DialogScene__) */
