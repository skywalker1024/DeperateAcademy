//
//  MissionMstList.cpp
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "MissionMstList.h"
#include "SQLiteManager.h"
MissionMstList* MissionMstListInstance = NULL;

/*
 * シングルトンインスタンスを取得。
 */
MissionMstList* MissionMstList::shared()
{
	if( MissionMstListInstance == NULL )
	{
		MissionMstListInstance= new MissionMstList();
        
        //读取sqlite
        CCArray * list = SQLiteManager::sharedInstance()->selectRows("select * from Mission");
        for (int i=0; i<list->count(); i++) {
            MissionMst * MissionMst = new class MissionMst();
            MissionMst->initWithArray(dynamic_cast<CCDictionary*>(list->objectAtIndex(i)));
            MissionMstListInstance->addObject(MissionMst);
        }
	}

	return MissionMstListInstance;
}

/*
 * コンストラクタ。
 */
MissionMstList::MissionMstList()
{
	mstList = new CCMutableArray<MissionMst*>;
}

/*
 * デストラクタ。
 */
MissionMstList::~MissionMstList()
{

}

/*
 * オブジェクトの追加。
 */
void MissionMstList::addObject( MissionMst* mst )
{
	mstList->addObject( mst );
    mst->autorelease();
}

/*
 * オブジェクトの解放。
 */
void MissionMstList::removeAllObjects()
{
	mstList->removeAllObjects();
}

/*
 * 件数の取得。
 */
int MissionMstList::getCount()
{
	return mstList->count();
}

/*
 * オブジェクトを取得。
 */
MissionMst* MissionMstList::getObject( int mission_id )
{
    for( int i = 0; i < mstList->count(); i++ )
    {
        MissionMst* mst = mstList->getObjectAtIndex( i );
        
        if( mst->getId() == mission_id ) return mst;
    }
    
    return NULL;
}





