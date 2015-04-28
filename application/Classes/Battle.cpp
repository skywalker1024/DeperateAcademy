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
#include "CommonUtils.h"
Battle::Battle()
:m_player1(NULL)
,m_player2(NULL)
{
    m_blockList = new CCMutableArray<Block*>();
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
    if (!BaseScene::init()) {
        return false;
    }
//    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
//    CCBReader reader = CCBReader(ccNodeLoaderLibrary);
//    CCLayer *layer = (CCLayer*)reader.readNodeGraphFromFile("ccbi/battle.ccbi",this);
//    this->addChild(layer);
    //i为行 j为列
    for (int i=0; i<NUM; i++) {
        for (int j=0; j<NUM; j++) {
            int rand = arc4random() % 7;
            string key = string("block").append(CommonUtils::IntToString(rand));
            CCSpriteBatchNode *batchNode = getCacheBatchNode(key, "block");
            if ( !batchNode ) {
                string spriteName = string("img/unit_ills_thum_").append(CommonUtils::IntToString(rand)).append(".png");
                batchNode = CCSpriteBatchNode::create( spriteName.c_str(), kDefaultSpriteBatchCapacity);
                this->addChild(batchNode);
                this->setCacheBatchNode(key, "block", batchNode);
            }
            Block *block = Block::create();
            block->setI(i);
            block->setJ(j);
            block->setType(rand);
            m_matrix[i][j] = m_blockList->count();
            m_blockList->addObject(block);
            
            CCSprite * rect = CCSprite::createWithTexture(batchNode->getTexture());
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
    BaseScene::onEnter();
    //m_player1->runAction(CCSequence::create(CCMoveBy::create(.1f, ccp(20,0)), CCMoveBy::create(.1f, ccp(-35, 0)), CCMoveBy::create(.1f, ccp(25, 0)), CCMoveBy::create(.1f, ccp(-10, 0)), NULL));
}

void Battle::onExit(){
    BaseScene::onExit();
}

bool Battle::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    BaseScene::ccTouchBegan(pTouch, pEvent);
    //判断落在哪个坑
    CCLog("x=%f y=%f",pTouch->getLocation().x, pTouch->getLocation().y);
    int j = (pTouch->getLocation().x - START_X) / WIDTH;
    int i = (pTouch->getLocation().y - START_Y) / WIDTH;
    CCLog("i=%d j=%d", i, j);
    int block_index = m_matrix[i][j];
    CCLog("block_index=%d", block_index);
    Block *block = m_blockList->getObjectAtIndex(block_index);
    CCSprite *sprite = block->getSprite();
    int blockType = block->getType();
    
    CCMutableArray<Block*> * searchAry = new CCMutableArray<Block*>();
    CCMutableArray<Block*> * usedAry = new CCMutableArray<Block*>();
    searchAry->addObject(block);
    while (searchAry->count() > 0) {
        CCMutableArray<Block*> * tmpAry = new CCMutableArray<Block*>();
        CCLog("start usedAry=%d searchAry=%d tmpAry=%d", usedAry->count(), searchAry->count(), tmpAry->count());
        for (int i=0; i<searchAry->count(); i++) {
            Block * block = searchAry->getObjectAtIndex(i);
            //左
            if (block->getJ() > 0) {
                Block * tmpBlock = m_blockList->getObjectAtIndex(m_matrix[block->getI()][block->getJ() - 1]);
                if (tmpBlock->getType() == blockType){
                    if(!usedAry->containsObject(tmpBlock)){
                        tmpAry->addObject(tmpBlock);
                    }
                }
            }
            //右
            if (block->getJ() < NUM - 1) {
                Block * tmpBlock = m_blockList->getObjectAtIndex(m_matrix[block->getI()][block->getJ() + 1]);
                if ( tmpBlock->getType() == blockType){
                    if(!usedAry->containsObject(tmpBlock)){
                        tmpAry->addObject(tmpBlock);
                    }
                }
            }
            
            //下
            if (block->getI() > 0) {
                Block * tmpBlock = m_blockList->getObjectAtIndex(m_matrix[block->getI() - 1][block->getJ()]);
                if ( tmpBlock->getType() == blockType){
                    if(!usedAry->containsObject(tmpBlock)){
                        tmpAry->addObject(tmpBlock);
                    }
                }
            }
            //右
            if (block->getI() < NUM - 1) {
                Block * tmpBlock = m_blockList->getObjectAtIndex(m_matrix[block->getI() + 1][block->getJ()]);
                if ( tmpBlock->getType() == blockType){
                    if(!usedAry->containsObject(tmpBlock)){
                        tmpAry->addObject(tmpBlock);
                    }
                }
            }
        }
        usedAry->addObjectsFromArray(searchAry);
        searchAry->removeAllObjects();
        CCLog("end usedAry=%d searchAry=%d tmpAry=%d", usedAry->count(), searchAry->count(), tmpAry->count());
        searchAry->addObjectsFromArray(tmpAry);
        CCLog("end usedAry=%d searchAry=%d tmpAry=%d", usedAry->count(), searchAry->count(), tmpAry->count());
    }
    
    for (int i=0; i<usedAry->count(); i++) {
        Block *block = usedAry->getObjectAtIndex(i);
        CCSprite * sprite = block->getSprite();
        sprite->runAction(CCSequence::create(CCMoveBy::create(.1f, ccp(20,0)), CCMoveBy::create(.1f, ccp(-35, 0)), CCMoveBy::create(.1f, ccp(25, 0)), CCMoveBy::create(.1f, ccp(-10, 0)), NULL));
    }
    
    //sprite->removeFromParent();

    //sprite->runAction(CCSequence::create(CCMoveBy::create(.1f, ccp(20,0)), CCMoveBy::create(.1f, ccp(-35, 0)), CCMoveBy::create(.1f, ccp(25, 0)), CCMoveBy::create(.1f, ccp(-10, 0)), NULL));
    return true;
}