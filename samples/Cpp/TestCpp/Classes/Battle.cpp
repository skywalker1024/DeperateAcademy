//
//  Battle.cpp
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//

#include "Battle.h"
#include "CommonUtils.h"
#include "SoldierMstList.h"
const int START_Y = 100;
const int WIDTH = 100;
const int ARMY_POSITION_Y = START_Y + NUM * WIDTH + 200;
Battle::Battle()
{
    m_blockList = new CCMutableDictionary<int, Block*>();
    m_myArmy = new CCMutableArray<Soldier*>();
    m_enemyArmy = new CCMutableArray<Soldier*>();
    MATRIX_START_X = (CommonUtils::getScreenWidth() - NUM * WIDTH) / 2;
    MY_ARMY_START_X = MATRIX_START_X;
    ENEMY_ARMY_START_X = MATRIX_START_X + NUM * WIDTH;
}

Battle::~Battle(){
    m_blockList->removeAllObjects();
    m_blockList->release();
    m_myArmy->removeAllObjects();
    m_myArmy->release();
    m_enemyArmy->removeAllObjects();
    m_enemyArmy->release();
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
    
    CCLog("height=%f width=%f", CCDirector::sharedDirector()->getWinSize().height, CCDirector::sharedDirector()->getWinSize().width );
   
//    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
//    CCBReader reader = CCBReader(ccNodeLoaderLibrary);
//    CCLayer *layer = (CCLayer*)reader.readNodeGraphFromFile("ccbi/battle.ccbi",this);
//    this->addChild(layer);
    //i为行 j为列
    for (int i=0; i<NUM; i++) {
        for (int j=0; j<NUM; j++) {
            createBlock(i, j);
        }
    }
    
    SoldierMstList::shared();
    
    return true;
}

bool Battle::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
    CCAssert(false, "onAssignCCBMemberVariable ended without assigning any variables. Check variable name");
    return false;
}

void Battle::onEnter(){
    BaseScene::onEnter();
    
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("ccs-res/armature/knight.png", "ccs-res/armature/knight.plist", "ccs-res/armature/knight.xml", this, NULL);
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("ccs-res/armature/weapon.png", "ccs-res/armature/weapon.plist", "ccs-res/armature/weapon.xml", this, NULL);
}

void Battle::onExit(){
    BaseScene::onExit();
}

