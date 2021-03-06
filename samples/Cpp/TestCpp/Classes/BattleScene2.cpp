//
//  BattleScene2.cpp
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//

#include "BattleScene2.h"
#include "CommonUtils.h"
#include "SoldierMstList.h"
#include "MissionInfo.h"
#include "UserInfo.h"
#include "MapScene.h"
#include "MissionEndScene.h"
#include "ArenaEndScene.h"
#include "WallMstList.h"
#include "SimpleAudioEngine.h"
const int START_Y = 100;
const int WIDTH = 100;
const int ARMY_POSITION_Y = START_Y + NUM * WIDTH + 200;
const int BLOCK_GREY_TYPE = 5;//Grey的serie id是5
const float ACTION_TIME = .2f;
BattleScene2::BattleScene2()
{

    MATRIX_START_X = (CommonUtils::getScreenWidth() - NUM * WIDTH) / 2;
    MY_ARMY_START_X = MATRIX_START_X;
    ENEMY_ARMY_START_X = MATRIX_START_X + NUM * WIDTH;

    m_missionMst = NULL;
    m_checkBlock = false;
    m_isOver = false;
    
    m_isMoved = false;
    m_canTouch = false;
    m_bossUseSkill = false;
    m_boss = NULL;
    m_timer = 0;
}

BattleScene2::~BattleScene2(){
}

CCScene * BattleScene2::scene(){
    CCScene* scene = CCScene::create();
    scene->addChild(BattleScene2::create());
    return scene;
}

bool BattleScene2::init(){
    if (!BaseScene::init()) {
        return false;
    }
//    if (MissionInfo::shared()->getIsArena()) {
//        int arena_id = MissionInfo::shared()->getCurrentArenaId();
//        m_arenaInfo = ArenaInfoList::shared()->getObject(arena_id);
//        m_enemyTimer = CommonUtils::getRandom(m_arenaInfo->getMinTimer(), m_arenaInfo->getMaxTimer());
//    }else{
        int mission_id = MissionInfo::shared()->getCurrentMissionId();
        m_missionMst = MissionMstList::shared()->getObject(mission_id);
        m_enemyTimer = CommonUtils::getRandom(m_missionMst->getMinTimer(), m_missionMst->getMaxTimer());
    m_enemyTimer = 10;
//    }

    CCLog("height=%f width=%f", CCDirector::sharedDirector()->getWinSize().height, CCDirector::sharedDirector()->getWinSize().width );
   
    createBlocks();
    
    SoldierMstList::shared();
    
    initPoint();
    
    //init boss
    initBoss();
    
    //init timer
    m_timer = CommonUtils::getRandom(3, 5) * 60 * 60;
    
    int rest_time = m_timer / 60;
    int min = rest_time / 60;
    int second = rest_time % 60;
    CCString * restString = CCString::createWithFormat("%d:%02d", min, second);
    m_timerLabel = GraphicUtils::drawString(this, restString->m_sString, 20, CommonUtils::getScreenHeight() - 200, getSystemColor(COLOR_KEY_GOLD), TEXT_ALIGN_LEFT_MIDDLE, 60);
    
    this->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(2.f), CCCallFunc::create(this, callfunc_selector(BattleScene2::setCheckBlock))));
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/bgm.mp3", true);
    return true;
}

bool BattleScene2::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
    CCAssert(false, "onAssignCCBMemberVariable ended without assigning any variables. Check variable name");
    return false;
}

void BattleScene2::onEnter(){
    BaseScene::onEnter();
}

void BattleScene2::onExit(){
    BaseScene::onExit();
}

bool BattleScene2::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    BaseScene::ccTouchBegan(pTouch, pEvent);
    
   
    m_isMoved = false;
    CCRect touchArea =  CCRect(MATRIX_START_X, START_Y, WIDTH * NUM, WIDTH * NUM);
    if (!touchArea.containsPoint(pTouch->getLocation())) {
        return false;
    }
    
    if (!m_canTouch || m_bossUseSkill) {
        return false;
    }
    //判断落在哪个坑
    CCLog("ccTouchBegan x=%f y=%f",pTouch->getLocation().x, pTouch->getLocation().y);
    int j = (pTouch->getLocation().x - MATRIX_START_X) / WIDTH;
    int i = (pTouch->getLocation().y - START_Y) / WIDTH;
    
    if (m_matrix[i][j]) {
        if(m_matrix[i][j]->getIsLocked()){
            initPoint();
            CCLog("ccTouchBegan i=%d j=%d isLOcked", i, j);
            return false;
        }
    }
    if (m_prevPoint.x >=0) {
        if ((i!= m_prevPoint.x || j!= m_prevPoint.y)) {
            m_nowPoint = ccp(i, j);
            if (canExchange()) {
                CCLog("ccTouchBegan i=%d j=%d canExchange", i, j);
            }else{
                CCLog("ccTouchBegan i=%d j=%d can not Exchange", i, j);
                initPoint();
                m_prevPoint = ccp(i, j);
            }
        }
    }else{
        CCLog("ccTouchBegan i=%d j=%d m_prevPoint", i, j);
        m_prevPoint = ccp(i, j);
    }
    
    return true;
}

