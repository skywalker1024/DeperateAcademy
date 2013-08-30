//
//  Poker.cpp
//  CrossKaiser
//
//  Created by 龚畅优 on 13-8-28.
//
//

#include "Poker.h"
Poker::Poker()
:m_number(NULL)
{}
Poker::~Poker(){}

bool Poker::init(){
    if (CCLayer::init()) {
        CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
        CCBReader reader = CCBReader(ccNodeLoaderLibrary);
        Poker *poker = (Poker*)reader.readNodeGraphFromFile("ccbi/poker.ccbi",this);
        this->addChild(poker);
        return true;
    }
    return false;
}

bool Poker::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_number", CCLabelTTF*, m_number);
    CCAssert(false, "onAssignCCBMemberVariable ended without assigning any variables. Check variable name");
    return false;
}

void Poker::onEnter(){
    CCLayer::onEnter();
    m_number->setString("10");
}