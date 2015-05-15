//
//  WallMstList.h
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_WallMstList_h
#define BraveFrontier_WallMstList_h

#include "cocos2d.h"
#include "WallMst.h"

USING_NS_CC;

class WallMstList : public CCObject
{
public:
    // インスタンスの取得
    static WallMstList* shared();
    // オブジェクトの追加
    void addObject( WallMst* mst);
    // オブジェクトの解放
    void removeAllObjects();
    // 件数の取得
    int getCount();
    // オブジェクトの取得
    WallMst* getObject( int lv );
private:
    // コンストラクタ
    WallMstList();
    // デストラクタ
    ~WallMstList();
    // mstリスト
    CCMutableArray<WallMst*> *mstList;

};

#endif
