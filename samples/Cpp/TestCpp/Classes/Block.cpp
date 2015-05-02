//
//  Block.cpp
//  CrossKaiser
//
//  Created by 龚畅优 on 13-8-28.
//
//

#include "Block.h"
Block::Block()
:m_i(0)
,m_j(0)
,m_sprite(NULL)
,m_type(0)
{}
Block::~Block(){
    CC_SAFE_RELEASE_NULL(m_sprite);
}
bool Block::init(){
    return true;
}
