//
//  MissionMstList.cpp
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "MissionMstList.h"
#include "PermitPlaceInfoList.h"

MissionMstList* MissionMstListInstance = NULL;

/*
 * シングルトンインスタンスを取得。
 */
MissionMstList* MissionMstList::shared()
{
	if( MissionMstListInstance == NULL )
	{
		MissionMstListInstance= new MissionMstList();
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
MissionMst* MissionMstList::getObject( int index )
{
	return mstList->getObjectAtIndex( index );
}

/*
 * オブジェクトを取得。
 */
MissionMst* MissionMstList::getObjectWithMissionID( string mission_id )
{
    for( int i = 0; i < mstList->count(); i++ )
    {
        MissionMst* mst = mstList->getObjectAtIndex( i );
        
        if( mst->getMissionID() == mission_id ) return mst;
    }
    
    return NULL;
}

/*
 * ミッションリストの取得。
 * dungeon_id:ダンジョンID。
 */
CCMutableArray<MissionMst*>* MissionMstList::getMissionListWithDungeonID( string dungeon_id )
{
    CCMutableArray<MissionMst*> *relist = new CCMutableArray<MissionMst*>;
    relist->autorelease();
    
    for( int i = 0; i < mstList->count(); i++ )
    {
        MissionMst* mst = mstList->getObjectAtIndex( i );
        
        if( mst->getDungeonID() != dungeon_id ) continue;
        // 有効でない場合
        if( !PermitPlaceInfoList::shared()->isPermitMission( mst->getMissionID() ) ) continue;
        
        relist->addObject( mst );
    }
    
    return relist;
}

/*
 * ミッションリストの取得。
 * dungeon_id:ダンジョンID。
 */
CCMutableArray<MissionMst*>* MissionMstList::getMissionListWithDungeonIDAll( string dungeon_id )
{
    CCMutableArray<MissionMst*> *relist = new CCMutableArray<MissionMst*>;
    relist->autorelease();
    
    for( int i = 0; i < mstList->count(); i++ )
    {
        MissionMst* mst = mstList->getObjectAtIndex( i );
        
        if( mst->getDungeonID() != dungeon_id ) continue;

        relist->addObject( mst );
    }
    
    return relist;
}







