//
//  Soldier.cpp
//  CrossKaiser
//
//  Created by 龚畅优 on 13-8-28.
//
//

#include "Soldier.h"

Soldier::Soldier()
:m_name("")
,m_hp(100)
,m_atk(30)
,m_moveSpeed(50)
,m_atkRange(10)
,m_armature(NULL)
,m_status(WALKING)
,m_target(NULL)
,m_atkTimer(0)
{}
Soldier::~Soldier(){}

bool Soldier::init(){
    m_atkTimer = ATK_TIMER;
    return true;
}
