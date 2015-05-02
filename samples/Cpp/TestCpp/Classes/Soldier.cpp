//
//  Soldier.cpp
//  CrossKaiser
//
//  Created by 龚畅优 on 13-8-28.
//
//

#include "Soldier.h"
#include "SoldierMstList.h"
Soldier::Soldier()
:m_name("")
,m_hp(0)
,m_atk(0)
,m_moveSpeed(0)
,m_atkRange(0)
,m_armature(NULL)
,m_status(WALKING)
,m_target(NULL)
,m_atkTimer(0)
{}
Soldier::~Soldier(){
    CC_SAFE_RELEASE_NULL(m_armature);
    CC_SAFE_RELEASE_NULL(m_target);
}

bool Soldier::init(){
    m_atkTimer = ATK_TIMER;
    return true;
}

void Soldier::initWithSoldierId(int soldierId){
    SoldierMst * soldierMst = SoldierMstList::shared()->getObject(soldierId);
    m_name = soldierMst->getName();
    m_hp = soldierMst->getHp();
    m_atk = soldierMst->getAtk();
    m_moveSpeed = soldierMst->getMoveSpeed();
    m_atkRange = soldierMst->getAtkRange();
}
