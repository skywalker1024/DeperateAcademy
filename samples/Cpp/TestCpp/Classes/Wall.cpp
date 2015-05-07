//
//  Wall.cpp
//  CrossKaiser
//
//  Created by 龚畅优 on 13-8-28.
//
//

#include "Wall.h"
#include "CommonUtils.h"
Wall::Wall()
:m_hp(0)
,m_sprite(NULL)
,m_stringLabelList(NULL)
{}
Wall::~Wall(){
    CC_SAFE_RELEASE_NULL(m_sprite);
    CC_SAFE_RELEASE_NULL(m_stringLabelList);
}

bool Wall::init(){
    return true;
}

void Wall::updateHp(int hp){
    setHp(hp);
    m_stringLabelList->changeString(CommonUtils::IntToString(hp));
}

