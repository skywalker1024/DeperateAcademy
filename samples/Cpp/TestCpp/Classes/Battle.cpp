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
#include "MissionInfo.h"
#include "UserInfo.h"
#include "MapScene.h"
#include "MissionEndScene.h"
#include "ArenaEndScene.h"
#include "WallMstList.h"
const int START_Y = 100;
const int WIDTH = 100;
const int ARMY_POSITION_Y = START_Y + NUM * WIDTH + 200;
const int BLOCK_GREY_TYPE = 5;//Grey的serie id是5
Battle::Battle()
{
    m_blockList = new CCMutableDictionary<int, Block*>();
    m_myArmy = new CCMutableArray<Soldier*>();
    m_enemyArmy = new CCMutableArray<Soldier*>();
    MATRIX_START_X = (CommonUtils::getScreenWidth() - NUM * WIDTH) / 2;
    MY_ARMY_START_X = MATRIX_START_X;
    ENEMY_ARMY_START_X = MATRIX_START_X + NUM * WIDTH;
    m_myWall = NULL;
    m_enemyWall = NULL;
    m_missionMst = NULL;
    m_checkBlock = true;
    m_isOver = false;
    m_riceList = new CCMutableDictionary<int, Rice*>();
}

Battle::~Battle(){
    m_blockList->removeAllObjects();
    m_blockList->release();
    m_myArmy->removeAllObjects();
    m_myArmy->release();
    m_enemyArmy->removeAllObjects();
    m_enemyArmy->release();
    CC_SAFE_RELEASE_NULL(m_myWall);
    CC_SAFE_RELEASE_NULL(m_enemyWall);
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
    if (MissionInfo::shared()->getIsArena()) {
        int arena_id = MissionInfo::shared()->getCurrentArenaId();
        m_arenaInfo = ArenaInfoList::shared()->getObject(arena_id);
        m_enemyTimer = CommonUtils::getRandom(m_arenaInfo->getMinTimer(), m_arenaInfo->getMaxTimer());
    }else{
        int mission_id = MissionInfo::shared()->getCurrentMissionId();
        m_missionMst = MissionMstList::shared()->getObject(mission_id);
        m_enemyTimer = CommonUtils::getRandom(m_missionMst->getMinTimer(), m_missionMst->getMaxTimer());
    }
    
    CCLog("height=%f width=%f", CCDirector::sharedDirector()->getWinSize().height, CCDirector::sharedDirector()->getWinSize().width );
   
    createBlocks();
    //创建rice
    int screenWidth = CommonUtils::getScreenWidth();
    int rice_start_x = (screenWidth - (4 * 100 + 3*100)) / 2;
    int count = MIN(4,UserInfo::shared()->m_soldierMap.size());
    for (int i=0; i<count; i++) {
        Rice *rice = Rice::create();
        StringLabelList * stringLabel = GraphicUtils::drawString(this, "0", rice_start_x + 200*i, 200, getSystemColor(COLOR_KEY_GOLD), TEXT_ALIGN_LEFT_BOTTOM, 60);
        rice->setStringLabelList(stringLabel);
        m_riceList->setObject(rice, i+1);
    }
    
    SoldierMstList::shared();
    
    setMyWall(Wall::create());
    CCSprite * myWallSprite = CCSprite::create("img/wall_red.png");
    myWallSprite->setPosition(ccp(MY_ARMY_START_X, ARMY_POSITION_Y));
    addChild(myWallSprite);
    WallMst * wallMst = WallMstList::shared()->getObject(UserInfo::shared()->getWallLv());
    m_myWall->setHp(wallMst->getHp());
    StringLabelList *myWallHpString = GraphicUtils::drawString(this, CommonUtils::IntToString( m_myWall->getHp() ), MY_ARMY_START_X, ARMY_POSITION_Y + 300, getSystemColor(COLOR_KEY_HP), TEXT_ALIGN_CENTER_MIDDLE, 60);
    m_myWall->setStringLabelList(myWallHpString);
    
    setEnemyWall( Wall::create() );
    CCSprite * enemyWallSprite = CCSprite::create("img/wall_red.png");
    enemyWallSprite->setPosition(ccp(ENEMY_ARMY_START_X, ARMY_POSITION_Y));
    addChild(enemyWallSprite);
    if (MissionInfo::shared()->getIsArena()) {
        WallMst *wallMst = WallMstList::shared()->getObject(m_arenaInfo->getWallLv());
        m_enemyWall->setHp(wallMst->getHp());
    }else{
        m_enemyWall->setHp(m_missionMst->getHp());
    }
    StringLabelList *enemyWallHpString = GraphicUtils::drawString(this, CommonUtils::IntToString( m_enemyWall->getHp() ), ENEMY_ARMY_START_X, ARMY_POSITION_Y + 300, getSystemColor(COLOR_KEY_HP), TEXT_ALIGN_CENTER_MIDDLE, 60);
    m_enemyWall->setStringLabelList(enemyWallHpString);
    
    
    
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
        
        //如果点错，对面出来一堆兵,
        createEnemy();
        return false;
    }
    
    m_checkBlock = false;
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
        if (block->getType() != BLOCK_GREY_TYPE) {
            int soldierId = UserInfo::shared()->m_soldierMap[block->getType()];
            if(m_riceList->objectForKey(block->getType())->updateCount(usedAry->count())){
                createSoldier(soldierId, m_myArmy, true, 0);
            }
        }
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
    float checkDelayTime = 0.f;
    for (int i=0; i<column_list.size(); i++) {
        float actionTime = 0.1f * blank_list[i];
        int tmp_j = column_list[i];
        int start_ii = NUM - blank_list[i];
        for (int ii=start_ii; ii<NUM; ii++) {
            createBlock(ii, tmp_j);
            //重置位置并runaction
            CCSprite * blockSprite = m_blockList->objectForKey(m_matrix[ii][tmp_j])->getSprite();
            blockSprite->setPosition(ccp(MATRIX_START_X + tmp_j * WIDTH, START_Y + NUM * WIDTH + (ii - start_ii) * WIDTH));
            blockSprite->runAction(CCMoveBy::create(actionTime, ccp(0,-WIDTH * blank_list[i])));
        }
        if(actionTime > checkDelayTime){
            checkDelayTime = actionTime;
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
    
    this->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(checkDelayTime), CCCallFunc::create(this, callfunc_selector(Battle::setCheckBlock))));
    
    return true;
}

