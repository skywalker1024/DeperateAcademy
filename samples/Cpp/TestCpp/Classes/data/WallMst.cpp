//
//  WallMst.cpp
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "WallMst.h"

/*
 * コンストラクタ。
 */
WallMst::WallMst()
{
    m_lv = 0;
    m_hp = 0;
    m_cost = 0;
    m_name = "";
}

/*
 * デストラクタ。
 */
WallMst::~WallMst()
{

}

void WallMst::initWithArray(CCDictionary * list){
    m_lv = dynamic_cast<CCString*>(list->objectForKey("lv"))->intValue();
    m_hp = dynamic_cast<CCString*>(list->objectForKey("hp"))->intValue();
    m_cost = dynamic_cast<CCString*>(list->objectForKey("cost"))->intValue();
    m_name = dynamic_cast<CCString*>(list->objectForKey("name"))->m_sString;
}


