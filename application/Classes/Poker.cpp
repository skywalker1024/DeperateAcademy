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
,m_bg(NULL)
{}
Poker::~Poker(){}

bool Poker::init(){
    if (CCLayer::init()) {
        CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
        CCBReader reader = CCBReader(ccNodeLoaderLibrary);
        Poker *poker = (Poker*)reader.readNodeGraphFromFile("ccbi/poker.ccbi",this);
        this->addChild(poker);
        this->setTouchEnabled(true);
        return true;
    }
    return false;
}

bool Poker::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_number", CCLabelTTF*, m_number);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_bg", CCSprite*, m_bg);
    
    CCAssert(false, "onAssignCCBMemberVariable ended without assigning any variables. Check variable name");
    return false;
}

void Poker::onEnter(){
    CCLayer::onEnter();
    m_number->setString("10");
    m_bg->setTexture(CCTextureCache::sharedTextureCache()->addImage("Icon-57.png"));
}

bool Poker::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    return true;
}
void Poker::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    CCLayer::ccTouchEnded(pTouch, pEvent);
    this->setPosition(ccp(this->getPositionX(), this->getPositionY() + 20));
  CCLog("touch end");
}

void Poker::registerWithTouchDispatcher(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -122, true);
}