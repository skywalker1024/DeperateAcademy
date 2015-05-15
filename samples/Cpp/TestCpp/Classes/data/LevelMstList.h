//
//  LevelMstList.h
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_LevelMstList_h
#define BraveFrontier_LevelMstList_h

#include "cocos2d.h"
#include "LevelMst.h"

USING_NS_CC;

class LevelMstList : public CCObject
{
public:
    // インスタンスの取得
    static LevelMstList* shared();
    // オブジェクトの追加
    void addObject( LevelMst* mst);
    // オブジェクトの解放
    void removeAllObjects();
    // 件数の取得
    int getCount();
    // オブジェクトの取得
    LevelMst* getObject( int lv );
    LevelMst* getObjectByUnLockSoldierId( int soldier_id );
    LevelMst* getObjectByUnLockWallLv( int wall_lv );
private:
    // コンストラクタ
    LevelMstList();
    // デストラクタ
    ~LevelMstList();
    // mstリスト
    CCMutableArray<LevelMst*> *mstList;

};

#endif