void BattleScene2::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    BaseScene::ccTouchMoved(pTouch, pEvent);
    CCLog("ccTouchMoved x=%f y=%f",pTouch->getLocation().x, pTouch->getLocation().y);
    if (!m_canTouch || m_bossUseSkill) {
        CCLog("ccTouchMoved m_canTouch x=%f y=%f",pTouch->getLocation().x, pTouch->getLocation().y);
        return;
    }
    CCRect touchArea =  CCRect(MATRIX_START_X, START_Y, WIDTH * NUM, WIDTH * NUM);
    if (!touchArea.containsPoint(pTouch->getLocation())) {
        initPoint();
        return;
    }
    
    
    int j = (pTouch->getLocation().x - MATRIX_START_X) / WIDTH;
    int i = (pTouch->getLocation().y - START_Y) / WIDTH;
    
    if (m_matrix[i][j]) {
        if(m_matrix[i][j]->getIsLocked()){
            initPoint();
            CCLog("ccTouchMoved getIsLocked i=%d y=%d",i, j);
            return;
        }
    }
    if ((i!= m_prevPoint.x || j!= m_prevPoint.y)) {
        m_nowPoint = ccp(i, j);
        if (canExchange() && m_canTouch) {
            m_canTouch = false;//防止再次点击
            CCLog("ccTouchMoved canExchange i=%d y=%d",i, j);
            m_isMoved = true;
            exchangeBlock();
        }else{
            initPoint();
            m_prevPoint = ccp(i, j);
        }
    }
}

void BattleScene2::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    BaseScene::ccTouchEnded(pTouch, pEvent);
    if (!m_canTouch || m_bossUseSkill) {
        return;
    }
    if (!m_isMoved) {
        if (canExchange()) {
            exchangeBlock();
        }
    }
}
void BattleScene2::ccTouchCanceled(CCTouch *pTouch, CCEvent *pEvent){
    initPoint();
}

void BattleScene2::createBlock(int i , int j){
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
    string key = string("cell").append(CommonUtils::IntToString(rand));
    CCSpriteBatchNode *batchNode = getCacheBatchNode(key, "cell");
    if ( !batchNode ) {
        string spriteName = string("img/bubble_").append(CommonUtils::IntToString(rand)).append(".png");
        batchNode = CCSpriteBatchNode::create( spriteName.c_str(), kDefaultSpriteBatchCapacity);
        this->addChild(batchNode);
        this->setCacheBatchNode(key, "cell", batchNode);
    }
    Cell *block = Cell::create();
    block->initWithTexture(batchNode->getTexture());
    block->setAnchorPoint(CCPointZero);
    block->setPosition(ccpAdd(ccp(MATRIX_START_X, START_Y), ccp(WIDTH * j, WIDTH * i)));
    block->setScale( WIDTH / block->getTexture()->getContentSize().width );
    CCLog("width=%f scale=%f",block->getContentSize().width, block->getScale() );
    this->addChild(block);
    
    block->setType(rand + 1);//type是serie id
    m_matrix[i][j] = block;

}

void BattleScene2::draw(){
    if (m_isOver) {
        return;
    }
    
    //updateTimer
    checkTimer();
    
    //checkLose
    if(checkLose()){
        GraphicUtils::drawString(this, "you lose!", CommonUtils::getScreenWidth() / 2, CommonUtils::getScreenHeight() - 300, getSystemColor(COLOR_KEY_RED), TEXT_ALIGN_CENTER_MIDDLE, 60);
        m_isOver = true;
        changeNextScene(false);
    }
    //checkExistMove TODO
    
    //checkBlock
    if (m_checkBlock) {
        checkBlock();
    }
    
    if (m_boss && !m_boss->getIsDead()){
        if (m_enemyTimer > 0) {
            m_enemyTimer--;
        }else{
            m_bossUseSkill = true;
            if (m_bossUseSkill && m_canTouch) {
                m_bossUseSkill = false;
                bossUseSkill();
                //        if (MissionInfo::shared()->getIsArena()) {
                //            m_enemyTimer = CommonUtils::getRandom(m_arenaInfo->getMinTimer(), m_arenaInfo->getMaxTimer());
                //        }else{
                m_enemyTimer = CommonUtils::getRandom(m_missionMst->getMinTimer(), m_missionMst->getMaxTimer());
                //        }
            }
        }
    }

    //检查输赢
    if ( checkWin() ) {
        GraphicUtils::drawString(this, "you win!", CommonUtils::getScreenWidth() / 2, CommonUtils::getScreenHeight() - 300, getSystemColor(COLOR_KEY_RED), TEXT_ALIGN_CENTER_MIDDLE, 60);
        m_isOver = true;
        changeNextScene(true);
    }
}