bool Battle::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    BaseScene::ccTouchBegan(pTouch, pEvent);
    CCRect touchArea =  CCRect(MATRIX_START_X, START_Y, WIDTH * NUM, WIDTH * NUM);
    if (!touchArea.containsPoint(pTouch->getLocation())) {
        return false;
    }
    //判断落在哪个坑
    CCLog("x=%f y=%f",pTouch->getLocation().x, pTouch->getLocation().y);
    int j = (pTouch->getLocation().x - MATRIX_START_X) / WIDTH;
    int i = (pTouch->getLocation().y - START_Y) / WIDTH;
    CCLog("i=%d j=%d", i, j);
    int block_index = m_matrix[i][j];
    CCLog("block_index=%d", block_index);
    Block *block = m_blockList->objectForKey(block_index);
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
                Block * tmpBlock = m_blockList->objectForKey(m_matrix[block->getI()][block->getJ() - 1]);
                if (tmpBlock->getType() == blockType){
                    if(!usedAry->containsObject(tmpBlock)){
                        tmpAry->addObject(tmpBlock);
                    }
                }
            }
            //右
            if (block->getJ() < NUM - 1) {
                Block * tmpBlock = m_blockList->objectForKey(m_matrix[block->getI()][block->getJ() + 1]);
                if ( tmpBlock->getType() == blockType){
                    if(!usedAry->containsObject(tmpBlock)){
                        tmpAry->addObject(tmpBlock);
                    }
                }
            }
            
            //下
            if (block->getI() > 0) {
                Block * tmpBlock = m_blockList->objectForKey(m_matrix[block->getI() - 1][block->getJ()]);
                if ( tmpBlock->getType() == blockType){
                    if(!usedAry->containsObject(tmpBlock)){
                        tmpAry->addObject(tmpBlock);
                    }
                }
            }
            //右
            if (block->getI() < NUM - 1) {
                Block * tmpBlock = m_blockList->objectForKey(m_matrix[block->getI() + 1][block->getJ()]);
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
    
    if (usedAry->count() < 3) {
        for (int i=0; i<usedAry->count(); i++) {
            Block *block = usedAry->getObjectAtIndex(i);
            block->getSprite()->runAction(CCSequence::create(CCMoveBy::create(.1f, ccp(20,0)), CCMoveBy::create(.1f, ccp(-35, 0)), CCMoveBy::create(.1f, ccp(25, 0)), CCMoveBy::create(.1f, ccp(-10, 0)), NULL));
        }
        createSoldier(1, m_enemyArmy, false);
        return false;
    }
    
    map<int, int> column_list;
    //清空点击的block,并且更新数组 CCMutableArray<Block*> * m_blockList;
    for (int i=0; i<usedAry->count(); i++) {
        Block *block = usedAry->getObjectAtIndex(i);
        int tmp_i = block->getI();
        int tmp_j = block->getJ();
        CCLog("j=%d i=%d", block->getJ(), block->getI());
        
        //判断是否存在这列
        bool in_column_list = false;
        for (int column_key=0; column_key<column_list.size(); column_key++) {
            CCLog("column=%d",column_list[column_key]);
            if (column_list[column_key] == tmp_j) {
                in_column_list = true;
                break;
            }
        }
        if (!in_column_list) {
            column_list[column_list.size()] = tmp_j;
        }
        m_matrix[tmp_i][tmp_j] = -1;
        CCSprite * sprite = block->getSprite();
        sprite->removeFromParent();
        //sprite->runAction(CCSequence::create(CCMoveBy::create(.1f, ccp(20,0)), CCMoveBy::create(.1f, ccp(-35, 0)), CCMoveBy::create(.1f, ccp(25, 0)), CCMoveBy::create(.1f, ccp(-10, 0)), NULL));
    }
    //新增小兵的依据，消3个出来一个还是消3个出来3个
    if (usedAry->count() > 0) {
        //新增小兵
        createSoldier(block->getType(), m_myArmy, true);
        
        createSoldier(1, m_enemyArmy, false);
    }
    
    map<int, int> blank_list;
    for (int i=0; i<column_list.size(); i++) {
        int blank_count = 0;
        int tmp_j = column_list[i];
        for (int ii=0; ii<NUM; ii++) {
            int index = m_matrix[ii][tmp_j];
            if (index == -1) {
                blank_count++;
            }else{
                if (blank_count > 0) {
                    Block *block = m_blockList->objectForKey(index);
                    //需要往下挪blank_count个格子
                    int index_target = index - blank_count * NUM;
                    CCLog("index=%d index_target=%d blank_count=%d",index,index_target,blank_count);
                    block->setI(block->getI() - blank_count);
                    m_blockList->removeObjectForKey(index_target);
                    m_blockList->setObject(block, index_target);
                    
                    block->getSprite()->runAction(CCMoveBy::create(0.1f * blank_count, ccp(0,-WIDTH * blank_count)));
                }
            }
        }
        blank_list[i] = blank_count;
    }
    
    //将m_blockList补齐
    for (int i=0; i<column_list.size(); i++) {
        int tmp_j = column_list[i];
        int start_ii = NUM - blank_list[i];
        for (int ii=start_ii; ii<NUM; ii++) {
            createBlock(ii, tmp_j);
            //重置位置并runaction
            CCSprite * blockSprite = m_blockList->objectForKey(m_matrix[ii][tmp_j])->getSprite();
            blockSprite->setPosition(ccp(MATRIX_START_X + tmp_j * WIDTH, START_Y + NUM * WIDTH + (ii - start_ii) * WIDTH));
            blockSprite->runAction(CCMoveBy::create(0.1f * blank_list[i], ccp(0,-WIDTH * blank_list[i])));
        }
    }
    //补齐matrix
    for (int i=0; i<NUM; i++) {
        for (int j=0; j<NUM; j++) {
            if (m_matrix[i][j] == -1) {
                m_matrix[i][j] = i * NUM + j;
            }
        }
    }

    return true;
}

