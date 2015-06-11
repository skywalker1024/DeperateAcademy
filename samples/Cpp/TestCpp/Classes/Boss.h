//
//  Boss.h
//  CrossKaiser
//
//  Created by 龚畅优 on 13-8-28.
//
//

#ifndef __CrossKaiser__Boss__
#define __CrossKaiser__Boss__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class Boss :public CCNode{
public:
    Boss();
    virtual ~Boss();
    virtual bool init();
    CREATE_FUNC(Boss);
    
    void decHp(int damage);
    void useSkillAction();
    void AttackedAction(float delayTime);
private:
    CC_SYNTHESIZE(int, m_hp, Hp);
    CC_SYNTHESIZE(int, m_maxHp, MaxHp);
    CC_SYNTHESIZE(CCProgressTimer*, m_hpBar, HpBar);
};

#endif /* defined(__CrossKaiser__Boss__) */
