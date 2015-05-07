//
//  Wall.h
//  CrossKaiser
//
//  Created by 龚畅优 on 13-8-28.
//
//

#ifndef __CrossKaiser__Wall__
#define __CrossKaiser__Wall__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
#include "StringLabelList.h"
class Wall :public CCObject{
public:
    Wall();
    virtual ~Wall();
    virtual bool init();
    CREATE_FUNC(Wall);
    void updateHp(int hp);
private:
    CC_SYNTHESIZE(int, m_hp, Hp);
    CC_SYNTHESIZE_RETAIN(CCSprite*, m_sprite, Sprite);
    CC_SYNTHESIZE_RETAIN(StringLabelList*, m_stringLabelList, StringLabelList);
};

#endif /* defined(__CrossKaiser__Wall__) */
