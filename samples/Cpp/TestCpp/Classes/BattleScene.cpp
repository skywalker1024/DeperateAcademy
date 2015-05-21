//
//  BattleScene.cpp
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//

#include "BattleScene.h"
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
const float ACTION_TIME = .2f;
BattleScene::BattleScene()
{
    m_myArmy = new CCMutableArray<Soldier*>();
    m_enemyArmy = new CCMutableArray<Soldier*>();
    MATRIX_START_X = (CommonUtils::getScreenWidth() - NUM * WIDTH) / 2;
    MY_ARMY_START_X = MATRIX_START_X;
    ENEMY_ARMY_START_X = MATRIX_START_X + NUM * WIDTH;
    m_myWall = NULL;
    m_enemyWall = NULL;
    m_missionMst = NULL;
    m_checkBlock = false;
    m_isOver = false;
    m_riceList = new CCMutableDictionary<int, Rice*>();
    m_isMoved = false;
    
}

BattleScene::~BattleScene(){
    m_myArmy->removeAllObjects();
    m_myArmy->release();
    m_enemyArmy->removeAllObjects();
    m_enemyArmy->release();
    CC_SAFE_RELEASE_NULL(m_myWall);
    CC_SAFE_RELEASE_NULL(m_enemyWall);
}

CCScene * BattleScene::scene(){
    CCScene* scene = CCScene::create();
    scene->addChild(BattleScene::create());
    return scene;
}

bool BattleScene::init(){
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
    
    initPoint();
    
    
    this->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(2.f), CCCallFunc::create(this, callfunc_selector(BattleScene::setCheckBlock))));
    return true;
}

bool BattleScene::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
    CCAssert(false, "onAssignCCBMemberVariable ended without assigning any variables. Check variable name");
    return false;
}

void BattleScene::onEnter(){
    BaseScene::onEnter();
    
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("ccs-res/armature/knight.png", "ccs-res/armature/knight.plist", "ccs-res/armature/knight.xml", this, NULL);
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("ccs-res/armature/weapon.png", "ccs-res/armature/weapon.plist", "ccs-res/armature/weapon.xml", this, NULL);
}

void BattleScene::onExit(){
    BaseScene::onExit();
}

bool BattleScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    BaseScene::ccTouchBegan(pTouch, pEvent);
    m_isMoved = false;
    CCRect touchArea =  CCRect(MATRIX_START_X, START_Y, WIDTH * NUM, WIDTH * NUM);
    if (!touchArea.containsPoint(pTouch->getLocation())) {
        return false;
    }
    //判断落在哪个坑
    CCLog("ccTouchBegan x=%f y=%f",pTouch->getLocation().x, pTouch->getLocation().y);
    int j = (pTouch->getLocation().x - MATRIX_START_X) / WIDTH;
    int i = (pTouch->getLocation().y - START_Y) / WIDTH;
    CCLog("ccTouchBegan i=%d j=%d", i, j);
    if (m_prevPoint.x >=0) {
        m_nowPoint = ccp(i, j);
        if (canExchange()) {
            
        }else{
            initPoint();
            m_prevPoint = ccp(i, j);
        }
    }else{
        m_prevPoint = ccp(i, j);
    }
    
    return true;
}

void BattleScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    BaseScene::ccTouchMoved(pTouch, pEvent);
    
    CCRect touchArea =  CCRect(MATRIX_START_X, START_Y, WIDTH * NUM, WIDTH * NUM);
    if (!touchArea.containsPoint(pTouch->getLocation())) {
        initPoint();
        return;
    }
    
    CCLog("x=%f y=%f",pTouch->getLocation().x, pTouch->getLocation().y);
    int j = (pTouch->getLocation().x - MATRIX_START_X) / WIDTH;
    int i = (pTouch->getLocation().y - START_Y) / WIDTH;
    if ((i!= m_prevPoint.x || j!= m_prevPoint.y)) {
        if (m_nowPoint.x == -1 && m_nowPoint.y == -1) {
            m_nowPoint = ccp(i,j);
            //如果相邻
            if(canExchange()){
                m_isMoved = true;
                exchangeBlock(true);
            }
        }else{
            if (m_nowPoint.x == i && m_nowPoint.y == j) {
                
            }else{
                initPoint();
            }
        }
    }
}

void BattleScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    BaseScene::ccTouchEnded(pTouch, pEvent);
    
    if (!m_isMoved) {
        if (canExchange()) {
            exchangeBlock(true);
        }
    }
}
void BattleScene::ccTouchCanceled(CCTouch *pTouch, CCEvent *pEvent){
    initPoint();
}

void BattleScene::createSoldier(int soldierId, CCMutableArray<Soldier*>* army, bool myArmy, int offsetX){
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

void BattleScene::createBlock(int i , int j){
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
    block->initWithTexture(batchNode->getTexture());
    block->setAnchorPoint(CCPointZero);
    block->setPosition(ccpAdd(ccp(MATRIX_START_X, START_Y), ccp(WIDTH * j, WIDTH * i)));
    block->setScale( WIDTH / block->getTexture()->getContentSize().width );
    this->addChild(block);
    
    block->setType(rand + 1);//type是serie id
    m_matrix[i][j] = block;

}

void BattleScene::draw(){
    if (m_isOver) {
        return;
    }
    
    //checkExistMove
    
    //checkBlock
    if (m_checkBlock) {
        checkBlock();
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

void BattleScene::updateArmy(CCMutableArray<Soldier*>* atkArmy, CCMutableArray<Soldier*>* defArmy, bool myArmy){
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

void BattleScene::createEnemy(){
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

void BattleScene::checkBlock(){
    bool removeFlg = false;
    //判断每行是否有可以消除的
    for(int i=0;i<NUM;i++) //判断7行里面每行是否有可以消除的
    {
        for(int j=0;j<=NUM - 3;j++)
        {
            int type = m_matrix[i][j]->getType(); //获取map[r][c]的怪物编号
            int samnum=0;
            int nowcol=0;
            for(nowcol=j+1; nowcol<NUM; nowcol++) {
                if(type==m_matrix[i][nowcol]->getType())
                {
                    samnum++;
                }else
                {
                    break;
                }
            }
            //判断samenum
            if(samnum>=2) //消除所有相同的
            {
                removeFlg = true;
                for(int tmp=j;tmp<nowcol;tmp++)
                {
                    m_matrix[i][tmp]->setCanRemove(true);
                }
            }
        }
    }
    
    //判断每列是否有可以消除的
    for(int j=0;j<NUM;j++) //判断7行里面每行是否有可以消除的
    {
        for(int i=0;i<=NUM - 3;i++)
        {
            int type = m_matrix[i][j]->getType(); //获取map[r][c]的怪物编号
            int samnum=0;
            int nowrow=0;
            for(nowrow=i+1; nowrow<NUM; nowrow++) {
                if(type==m_matrix[nowrow][j]->getType())
                {
                    samnum++;
                }else
                {
                    break;
                }
            }
            //判断samenum
            if(samnum>=2) //消除所有相同的
            {
                removeFlg = true;
                for(int tmp=i;tmp<nowrow;tmp++)
                {
                    m_matrix[tmp][j]->setCanRemove(true);
                }
            }
        }
    }
    
    if (!removeFlg) {
        if (m_prevPoint.x != -1 && m_nowPoint.x != -1) {
            //把两个block交换回去
            exchangeBlock(false);
            initPoint();
        }
    }else{
        m_checkBlock = false;
        initPoint();
        //removeBlocks
        for(int i=0;i<NUM;i++) //判断7行里面每行是否有可以消除的
        {
            for(int j=0;j<NUM;j++)
            {
                if(m_matrix[i][j]->getCanRemove())
                {
                    //increase rice
                    int blockType = m_matrix[i][j]->getType();
                    if (blockType != BLOCK_GREY_TYPE) {
                        int soldierId = UserInfo::shared()->m_soldierMap[blockType];
                        if(m_riceList->objectForKey(blockType)->updateCount(1)){
                            createSoldier(soldierId, m_myArmy, true, 0);
                        }
                    }
                    m_matrix[i][j]->removeFromParent();
                    m_matrix[i][j] = NULL;
                }
            }
        }
        
        //autoDown new Blocks
        autoDownBlocks();
        this->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(ACTION_TIME + .1f), CCCallFunc::create(this, callfunc_selector(BattleScene::checkBlock))));//这个delay时间要长过ACTION_TIME
    }
}

void BattleScene::createBlocks(){
    /*
    for (int i=0; i<NUM; i++) {
        for (int j=0; j<NUM; j++) {
            Block *block = m_matrix[i][j];
            if (block) {
                if (block->getSprite()) {
                    block->getSprite()->removeFromParent();
                }
            }
        }
    }
     */
    //i为行 j为列
    for (int i=0; i<NUM; i++) {
        for (int j=0; j<NUM; j++) {
            createBlock(i, j);
        }
    }
}

void BattleScene::setCheckBlock(){
    m_checkBlock = true;
}

void BattleScene::changeNextScene(bool isWin){
    if (MissionInfo::shared()->getIsArena()) {
        
        string postData = CCString::createWithFormat("enemy_id=%d&is_win=%d", m_arenaInfo->getUserId(), isWin ? 1:0)->m_sString;
        pushStepScene("end_arena.php", postData, ArenaEndScene::scene());//跳转去arena结算
    }else{
        string postData = CCString::createWithFormat("mission_id=%d&is_win=%d", MissionInfo::shared()->getCurrentMissionId(), isWin ? 1:0)->m_sString;
        pushStepScene("end_mission.php", postData, MissionEndScene::scene());
    }
}

void BattleScene::initPoint(){
    m_prevPoint = ccp(-1,-1);
    m_nowPoint = ccp(-1, -1);
}

void BattleScene::exchangeBlock(bool needCheck){
    CCLog("exchange block");
    m_checkBlock = false;
    
    int prevI = (int) m_prevPoint.x;
    int prevJ = (int) m_prevPoint.y;
    int nowI = (int) m_nowPoint.x;
    int nowJ = (int) m_nowPoint.y;
    Block * prevBlock = m_matrix[prevI][prevJ];
    Block * nowBlock = m_matrix[nowI][nowJ];
    
    //先交换位置之后判断是否需要消除
    prevBlock->runAction(CCMoveTo::create(ACTION_TIME, nowBlock->getPosition()));
    nowBlock->runAction(CCMoveTo::create(ACTION_TIME, prevBlock->getPosition()));
    m_matrix[prevI][prevJ] = nowBlock;
    m_matrix[nowI][nowJ] = prevBlock;

    if (needCheck) {
        this->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(ACTION_TIME + .1f), CCCallFunc::create(this, callfunc_selector(BattleScene::checkBlock))));
    }
}

bool BattleScene::canExchange(){
    if (fabs(m_nowPoint.x - m_prevPoint.x) == 1 && m_nowPoint.y == m_prevPoint.y) {
        return true;
    }
    
    if (fabs(m_nowPoint.y - m_prevPoint.y) == 1 && m_nowPoint.x == m_prevPoint.x) {
        return true;
    }
    
    return false;
}
void BattleScene::autoDownBlocks()//自动掉落
{
    for(int j=0; j<NUM; j++){
        for (int i=0; i<NUM; i++) {
            if(m_matrix[i][j]==NULL)
            { //让他上方的所有块向下移动
                CCLog("i%d j=%d NULL",i,j);
                for(int tmprow=i;tmprow<NUM-1;tmprow++)
                {
                    if(m_matrix[tmprow+1][j]!=NULL)
                    {
                        m_matrix[tmprow+1][j]->runAction( CCMoveTo::create(ACTION_TIME, ccpAdd(ccp(MATRIX_START_X, START_Y), ccp(j * WIDTH, i * WIDTH))));
                        m_matrix[i][j]=m_matrix[tmprow+1][j];
                        m_matrix[tmprow+1][j]=NULL;
                        CCLog("set i=%d j=%d NULL",tmprow+1,j);
                        CCLog("set i=%d j=%d  not NULL",i,j);
                        break;
                    }
                }
            }
        }
    }
    
    //补齐
    for(int j=0; j<NUM; j++){
        int blank_count = 0;
        for (int i=0; i<NUM; i++) {
            if(m_matrix[i][j]==NULL){
                createBlock(i, j);
                CCPoint targetPos = m_matrix[i][j]->getPosition();
                m_matrix[i][j]->setPosition(ccpAdd(ccp(MATRIX_START_X, START_Y), ccp(j * WIDTH, NUM * WIDTH + blank_count * WIDTH)));
                m_matrix[i][j]->runAction(CCMoveTo::create(ACTION_TIME, targetPos));
                
                blank_count++;
                
            }
        }
    }
    
}