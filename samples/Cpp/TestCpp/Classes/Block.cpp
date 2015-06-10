//
//  Block.cpp
//  CrossKaiser
//
//  Created by 龚畅优 on 13-8-28.
//
//

#include "Block.h"
#include "CommonUtils.h"
#include "BaseScene.h"

const int ZORDER = -1;

Block::Block()
:m_type(0)
,m_callScene(NULL)
{}
Block::~Block(){
}
bool Block::init(){
    return true;
}

Block * Block::create(int type, BaseScene * callScene, CCPoint pos){
    Block *block = Block::create();
    block->setType(type);
    block->setCallScene(callScene);
    block->changeSprite();
    
    block->setPosition(pos);
    //callScene->addChild(block, ZORDER);
    return block;
}

void Block::decType(){
    m_type--;
    changeSprite();
}

string Block::getSpriteName(){
    string spriteName = "img/";
    switch (m_type) {
        case 3:
            spriteName.append( "wall_blue.png" );
            break;
        case 2:
            spriteName.append( "wall_red.png" );
            break;
        case 1:
            spriteName.append( "wall_yellow.png" );
            break;
        default:
            break;
    }
    return spriteName;
}

void Block::changeSprite(){
    if (m_type > 0) {
        string key = string("block").append(CommonUtils::IntToString(m_type));
        CCSpriteBatchNode *batchNode = m_callScene->getCacheBatchNode(key, "block");
        if ( !batchNode ) {
            string spriteName = getSpriteName();
            batchNode = CCSpriteBatchNode::create( spriteName.c_str(), kDefaultSpriteBatchCapacity);
            m_callScene->addChild(batchNode, ZORDER);
            m_callScene->setCacheBatchNode(key, "block", batchNode);
        }
        //CCPoint tmpPos = this->getPosition();
        this->initWithTexture(batchNode->getTexture());
        this->setAnchorPoint(CCPointZero);
        
        this->retain();
        this->removeFromParent();
        m_callScene->addChild(this, ZORDER);
        this->release();
    }else{
        this->removeFromParent();
    }
}