void Battle::createSoldier(int kind, CCMutableArray<Soldier*>* army, bool myArmy){
    cocos2d::extension::CCArmature *armature = NULL;
    armature = new cocos2d::extension::CCArmature();
    armature->init("Knight_f/Knight");
    armature->getAnimation()->playWithIndex(1);
    
    std::string weapon[] = {"weapon_f-sword.png", "weapon_f-sword2.png", "weapon_f-sword3.png", "weapon_f-sword4.png", "weapon_f-sword5.png", "weapon_f-knife.png", "weapon_f-hammer.png"};
    
    CCSkin *skin = CCSkin::createWithSpriteFrameName(weapon[kind].c_str());
    armature->getBone("weapon")->addDisplay(skin, 0);
    
    armature->getBone("weapon")->changeDisplayWithIndex(0, true);
    
    addChild(armature);
    armature->release();
    if (myArmy) {
        armature->setScale(1.2f);
        armature->setPosition(ccp(MY_ARMY_START_X, ARMY_POSITION_Y));
    }else{
        armature->setScaleX(-1.2f);
        armature->setPosition(ccp(ENEMY_ARMY_START_X, ARMY_POSITION_Y));
    }
    
    
    Soldier * soldier = Soldier::create();
    soldier->initWithSoldierId(101 + kind * 100);
    soldier->setArmature(armature);
    army->addObject(soldier);
}

void Battle::createBlock(int i , int j){
    int rand = arc4random() % 4;
    string key = string("block").append(CommonUtils::IntToString(rand));
    CCSpriteBatchNode *batchNode = getCacheBatchNode(key, "block");
    if ( !batchNode ) {
        string spriteName = string("img/bubble_").append(CommonUtils::IntToString(rand)).append(".png");
        batchNode = CCSpriteBatchNode::create( spriteName.c_str(), kDefaultSpriteBatchCapacity);
        this->addChild(batchNode);
        this->setCacheBatchNode(key, "block", batchNode);
    }
    Block *block = Block::create();
    block->setI(i);
    block->setJ(j);
    block->setType(rand);
    m_matrix[i][j] = i * NUM + j;
    m_blockList->removeObjectForKey(m_matrix[i][j]);
    m_blockList->setObject(block, m_matrix[i][j]);
    
    CCSprite * rect = CCSprite::createWithTexture(batchNode->getTexture());
    rect->setAnchorPoint(ccp(0,0));
    rect->setPosition(ccpAdd(ccp(MATRIX_START_X, START_Y), ccp(WIDTH * j, WIDTH * i)));
    CCLog( "%f", rect->getTexture()->getContentSize().width);
    rect->setScale( WIDTH / rect->getTexture()->getContentSize().width );
    this->addChild(rect);
    block->setSprite(rect);
}

void Battle::draw(){
    updateArmy(m_myArmy, m_enemyArmy, true);
    updateArmy(m_enemyArmy, m_myArmy, false);
}

void Battle::updateArmy(CCMutableArray<Soldier*>* atkArmy, CCMutableArray<Soldier*>* defArmy, bool myArmy){
    for (int i=0; i<atkArmy->count(); i++) {
        Soldier * soldier = atkArmy->getObjectAtIndex(i);
        if (soldier->getHp()<=0) {
            soldier->setStatus(Soldier::DEAD);
        }
        if (soldier->getStatus() == Soldier::DEAD) {
            CCLog("soldier die");
            soldier->getArmature()->removeFromParent();
            atkArmy->removeObject(soldier);
        }else if (soldier->getStatus() == Soldier::WALKING) {
            float mvDistance;
            if (myArmy) {
                mvDistance = soldier->getMoveSpeed() / 100.f;
            }else{
                mvDistance = -soldier->getMoveSpeed() / 100.f;
            }
            soldier->getArmature()->setPositionX(soldier->getArmature()->getPositionX() + mvDistance);
            
            //判断是否到了敌方面前
            for(int j=0; j<defArmy->count(); j++){
                Soldier * enemy = defArmy->getObjectAtIndex(j);
                if (enemy->getStatus() != Soldier::DEAD && fabs(enemy->getArmature()->getPositionX() - soldier->getArmature()->getPositionX())<soldier->getAtkRange()) {
                    soldier->setStatus(Soldier::ATKING);
                    soldier->setTarget(enemy);
                    soldier->getArmature()->getAnimation()->playWithIndex(0);
                }
            }
        }else if (soldier->getStatus() == Soldier::ATKING){
            if (soldier->getAtkTimer() > 0) {//攻击倒计时
                soldier->setAtkTimer(soldier->getAtkTimer() - 1);
            }else{//攻击
                Soldier * enemy = soldier->getTarget();
                enemy->setHp(enemy->getHp() - soldier->getAtk());
                //重置倒计时
                soldier->setAtkTimer(ATK_TIMER);
            }
            Soldier * enemy = soldier->getTarget();
            if (enemy->getHp()<=0) {
                soldier->setStatus(Soldier::WALKING);
                soldier->getArmature()->getAnimation()->playWithIndex(1);
            }
        }
    }
}