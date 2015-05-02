//
//  SoldierMstList.h
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_SoldierMstList_h
#define BraveFrontier_SoldierMstList_h

#include "cocos2d.h"
#include "SoldierMst.h"

USING_NS_CC;

class SoldierMstList : public CCObject
{
public:
    // インスタンスの取得
    static SoldierMstList* shared();
    // オブジェクトの追加
    void addObject( SoldierMst* mst);
    // オブジェクトの解放
    void removeAllObjects();
    // 件数の取得
    int getCount();
    // オブジェクトの取得
    SoldierMst* getObject( int soldier_id );

private:
    // コンストラクタ
    SoldierMstList();
    // デストラクタ
    ~SoldierMstList();
    // mstリスト
    CCMutableArray<SoldierMst*> *mstList;

};

#endif