void BattleScene2::bossUseSkill(){
    m_boss->useSkillAction();
    
    //随机挑选3个锁链锁上
    for (int k=0; k<3; k++) {
        int i = CommonUtils::getRandom(0, NUM - 1);
        int j = CommonUtils::getRandom(0, NUM - 1);
        Cell *cell = m_matrix[i][j];
        if (cell) {
            CCSpriteBatchNode *batchNode = getCacheBatchNode("lock", "lock");
            if ( !batchNode ) {
                
                batchNode = CCSpriteBatchNode::create( "img/chain.png", kDefaultSpriteBatchCapacity);
                this->addChild(batchNode);
                this->setCacheBatchNode("lock", "lock", batchNode);
            }
            cell->lockWithTexture(batchNode->getTexture());
        }
    }
}

void BattleScene2::checkBlock(){
    bool hasRemoveCell = isExistRemoveCell();
    if (!hasRemoveCell) {
        m_canTouch = true;
        return;
    }
    
    m_checkBlock = false;
    initPoint();
    //removeBlocks
    for(int i=0;i<NUM;i++) //判断7行里面每行是否有可以消除的
    {
        for(int j=0;j<NUM;j++)
        {
            if(m_matrix[i][j]->getCanRemove())
            {
                if (m_matrix[i][j]->getIsLocked()) {
                    m_matrix[i][j]->unlock();
                    m_matrix[i][j]->setCanRemove(false);//重新置位防止下次check时被delete
                }else{
                    CCPoint pos = m_matrix[i][j]->getPosition();
                    int blockType = m_matrix[i][j]->getType();
                    
                    m_matrix[i][j]->removeFromParent();
                    m_matrix[i][j] = NULL;
                    
                    //create fire ball
                    createFireBall(pos, blockType);
                    
                    //城墙倒掉一块
                    if (m_block[i][j]) {
                        Block * block = m_block[i][j];
                        if (block->getType() == 1) {
                            m_block[i][j] = NULL;
                        }
                        block->decType();
                    }
                }
                
            }
        }
    }
    
    //autoDown new Blocks
    autoDownBlocks();
    this->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(ACTION_TIME + .1f), CCCallFunc::create(this, callfunc_selector(BattleScene2::checkBlock))));//这个delay时间要长过ACTION_TIME
}

void BattleScene2::createBlocks(){
    //i为行 j为列
    for (int i=0; i<NUM; i++) {
        for (int j=0; j<NUM; j++) {
            createBlock(i, j);
            
            Block *block = Block::create(CommonUtils::getRandom(1, 3), this, ccpAdd(ccp(MATRIX_START_X, START_Y), ccp(WIDTH * j, WIDTH * i)));
            m_block[i][j] = block;
        }
    }
}

void BattleScene2::setCheckBlock(){
    m_checkBlock = true;
    m_canTouch = false;
}

void BattleScene2::changeNextScene(bool isWin){
//    if (MissionInfo::shared()->getIsArena()) {
//        
//        string postData = CCString::createWithFormat("enemy_id=%d&is_win=%d", m_arenaInfo->getUserId(), isWin ? 1:0)->m_sString;
//        pushStepScene("end_arena.php", postData, ArenaEndScene::scene());//跳转去arena结算
//    }else{
        string postData = CCString::createWithFormat("mission_id=%d&is_win=%d", MissionInfo::shared()->getCurrentMissionId(), isWin ? 1:0)->m_sString;
        pushStepScene("end_mission.php", postData, MissionEndScene::scene());
//    }
}

void BattleScene2::initPoint(){
    m_prevPoint = ccp(-1,-1);
    m_nowPoint = ccp(-1, -1);
}

