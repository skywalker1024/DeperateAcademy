//
//  Rice.cpp
//  CrossKaiser
//
//  Created by 龚畅优 on 13-8-28.
//
//

#include "Rice.h"
#include "CommonUtils.h"
const int MAX_RICE = 20;
Rice::Rice()
:m_count(0)
//,m_sprite(NULL)
,m_stringLabelList(NULL)
{}
Rice::~Rice(){
    //CC_SAFE_RELEASE_NULL(m_sprite);
    CC_SAFE_RELEASE_NULL(m_stringLabelList);
}

bool Rice::init(){
    return true;
}

bool Rice::updateCount(int count){
    m_count += count;
    if(m_count >= MAX_RICE){
        m_count = m_count % MAX_RICE;
        setCount(m_count);
        m_stringLabelList->changeString(CommonUtils::IntToString(m_count));
        return true;
    }else{
        m_stringLabelList->changeString(CommonUtils::IntToString(m_count));
        return false;
    }
}

