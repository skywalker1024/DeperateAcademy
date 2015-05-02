//
//  SoldierMstList.cpp
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "SoldierMstList.h"
#include "SQLiteManager.h"
SoldierMstList* SoldierMstListInstance = NULL;

/*
 * シングルトンインスタンスを取得。
 */
SoldierMstList* SoldierMstList::shared()
{
	if( SoldierMstListInstance == NULL )
	{
		SoldierMstListInstance= new SoldierMstList();
        
        //读取sqlite
        CCArray * list = SQLiteManager::sharedInstance()->selectRows("select * from soldier");
        for (int i=0; i<list->count(); i++) {
            SoldierMst * soldierMst = new SoldierMst();
            soldierMst->initWithArray(dynamic_cast<CCDictionary*>(list->objectAtIndex(i)));
            SoldierMstListInstance->addObject(soldierMst);
        }
	}

	return SoldierMstListInstance;
}

/*
 * コンストラクタ。
 */
SoldierMstList::SoldierMstList()
{
	mstList = new CCMutableArray<SoldierMst*>;
}

/*
 * デストラクタ。
 */
SoldierMstList::~SoldierMstList()
{

}

/*
 * オブジェクトの追加。
 */
void SoldierMstList::addObject( SoldierMst* mst )
{
	mstList->addObject( mst );
    mst->autorelease();
}

/*
 * オブジェクトの解放。
 */
void SoldierMstList::removeAllObjects()
{
	mstList->removeAllObjects();
}

/*
 * 件数の取得。
 */
int SoldierMstList::getCount()
{
	return mstList->count();
}

/*
 * オブジェクトを取得。
 */
SoldierMst* SoldierMstList::getObject( int soldier_id )
{
    for( int i = 0; i < mstList->count(); i++ )
    {
        SoldierMst* mst = mstList->getObjectAtIndex( i );
        
        if( mst->getId() == soldier_id ) return mst;
    }
    
    return NULL;
}





