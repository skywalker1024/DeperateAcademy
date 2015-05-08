//
//  EvoMstList.h
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_EvoMstList_h
#define BraveFrontier_EvoMstList_h

#include "cocos2d.h"
#include "EvoMst.h"

USING_NS_CC;

class EvoMstList : public CCObject
{
public:
    // インスタンスの取得
    static EvoMstList* shared();
    // オブジェクトの追加
    void addObject( EvoMst* mst);
    // オブジェクトの解放
    void removeAllObjects();
    // 件数の取得
    int getCount();
    // オブジェクトの取得
    EvoMst * getObjectByBeforeId( int before_id );
    EvoMst * getObject( int evo_id );
private:
    // コンストラクタ
    EvoMstList();
    // デストラクタ
    ~EvoMstList();
    // mstリスト
    CCMutableArray<EvoMst*> *mstList;

};

#endif
