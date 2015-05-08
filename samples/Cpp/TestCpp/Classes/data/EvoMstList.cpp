//
//  EvoMstList.cpp
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "EvoMstList.h"
#include "SQLiteManager.h"
EvoMstList* EvoMstListInstance = NULL;

/*
 * シングルトンインスタンスを取得。
 */
EvoMstList* EvoMstList::shared()
{
	if( EvoMstListInstance == NULL )
	{
		EvoMstListInstance= new EvoMstList();
        
        //读取sqlite
        CCArray * list = SQLiteManager::sharedInstance()->selectRows("select * from Evolution");
        for (int i=0; i<list->count(); i++) {
            EvoMst * EvoMst = new class EvoMst();
            EvoMst->initWithArray(dynamic_cast<CCDictionary*>(list->objectAtIndex(i)));
            EvoMstListInstance->addObject(EvoMst);
        }
	}

	return EvoMstListInstance;
}

/*
 * コンストラクタ。
 */
EvoMstList::EvoMstList()
{
	mstList = new CCMutableArray<EvoMst*>;
}

/*
 * デストラクタ。
 */
EvoMstList::~EvoMstList()
{

}

/*
 * オブジェクトの追加。
 */
void EvoMstList::addObject( EvoMst* mst )
{
	mstList->addObject( mst );
    mst->autorelease();
}

/*
 * オブジェクトの解放。
 */
void EvoMstList::removeAllObjects()
{
	mstList->removeAllObjects();
}

/*
 * 件数の取得。
 */
int EvoMstList::getCount()
{
	return mstList->count();
}

/*
 * オブジェクトを取得。
 */
EvoMst * EvoMstList::getObjectByBeforeId( int before_id )
{
    for( int i = 0; i < mstList->count(); i++ )
    {
        EvoMst* mst = mstList->getObjectAtIndex( i );
        
        if( mst->getBeforeId() == before_id ) return mst;
    }
    
    return NULL;
}

EvoMst * EvoMstList::getObject( int evo_id )
{
    for( int i = 0; i < mstList->count(); i++ )
    {
        EvoMst* mst = mstList->getObjectAtIndex( i );
        
        if( mst->getId() == evo_id ) return mst;
    }
    
    return NULL;
}




