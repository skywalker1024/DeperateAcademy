//
//  EvoMst.cpp
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "EvoMst.h"

/*
 * コンストラクタ。
 */
EvoMst::EvoMst()
{
    m_id = 0;
    m_beforeId = 0;
    m_afterId = 0;
    m_cost = 0;
}

/*
 * デストラクタ。
 */
EvoMst::~EvoMst()
{

}

void EvoMst::initWithArray(CCDictionary * list){
    m_id = dynamic_cast<CCString*>(list->objectForKey("id"))->intValue();
    m_beforeId = dynamic_cast<CCString*>(list->objectForKey("before_id"))->intValue();
    m_afterId = dynamic_cast<CCString*>(list->objectForKey("after_id"))->intValue();
    m_cost = dynamic_cast<CCString*>(list->objectForKey("cost"))->intValue();
}


