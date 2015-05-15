//
//  Rice.h
//  CrossKaiser
//
//  Created by 龚畅优 on 13-8-28.
//
//

#ifndef __CrossKaiser__Rice__
#define __CrossKaiser__Rice__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
#include "StringLabelList.h"
class Rice :public CCObject{
public:
    Rice();
    virtual ~Rice();
    virtual bool init();
    CREATE_FUNC(Rice);
    bool updateCount(int count);
private:
    CC_SYNTHESIZE(int, m_count, Count);
    //CC_SYNTHESIZE_RETAIN(CCSprite*, m_sprite, Sprite);
    CC_SYNTHESIZE_RETAIN(StringLabelList*, m_stringLabelList, StringLabelList);
};

#endif /* defined(__CrossKaiser__Rice__) */
