//
//  WallMstList.cpp
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "WallMstList.h"
#include "SQLiteManager.h"
WallMstList* WallMstListInstance = NULL;

/*
 * シングルトンインスタンスを取得。
 */
WallMstList* WallMstList::shared()
{
	if( WallMstListInstance == NULL )
	{
		WallMstListInstance= new WallMstList();
        
        //读取sqlite
        CCArray * list = SQLiteManager::sharedInstance()->selectRows("select * from wall_mst");
        for (int i=0; i<list->count(); i++) {
            WallMst * WallMst = new class WallMst();
            WallMst->initWithArray(dynamic_cast<CCDictionary*>(list->objectAtIndex(i)));
            WallMstListInstance->addObject(WallMst);
        }
	}

	return WallMstListInstance;
}

/*
 * コンストラクタ。
 */
WallMstList::WallMstList()
{
	mstList = new CCMutableArray<WallMst*>;
}

/*
 * デストラクタ。
 */
WallMstList::~WallMstList()
{

}

/*
 * オブジェクトの追加。
 */
void WallMstList::addObject( WallMst* mst )
{
	mstList->addObject( mst );
    mst->autorelease();
}

/*
 * オブジェクトの解放。
 */
void WallMstList::removeAllObjects()
{
	mstList->removeAllObjects();
}

/*
 * 件数の取得。
 */
int WallMstList::getCount()
{
	return mstList->count();
}

/*
 * オブジェクトを取得。
 */
WallMst* WallMstList::getObject( int lv )
{
    for( int i = 0; i < mstList->count(); i++ )
    {
        WallMst* mst = mstList->getObjectAtIndex( i );
        
        if( mst->getLv() == lv ) return mst;
    }
    
    return NULL;
}




