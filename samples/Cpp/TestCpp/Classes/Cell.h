//
//  Cell.h
//  CrossKaiser
//
//  Created by 龚畅优 on 13-8-28.
//
//

#ifndef __CrossKaiser__Cell__
#define __CrossKaiser__Cell__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class Cell :public CCSprite{
public:
    Cell();
    virtual ~Cell();
    virtual bool init();
    CREATE_FUNC(Cell);
    
    void lockWithTexture(CCTexture2D * texture);
    void unlock();
private:
    CC_SYNTHESIZE(int, m_type, Type);
    CC_SYNTHESIZE(bool, m_canRemove, CanRemove);
    CC_SYNTHESIZE(bool, m_isLocked, IsLocked);
    CC_SYNTHESIZE(CCSprite*, m_lockSprite, LockSprite);
};

#endif /* defined(__CrossKaiser__Cell__) */
