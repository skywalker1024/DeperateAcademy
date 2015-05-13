//
//  ArenaInfoList.h
//  BraveFrontier

//  Created by WillArk on 5/10/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_ArenaInfoList_h
#define BraveFrontier_ArenaInfoList_h

#include "cocos2d.h"

USING_NS_CC;
#include "ArenaInfo.h"

class ArenaInfoList : public CCObject
{
public:
    // インスタンスの取得
    static ArenaInfoList* shared();
    // オブジェクトの追加
    void addObject( ArenaInfo* mst);
    // オブジェクトの解放
    void removeAllObjects();
    // 件数の取得
    int getCount();
    // オブジェクトの取得
    ArenaInfo* getObject( int index );
    void updateWithJson(Json::Value json);
private:
    // コンストラクタ
    ArenaInfoList();
    // デストラクタ
    ~ArenaInfoList();
    // mstリスト
    CCMutableArray<ArenaInfo*> *arenaList;
};

#endif
