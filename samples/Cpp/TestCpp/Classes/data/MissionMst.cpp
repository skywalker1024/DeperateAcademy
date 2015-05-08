//
//  MissionMst.cpp
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "MissionMst.h"

/*
 * コンストラクタ。
 */
MissionMst::MissionMst()
{
    m_id = 0;
    m_name = "";
    m_actionP = 0;
    m_exp = 0;
}

/*
 * デストラクタ。
 */
MissionMst::~MissionMst()
{

}

void MissionMst::initWithArray(CCDictionary * list){
    m_id = dynamic_cast<CCString*>(list->objectForKey("id"))->intValue();
    m_exp = dynamic_cast<CCString*>(list->objectForKey("exp"))->intValue();
    m_actionP = dynamic_cast<CCString*>(list->objectForKey("action_p"))->intValue();
    m_name = dynamic_cast<CCString*>(list->objectForKey("name"))->m_sString;
}


