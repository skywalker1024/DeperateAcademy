//
//  SoldierMst.cpp
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "SoldierMst.h"

/*
 * コンストラクタ。
 */
SoldierMst::SoldierMst()
{
    m_id = 0;
    m_name = "";
    m_series = 0;
    m_hp = 0;
    m_atk = 0;
    m_moveSpeed = 0;
    m_atkRange = 0;
}

/*
 * デストラクタ。
 */
SoldierMst::~SoldierMst()
{

}

void SoldierMst::initWithArray(CCDictionary * list){
    m_id = dynamic_cast<CCString*>(list->objectForKey("id"))->intValue();
    m_name = dynamic_cast<CCString*>(list->objectForKey("name"))->m_sString;
    m_series = dynamic_cast<CCString*>(list->objectForKey("series"))->intValue();
    m_hp = dynamic_cast<CCString*>(list->objectForKey("hp"))->intValue();
    m_atk = dynamic_cast<CCString*>(list->objectForKey("atk"))->intValue();
    m_moveSpeed = dynamic_cast<CCString*>(list->objectForKey("move_speed"))->intValue();
    m_atkRange = dynamic_cast<CCString*>(list->objectForKey("atk_range"))->intValue();
}


