//
//  PurchaseMstList.cpp
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "PurchaseMstList.h"
#include "SQLiteManager.h"
PurchaseMstList* PurchaseMstListInstance = NULL;

/*
 * シングルトンインスタンスを取得。
 */
PurchaseMstList* PurchaseMstList::shared()
{
	if( PurchaseMstListInstance == NULL )
	{
		PurchaseMstListInstance= new PurchaseMstList();
        
        //读取sqlite
        CCArray * list = SQLiteManager::sharedInstance()->selectRows("select * from purchase_mst");
        for (int i=0; i<list->count(); i++) {
            PurchaseMst * PurchaseMst = new class PurchaseMst();
            PurchaseMst->initWithArray(dynamic_cast<CCDictionary*>(list->objectAtIndex(i)));
            PurchaseMstListInstance->addObject(PurchaseMst);
        }
	}

	return PurchaseMstListInstance;
}

/*
 * コンストラクタ。
 */
PurchaseMstList::PurchaseMstList()
{
	mstList = new CCMutableArray<PurchaseMst*>;
}

/*
 * デストラクタ。
 */
PurchaseMstList::~PurchaseMstList()
{

}

/*
 * オブジェクトの追加。
 */
void PurchaseMstList::addObject( PurchaseMst* mst )
{
	mstList->addObject( mst );
    mst->autorelease();
}

/*
 * オブジェクトの解放。
 */
void PurchaseMstList::removeAllObjects()
{
	mstList->removeAllObjects();
}

/*
 * 件数の取得。
 */
int PurchaseMstList::getCount()
{
	return mstList->count();
}

PurchaseMst * PurchaseMstList::getObject(int index){
    return mstList->getObjectAtIndex(index);
}

PurchaseMst * PurchaseMstList::getObjectById(int Id){
    for( int i = 0; i < mstList->count(); i++ )
    {
        PurchaseMst* mst = mstList->getObjectAtIndex( i );
        
        if( mst->getId() == Id ) return mst;
    }
    
    return NULL;
}

