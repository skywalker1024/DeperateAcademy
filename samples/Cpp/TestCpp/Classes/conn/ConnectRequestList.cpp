//
//  ConnectRequestList.cpp
//  BraveFrontier

//  Created by WillArk on 11/21/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "ConnectRequestList.h"

ConnectRequestList* ConnectRequestListInstance = NULL;

/*
 * シングルトンインスタンスを取得。
 */
ConnectRequestList* ConnectRequestList::shared()
{
	if( ConnectRequestListInstance == NULL )
	{
		ConnectRequestListInstance= new ConnectRequestList();
	}

	return ConnectRequestListInstance;
}

/*
 * コンストラクタ。
 */
ConnectRequestList::ConnectRequestList()
{
	requestList = new CCMutableArray<BaseRequest*>;
}

/*
 * デストラクタ。
 */
ConnectRequestList::~ConnectRequestList()
{

}

/*
 * オブジェクトの追加。
 */
void ConnectRequestList::addObject( BaseRequest* info )
{
	requestList->addObject( info );
}

/*
 * オブジェクトの解放。
 */
void ConnectRequestList::removeAllObjects()
{
    CCLog( "ConnectRequestList::removeAllObjects()" );
    
	requestList->removeAllObjects();
}

/*
 * オブジェクトの解放。
 */
void ConnectRequestList::removeObject( BaseRequest* request )
{
    requestList->removeObject( request );
}

/*
 * 件数の取得。
 */
int ConnectRequestList::getCount()
{
	return requestList->count();
}

/*
 * オブジェクトを取得。
 */
BaseRequest* ConnectRequestList::getObject( int index )
{
	return requestList->getObjectAtIndex( index );
}


