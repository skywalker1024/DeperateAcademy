//
//  LevelMstList.cpp
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "LevelMstList.h"
#include "SQLiteManager.h"
LevelMstList* LevelMstListInstance = NULL;

/*
 * シングルトンインスタンスを取得。
 */
LevelMstList* LevelMstList::shared()
{
	if( LevelMstListInstance == NULL )
	{
		LevelMstListInstance= new LevelMstList();
        
        //读取sqlite
        CCArray * list = SQLiteManager::sharedInstance()->selectRows("select * from Level");
        for (int i=0; i<list->count(); i++) {
            LevelMst * LevelMst = new class LevelMst();
            LevelMst->initWithArray(dynamic_cast<CCDictionary*>(list->objectAtIndex(i)));
            LevelMstListInstance->addObject(LevelMst);
        }
	}

	return LevelMstListInstance;
}

/*
 * コンストラクタ。
 */
LevelMstList::LevelMstList()
{
	mstList = new CCMutableArray<LevelMst*>;
}

/*
 * デストラクタ。
 */
LevelMstList::~LevelMstList()
{

}

/*
 * オブジェクトの追加。
 */
void LevelMstList::addObject( LevelMst* mst )
{
	mstList->addObject( mst );
    mst->autorelease();
}

/*
 * オブジェクトの解放。
 */
void LevelMstList::removeAllObjects()
{
	mstList->removeAllObjects();
}

/*
 * 件数の取得。
 */
int LevelMstList::getCount()
{
	return mstList->count();
}

/*
 * オブジェクトを取得。
 */
LevelMst* LevelMstList::getObject( int lv )
{
    for( int i = 0; i < mstList->count(); i++ )
    {
        LevelMst* mst = mstList->getObjectAtIndex( i );
        
        if( mst->getLv() == lv ) return mst;
    }
    
    return NULL;
}

LevelMst* LevelMstList::getObjectByUnLockSoldierId( int soldier_id ){
    for( int i = 0; i < mstList->count(); i++ )
    {
        LevelMst* mst = mstList->getObjectAtIndex( i );
        
        if( mst->getUnlockSoldierId() == soldier_id ) return mst;
    }
    
    return NULL;
}

LevelMst* LevelMstList::getObjectByUnLockWallLv( int wall_lv ){
    for( int i = 0; i < mstList->count(); i++ )
    {
        LevelMst* mst = mstList->getObjectAtIndex( i );
        
        if( mst->getUnlockWallLv() == wall_lv ) return mst;
    }
    
    return NULL;
}