void BattleScene2::exchangeBlock(){
    CCLog("exchange block");
    m_checkBlock = false;
    
    int prevI = (int) m_prevPoint.x;
    int prevJ = (int) m_prevPoint.y;
    int nowI = (int) m_nowPoint.x;
    int nowJ = (int) m_nowPoint.y;
    Cell * prevBlock = m_matrix[prevI][prevJ];
    Cell * nowBlock = m_matrix[nowI][nowJ];
    
    m_matrix[prevI][prevJ] = nowBlock;
    m_matrix[nowI][nowJ] = prevBlock;
    
    //预判断是否可交换
    bool removeFlg = isExistRemoveCell();
    
    if(removeFlg){
        //交换位置后再checkBlock
        prevBlock->runAction(CCMoveTo::create(ACTION_TIME, nowBlock->getPosition()));
        nowBlock->runAction(CCMoveTo::create(ACTION_TIME, prevBlock->getPosition()));
        m_matrix[prevI][prevJ] = nowBlock;
        m_matrix[nowI][nowJ] = prevBlock;
        this->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(ACTION_TIME + .1f), CCCallFunc::create(this, callfunc_selector(BattleScene2::checkBlock))));
    }else{
        //交换过来再换回去
        m_matrix[prevI][prevJ] = prevBlock;
        m_matrix[nowI][nowJ] = nowBlock;
        prevBlock->runAction(CCSequence::createWithTwoActions(CCMoveTo::create(ACTION_TIME, nowBlock->getPosition()), CCMoveTo::create(ACTION_TIME, prevBlock->getPosition())) );
        nowBlock->runAction(CCSequence::create(CCMoveTo::create(ACTION_TIME, prevBlock->getPosition()), CCMoveTo::create(ACTION_TIME, nowBlock->getPosition()), CCCallFunc::create(this, callfunc_selector(BattleScene2::checkBlock)), NULL) );
        initPoint();
    }
}

bool BattleScene2::canExchange(){
    if (fabs(m_nowPoint.x - m_prevPoint.x) == 1 && m_nowPoint.y == m_prevPoint.y) {
        return true;
    }
    
    if (fabs(m_nowPoint.y - m_prevPoint.y) == 1 && m_nowPoint.x == m_prevPoint.x) {
        return true;
    }
    
    return false;
}
void BattleScene2::autoDownBlocks()//自动掉落
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

void BattleScene2::createFireBall(CCPoint startPos, int type){
    if (!m_boss) {
        return;
    }
    float duration = 1.f;
    float x1 = 400;//  CommonUtils::getRandom(10, 20);
    float y1 = 0;// CommonUtils::getRandom(-800, -700);
    
    float x2 = -300;// CommonUtils::getRandom(300, 400);
    float y2 = 300;//CommonUtils::getRandom(-400, 0);
    CCLog("x1=%f y1=%f x2=%f y2=%f", x1,y1, x2,y2);
    ccBezierConfig config;
    config.controlPoint_1 = ccp(x1,y1);
    config.controlPoint_2 = ccp(x2,y1);
    config.endPosition = ccp(500,1200);
    
    ParticleAnime * particle = ParticleAnime::create("plist/fireBall.plist");
    particle->setTag(1);//这里临时借用tag做伤害
    particle->CCNode::setPosition(startPos);
    addChild(particle);
    CCSequence *seq = CCSequence::createWithTwoActions(CCBezierTo::create(duration, config), CCCallFuncO::create(this, callfuncO_selector(BattleScene2::decBossHp), particle));
    particle->runAction(seq);
    
    m_boss->AttackedAction(duration);

}

void BattleScene2::decBossHp(ParticleAnime * anime)
{
    int damage = anime->getTag();
    anime->removeFromParent();
    if (m_boss) {
        if (m_boss->getIsDead()) {
            m_boss = NULL;
        }else{
            m_boss->decHp(damage);
        }
    }
}

bool BattleScene2::checkWin(){
    for (int i=0; i<NUM; i++) {
        for (int j=0; j<NUM; j++) {
            if (m_block[i][j]) {
                return false;
            }
        }
    }
    
    if (m_boss && !m_boss->getIsDead()) {
        return false;
    }
    
    return true;
}

bool BattleScene2::checkLose(){
    if (m_timer<=0) {
        return true;//time's up
    }
    return false;
}

void BattleScene2::initBoss(){
    m_boss = Boss::create();
    m_boss->setPosition(ccp(500, 1200));
    this->addChild(m_boss);
}

void BattleScene2::checkTimer(){
    m_timer--;
    int rest_time = m_timer / 60;
    int min = rest_time / 60;
    int second = rest_time % 60;
    CCString * restString = CCString::createWithFormat("%d:%02d", min, second);
    m_timerLabel->changeString(restString->m_sString);

}

bool BattleScene2::isExistRemoveCell(){
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
    return removeFlg;
}