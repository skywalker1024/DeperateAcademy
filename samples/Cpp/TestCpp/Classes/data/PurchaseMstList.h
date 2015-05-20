//
//  PurchaseMstList.h
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_PurchaseMstList_h
#define BraveFrontier_PurchaseMstList_h

#include "cocos2d.h"
#include "PurchaseMst.h"

USING_NS_CC;

class PurchaseMstList : public CCObject
{
public:
    // インスタンスの取得
    static PurchaseMstList* shared();
    // オブジェクトの追加
    void addObject( PurchaseMst* mst);
    // オブジェクトの解放
    void removeAllObjects();
    // 件数の取得
    int getCount();
    PurchaseMst * getObject(int index);
    PurchaseMst * getObjectById(int Id);
private:
    // コンストラクタ
    PurchaseMstList();
    // デストラクタ
    ~PurchaseMstList();
    // mstリスト
    CCMutableArray<PurchaseMst*> *mstList;

};

#endif
