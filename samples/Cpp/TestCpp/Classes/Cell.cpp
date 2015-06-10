//
//  Cell.cpp
//  CrossKaiser
//
//  Created by 龚畅优 on 13-8-28.
//
//

#include "Cell.h"
Cell::Cell()
:m_type(0)
,m_canRemove(false)
,m_isLocked(false)
,m_lockSprite(NULL)
{}
Cell::~Cell(){
}
bool Cell::init(){
    return true;
}

void Cell::lockWithTexture(CCTexture2D * texture){
    if (!m_isLocked) {
        m_isLocked = true;
        m_lockSprite = CCSprite::create();
        m_lockSprite->initWithTexture(texture);
        m_lockSprite->setAnchorPoint(CCPointZero);
        m_lockSprite->setPosition(CCPointZero);
        m_lockSprite->setScale(100 / texture->getContentSize().width);
        this->addChild(m_lockSprite);
    }
}

void Cell::unlock(){
    m_isLocked = false;
    m_lockSprite->removeFromParent();
}