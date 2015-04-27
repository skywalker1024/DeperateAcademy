//
//  Battle.h
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//

#ifndef __TestCpp__Battle__
#define __TestCpp__Battle__
#include "cocos-ext.h"
#include "cocos2d.h"
USING_NS_CC;
USING_NS_CC_EXT;
#include "Block.h"
const int NUM = 8;

class Battle : public CCLayer, public CCBMemberVariableAssigner{
public:
    static CCScene * scene();
    Battle();
    virtual ~Battle();
    CREATE_FUNC(Battle);
    virtual bool init();
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher();
private:
    CCSprite *m_player1;
    CCSprite *m_player2;
    int m_matrix[NUM][NUM];
    CCArray * m_blockList;
    
};


#endif /* defined(__TestCpp__Battle__) */
