//
//  LevelMst.cpp
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "LevelMst.h"

/*
 * コンストラクタ。
 */
LevelMst::LevelMst()
{
    m_lv = 0;
    m_exp = 0;
    m_actionP = 0;
    unlock_soldier_id = 0;
}

/*
 * デストラクタ。
 */
LevelMst::~LevelMst()
{

}

void LevelMst::initWithArray(CCDictionary * list){
    m_lv = dynamic_cast<CCString*>(list->objectForKey("lv"))->intValue();
    m_exp = dynamic_cast<CCString*>(list->objectForKey("exp"))->intValue();
    m_actionP = dynamic_cast<CCString*>(list->objectForKey("action_p"))->intValue();
    unlock_soldier_id = dynamic_cast<CCString*>(list->objectForKey("unlock_soldier_id"))->intValue();
}


