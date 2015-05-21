//
//  Block.cpp
//  CrossKaiser
//
//  Created by 龚畅优 on 13-8-28.
//
//

#include "Block.h"
Block::Block()
:m_type(0)
,m_canRemove(false)
{}
Block::~Block(){
}
bool Block::init(){
    return true;
}
