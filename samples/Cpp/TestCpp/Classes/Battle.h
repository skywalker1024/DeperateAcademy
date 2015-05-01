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
    int m_matrix[NUM][NUM];
    CCMutableDictionary<int, Block*> * m_blockList;
    void createSoldier(int kind, CCMutableArray<Soldier*>* army, bool myArmy);
    void createBlock(int i, int j);
    int MATRIX_START_X;
    int MY_ARMY_START_X;
    int ENEMY_ARMY_START_X;
    CCMutableArray<Soldier*>* m_myArmy;
    CCMutableArray<Soldier*>* m_enemyArmy;
    void updateArmy(CCMutableArray<Soldier*>* atkArmy, CCMutableArray<Soldier*>* defArmy, bool myArmy);
};


#endif /* defined(__TestCpp__Battle__) */
