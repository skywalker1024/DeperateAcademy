//
//  Block.h
//  CrossKaiser
//
//  Created by 龚畅优 on 13-8-28.
//
//

#ifndef __CrossKaiser__Block__
#define __CrossKaiser__Block__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class Block :public CCSprite{
public:
    Block();
    virtual ~Block();
    virtual bool init();
    CREATE_FUNC(Block);
    
private:
    CC_SYNTHESIZE(int, m_type, Type);
    CC_SYNTHESIZE(bool, m_canRemove, CanRemove);
};

#endif /* defined(__CrossKaiser__Block__) */