void Battle::createSoldier(int soldierId, CCMutableArray<Soldier*>* army, bool myArmy, int offsetX){
    cocos2d::extension::CCArmature *armature = NULL;
    armature = new cocos2d::extension::CCArmature();
    armature->init("Knight_f/Knight");//soldierId / 100来区分兵种
    armature->getAnimation()->playWithIndex(1);
    
    std::string weapon[] = {"weapon_f-sword.png", "weapon_f-sword2.png", "weapon_f-sword3.png", "weapon_f-sword4.png", "weapon_f-sword5.png", "weapon_f-knife.png", "weapon_f-hammer.png"};
    int kind = soldierId % 100;
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
        armature->setPosition(ccp(ENEMY_ARMY_START_X + offsetX, ARMY_POSITION_Y));
    }
    
    
    Soldier * soldier = Soldier::create();
    soldier->initWithSoldierId(101 + kind * 100);
    soldier->setArmature(armature);
    army->addObject(soldier);
}

void Battle::createBlock(int i , int j){
    int blockTypes = 4;
    int rand = 0;
    if ( UserInfo::shared()->m_soldierMap.size() < 4) {
        blockTypes = UserInfo::shared()->m_soldierMap.size() + 1;
        rand = arc4random() % blockTypes;
        if (rand >= UserInfo::shared()->m_soldierMap.size()) {
            rand = BLOCK_GREY_TYPE - 1;
        }
    }else{
        rand = arc4random() % blockTypes;
    }
    CCLog("blockTypes=%d", rand);
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
    block->setType(rand + 1);//type是serie id
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
    if (m_isOver) {
        return;
    }
    if (m_checkBlock) {
        if(checkBlock() == -1){
            CCLog("no block can touch");
            createBlocks();
        }
    }
    
    if (m_enemyTimer > 0) {
        m_enemyTimer--;
    }else{
        createEnemy();
        if (MissionInfo::shared()->getIsArena()) {
            m_enemyTimer = CommonUtils::getRandom(m_arenaInfo->getMinTimer(), m_arenaInfo->getMaxTimer());
        }else{
            m_enemyTimer = CommonUtils::getRandom(m_missionMst->getMinTimer(), m_missionMst->getMaxTimer());
        }
    }
    
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
        }else if (soldier->getStatus() == Soldier::WALKING || soldier->getStatus() == Soldier::ATKING_WALL) {
            if (soldier->getStatus() == Soldier::WALKING) {
                float mvDistance;
                if (myArmy) {
                    mvDistance = soldier->getMoveSpeed() / 100.f;
                }else{
                    mvDistance = -soldier->getMoveSpeed() / 100.f;
                }
                soldier->getArmature()->setPositionX(soldier->getArmature()->getPositionX() + mvDistance);
            }
            
            if (soldier->getStatus() == Soldier::ATKING_WALL) {
                if (soldier->getAtkTimer() > 0) {//攻击倒计时
                    soldier->setAtkTimer(soldier->getAtkTimer() - 1);
                }else{//攻击
                    if (myArmy) {
                        m_enemyWall->updateHp(m_enemyWall->getHp() - soldier->getAtk());
                        if (m_enemyWall->getHp() <= 0) {
                            CCLog("you win");
                            
                            GraphicUtils::drawString(this, "you win!", CommonUtils::getScreenWidth() / 2, CommonUtils::getScreenHeight() - 300, getSystemColor(COLOR_KEY_RED), TEXT_ALIGN_CENTER_MIDDLE, 60);
                            m_isOver = true;
                            changeNextScene(true);
                            break;
                        }
                    }else{
                        m_myWall->updateHp(m_myWall->getHp() - soldier->getAtk());
                        if (m_myWall->getHp() <= 0) {
                            CCLog("you lose");
                            GraphicUtils::drawString(this, "you lose", CommonUtils::getScreenWidth() / 2, CommonUtils::getScreenHeight() - 300, getSystemColor(COLOR_KEY_RED), TEXT_ALIGN_CENTER_MIDDLE, 60);
                            string postData = CCString::createWithFormat("mission_id=%d&is_win=%d", MissionInfo::shared()->getCurrentMissionId(), 0)->m_sString;
                            m_isOver = true;
                            changeNextScene(false);
                            break;
                        }
                    }
                    //重置倒计时
                    soldier->setAtkTimer(ATK_TIMER);
                }
            }

            //判断是否到了敌方面前
            for(int j=0; j<defArmy->count(); j++){
                Soldier * enemy = defArmy->getObjectAtIndex(j);
                if (enemy->getStatus() != Soldier::DEAD && fabs(enemy->getArmature()->getPositionX() - soldier->getArmature()->getPositionX())<soldier->getAtkRange()) {
                    soldier->setAtkTimer(ATK_TIMER);
                    soldier->setStatus(Soldier::ATKING);
                    soldier->setTarget(enemy);
                    soldier->getArmature()->getAnimation()->playWithIndex(0);
                    break;
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
        
        //攻打城墙
        if(myArmy && soldier->getStatus() == Soldier::WALKING && fabs(ENEMY_ARMY_START_X - soldier->getArmature()->getPositionX())<soldier->getAtkRange()){
            soldier->setStatus(Soldier::ATKING_WALL);
        }
        
        if(!myArmy && soldier->getStatus() == Soldier::WALKING && fabs(MY_ARMY_START_X - soldier->getArmature()->getPositionX())<soldier->getAtkRange()){
            soldier->setStatus(Soldier::ATKING_WALL);
        }
    }
}

void Battle::createEnemy(){
    int minNum = 0;
    int maxNum = 0;
    std::map<int, int>soldierMap;
    if (MissionInfo::shared()->getIsArena()) {
        minNum = m_arenaInfo->getMinNum();
        maxNum = m_arenaInfo->getMaxNum();
        
        vector<string>soldierList = CommonUtils::split(m_arenaInfo->getSoldier(), ",");
        for (int i=0; i<soldierList.size(); i++) {
            soldierMap[i] = CommonUtils::StrToInt(soldierList[i]);
        }
    }else{
        minNum = m_missionMst->getMinNum();
        maxNum = m_missionMst->getMaxNum();
        soldierMap = m_missionMst->getSoldierMap();
    }
    int soldierNum = CommonUtils::getRandom(minNum, maxNum);
    
    int leftNum = soldierNum;
    for (int i=0; i<soldierMap.size(); i++) {
        int soldierNum = 0;
        if (i == soldierMap.size() - 1) {
            soldierNum = leftNum;
        }else{
            soldierNum = CommonUtils::getRandom(0, leftNum);
        }
        int soldierId = soldierMap[i];
        for (int j=0; j<soldierNum; j++) {
            int offsetX = 0;
            if (j > 0) {
                offsetX = CommonUtils::getRandom(100, 200);
            }
            createSoldier(soldierId, m_enemyArmy, false, offsetX);
        }
        
        leftNum -= soldierNum;
        if (leftNum <= 0) {
            break;
        }
    }
}

int Battle::checkBlock(){
    int count = NUM * NUM;
    for (int i=0; i<count; i++) {
        Block * block = m_blockList->objectForKey(i);
        CCMutableArray<Block*> * searchAry = new CCMutableArray<Block*>();
        CCMutableArray<Block*> * usedAry = new CCMutableArray<Block*>();
        searchAry->addObject(block);
        int blockType = block->getType();
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
        if(usedAry->count() >= 3){
            return i;
        }
    }
    return -1;
}

void Battle::createBlocks(){
    if (m_blockList->count() > 0) {
        int count = NUM * NUM;
        for (int i=0; i<count; i++) {
            Block *block = m_blockList->objectForKey(i);
            if (block) {
                if (block->getSprite()) {
                    block->getSprite()->removeFromParent();
                }
            }
        }
        m_blockList->removeAllObjects();
    }
    //i为行 j为列
    for (int i=0; i<NUM; i++) {
        for (int j=0; j<NUM; j++) {
            createBlock(i, j);
        }
    }
}

void Battle::setCheckBlock(){
    m_checkBlock = true;
}

void Battle::changeNextScene(bool isWin){
    if (MissionInfo::shared()->getIsArena()) {
        
        string postData = CCString::createWithFormat("enemy_id=%d&is_win=%d", m_arenaInfo->getUserId(), isWin ? 1:0)->m_sString;
        pushStepScene("end_arena.php", postData, ArenaEndScene::scene());//跳转去arena结算
    }else{
        string postData = CCString::createWithFormat("mission_id=%d&is_win=%d", MissionInfo::shared()->getCurrentMissionId(), isWin ? 1:0)->m_sString;
        pushStepScene("end_mission.php", postData, MissionEndScene::scene());
    }
}