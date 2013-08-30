//
//  Poker.h
//  CrossKaiser
//
//  Created by 龚畅优 on 13-8-28.
//
//

#ifndef __CrossKaiser__Poker__
#define __CrossKaiser__Poker__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class Poker : public CCLayer, public CCBMemberVariableAssigner{
public:
    Poker();
    virtual ~Poker();
    virtual bool init();
    virtual void onEnter();
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
    CREATE_FUNC(Poker);
private:
    CCLabelTTF *m_number;
};

#endif /* defined(__CrossKaiser__Poker__) */
