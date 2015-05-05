//
//  DialogBaseLayer.cpp
//  CrossKaiser
//
//  Created by 龚畅优 on 13-2-28.
//
//

#include "DialogBaseLayer.h"

DialogBaseLayer::DialogBaseLayer(){}
DialogBaseLayer::~DialogBaseLayer(){}

bool DialogBaseLayer::init()
{
    CCLayer::init();
    setTouchEnabled(true);
    return true;
}
void DialogBaseLayer::onEnter()
{
    CCLayer::onEnter();
}
void DialogBaseLayer::onExit()
{
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void DialogBaseLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 10, true);
}

bool DialogBaseLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void DialogBaseLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLayer::ccTouchEnded(pTouch, pEvent);
}

void DialogBaseLayer::dismissDialog(){
    this->removeFromParent();
}