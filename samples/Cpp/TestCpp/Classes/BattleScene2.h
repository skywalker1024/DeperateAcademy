//
//  BattleScene2.h
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//

#ifndef __TestCpp__BattleScene2__
#define __TestCpp__BattleScene2__
#include "cocos-ext.h"
#include "cocos2d.h"
USING_NS_CC;
USING_NS_CC_EXT;
#include "BaseScene.h"
#include "Cell.h"
#include "Soldier.h"
#include "Wall.h"
#include "MissionMstList.h"
#include "ArenaInfoList.h"
#include "Block.h"
#include "Boss.h"
const int NUM = 8;

class BattleScene2 : public BaseScene{
public:
    static CCScene * scene();
    BattleScene2();
    virtual ~BattleScene2();
    CREATE_FUNC(BattleScene2);
    virtual bool init();
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCanceled(CCTouch *pTouch, CCEvent *pEvent);
    void draw();
    void update();
private:
    MissionMst * m_missionMst;
    Cell * m_matrix[NUM][NUM];
    Block * m_block[NUM][NUM];
    
    void createBlock(int i, int j);
    int MATRIX_START_X;
    int MY_ARMY_START_X;
    int ENEMY_ARMY_START_X;
   
private:
   
    int m_enemyTimer;
    int m_timer;
    StringLabelList * m_timerLabel;
    void checkBlock();//检查所有可消除的方块
    bool m_checkBlock;
    void createBlocks();
    void setCheckBlock();
    bool m_isOver;
    
    void changeNextScene(bool isWin);
    
    CCPoint m_prevPoint;
    CCPoint m_nowPoint;
    void initPoint();
    void exchangeBlock();
    bool canExchange();
    void autoDownBlocks();
    bool m_isMoved;
    bool m_isChecking;
    void createFireBall(CCPoint startPos, int type);
    
    void bossUseSkill();
    bool checkWin();
    bool checkLose();
    bool m_bossUseSkill;
    void initBoss();
    Boss * m_boss;
    void decBossHp(ParticleAnime * anime);
    void checkTimer();
    
    bool isExistRemoveCell();
};


#endif /* defined(__TestCpp__BattleScene2__) */
