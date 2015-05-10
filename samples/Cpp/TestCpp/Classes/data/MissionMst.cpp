//
//  MissionMst.cpp
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "MissionMst.h"
#include "CommonUtils.h"
/*
 * コンストラクタ。
 */
MissionMst::MissionMst()
{
    m_id = 0;
    m_name = "";
    m_actionP = 0;
    m_exp = 0;
    m_posX = 0;
    m_posY = 0;
    m_minNum = 0;
    m_maxNum = 0;
    m_minTimer = 0;
    m_maxTimer = 0;
    m_soldier_id = "";
    m_mapId = 0;
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
    m_mapId = dynamic_cast<CCString*>(list->objectForKey("map_id"))->intValue();
    m_posX = dynamic_cast<CCString*>(list->objectForKey("pos_x"))->intValue();
    m_posY = dynamic_cast<CCString*>(list->objectForKey("pos_y"))->intValue();
    m_minNum = dynamic_cast<CCString*>(list->objectForKey("min_num"))->intValue();
    m_maxNum = dynamic_cast<CCString*>(list->objectForKey("max_num"))->intValue();
    m_minTimer = dynamic_cast<CCString*>(list->objectForKey("min_timer"))->intValue();
    m_maxTimer = dynamic_cast<CCString*>(list->objectForKey("max_timer"))->intValue();
    m_soldier_id = dynamic_cast<CCString*>(list->objectForKey("soldier_id"))->m_sString;
    
    vector<string>soldierList = CommonUtils::split(m_soldier_id, ",");
    for (int i=0; i<soldierList.size(); i++) {
        m_soldierMap[i] = CommonUtils::StrToInt(soldierList[i]);
    }
    
    //test
    m_minTimer = 400;
    m_maxTimer = 600;
}

std::map<int, int> MissionMst::getSoldierMap(){
    return m_soldierMap;
}
