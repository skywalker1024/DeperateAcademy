//
//  Soldier.h
//  CrossKaiser
//
//  Created by 龚畅优 on 13-8-28.
//
//

#ifndef __CrossKaiser__Soldier__
#define __CrossKaiser__Soldier__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
const int ATK_TIMER = 60;
class Soldier :public CCObject{
public:
    Soldier();
    virtual ~Soldier();
    virtual bool init();
    CREATE_FUNC(Soldier);
    enum status
    {
        WALKING = 1,
        ATKING = 2,
        DEAD = 3
    };
private:
    CC_SYNTHESIZE(string, m_name, Name);
    CC_SYNTHESIZE(int, m_hp, Hp);
    CC_SYNTHESIZE(int, m_atk, Atk);
    CC_SYNTHESIZE(int, m_moveSpeed, MoveSpeed);
    CC_SYNTHESIZE(int, m_atkRange, AtkRange);
    CC_SYNTHESIZE_RETAIN(CCArmature*, m_armature, Armature);
    CC_SYNTHESIZE(status, m_status, Status);
    CC_SYNTHESIZE_RETAIN(Soldier*, m_target, Target);
    CC_SYNTHESIZE(int, m_atkTimer, AtkTimer);
};

#endif /* defined(__CrossKaiser__Soldier__) */
