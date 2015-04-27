//
//  Battle.cpp
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//

const int START_X = 84;
const int START_Y = 100;
const int WIDTH = 100;

#include "Battle.h"

Battle::Battle()
:m_player1(NULL)
,m_player2(NULL)
{
    m_blockList = new CCArray();
}

Battle::~Battle(){
    m_blockList->release();
}

CCScene * Battle::scene(){
    CCScene* scene = CCScene::create();
    scene->addChild(Battle::create());
    return scene;
}

bool Battle::init(){
    if (!CCLayer::init()) {
        return false;
    }
    setTouchEnabled(true);
//    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
//    CCBReader reader = CCBReader(ccNodeLoaderLibrary);
//    CCLayer *layer = (CCLayer*)reader.readNodeGraphFromFile("ccbi/battle.ccbi",this);
//    this->addChild(layer);
    
    CCSpriteBatchNode * nodeRect = NULL;
    nodeRect = CCSpriteBatchNode::create( "img/npc_tutorial.png", kDefaultSpriteBatchCapacity);
    this->addChild(nodeRect);
    //i为行 j为列
    for (int i=0; i<NUM; i++) {
        for (int j=0; j<NUM; j++) {
            Block *block = Block::create();
            block->setI(i);
            block->setJ(j);
            m_matrix[i][j] = m_blockList->count();
            m_blockList->addObject(block);
            
            
            CCSprite * rect = CCSprite::createWithTexture(nodeRect->getTexture());
            rect->setAnchorPoint(ccp(0,0));
            rect->setPosition(ccpAdd(ccp(START_X, START_Y), ccp(WIDTH * j, WIDTH * i)));
            CCLog( "%f", rect->getTexture()->getContentSize().width);
            rect->setScale( WIDTH / rect->getTexture()->getContentSize().width );
            this->addChild(rect);
            block->setSprite(rect);
        }
    }
    
    
    return true;
}

bool Battle::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_player1", CCSprite*, m_player1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_player2", CCSprite*, m_player2);
    
    CCAssert(false, "onAssignCCBMemberVariable ended without assigning any variables. Check variable name");
    return false;
}

void Battle::onEnter(){
    CCLayer::onEnter();
    //m_player1->runAction(CCSequence::create(CCMoveBy::create(.1f, ccp(20,0)), CCMoveBy::create(.1f, ccp(-35, 0)), CCMoveBy::create(.1f, ccp(25, 0)), CCMoveBy::create(.1f, ccp(-10, 0)), NULL));
}

void Battle::onExit(){
    CCLayer::onExit();
}

bool Battle::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    //判断落在哪个坑
    CCLog("x=%f y=%f",pTouch->getLocation().x, pTouch->getLocation().y);
    int j = (pTouch->getLocation().x - START_X) / WIDTH;
    int i = (pTouch->getLocation().y - START_Y) / WIDTH;
    CCLog("i=%d j=%d", i, j);
    int block_index = m_matrix[i][j];
    CCLog("block_index=%d", block_index);
    Block *block = dynamic_cast<Block*>( m_blockList->objectAtIndex(block_index) );
    CCSprite *sprite = block->getSprite();
    sprite->runAction(CCSequence::create(CCMoveBy::create(.1f, ccp(20,0)), CCMoveBy::create(.1f, ccp(-35, 0)), CCMoveBy::create(.1f, ccp(25, 0)), CCMoveBy::create(.1f, ccp(-10, 0)), NULL));
    return true;
}

void Battle::registerWithTouchDispatcher(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -122, true);
}