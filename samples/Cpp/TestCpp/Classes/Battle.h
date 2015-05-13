//
//  Battle.h
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//

#ifndef __TestCpp__Battle__
#define __TestCpp__Battle__
#include "cocos-ext.h"
#include "cocos2d.h"
USING_NS_CC;
USING_NS_CC_EXT;
#include "BaseScene.h"
#include "Block.h"
#include "Soldier.h"
#include "Wall.h"
#include "MissionMstList.h"
#include "ArenaInfoList.h"
const int NUM = 8;

class Battle : public BaseScene{
public:
    static CCScene * scene();
    Battle();
    virtual ~Battle();
    CREATE_FUNC(Battle);
    virtual bool init();
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void draw();
    void update();
private:
    MissionMst * m_missionMst;
    int m_matrix[NUM][NUM];
    CCMutableDictionary<int, Block*> * m_blockList;
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
    int checkBlock();
    bool m_checkBlock;
    void createBlocks();
    void setCheckBlock();
    bool m_isOver;
    ArenaInfo * m_arenaInfo;
    void changeNextScene(bool isWin);
};


#endif /* defined(__TestCpp__Battle__) */
