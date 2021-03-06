//
//  BattleScene.h
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//

#ifndef __TestCpp__BattleScene__
#define __TestCpp__BattleScene__
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
#include "Rice.h"
const int NUM = 8;

class BattleScene : public BaseScene{
public:
    static CCScene * scene();
    BattleScene();
    virtual ~BattleScene();
    CREATE_FUNC(BattleScene);
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
    CCMutableDictionary<int, Rice*> * m_riceList;
    void createSoldier(int soldierId, CCMutableArray<Soldier*>* army, bool myArmy, int offsetX);
    void createBlock(int i, int j);
    int MATRIX_START_X;
    int MY_ARMY_START_X;
    int ENEMY_ARMY_START_X;
    CCMutableArray<Soldier*>* m_myArmy;
    CCMutableArray<Soldier*>* m_enemyArmy;
    void updateArmy(CCMutableArray<Soldier*>* atkArmy, CCMutableArray<Soldier*>* defArmy, bool myArmy);
    CC_SYNTHESIZE_RETAIN(Wall*, m_myWall, MyWall);
    CC_SYNTHESIZE_RETAIN(Wall*, m_enemyWall, EnemyWall);
private:
    void createEnemy();
    int m_enemyTimer;
    void checkBlock();//检查所有可消除的方块
    bool m_checkBlock;
    void createBlocks();
    void setCheckBlock();
    bool m_isOver;
    ArenaInfo * m_arenaInfo;
    void changeNextScene(bool isWin);
    
    CCPoint m_prevPoint;
    CCPoint m_nowPoint;
    void initPoint();
    void exchangeBlock(bool needCheck);
    bool canExchange();
    void autoDownBlocks();
    bool m_isMoved;
    bool m_isChecking;
    void createFireBall(CCPoint startPos, int type);
};


#endif /* defined(__TestCpp__BattleScene__) */
