//
//  ArenaInfoList.cpp
//  BraveFrontier

//  Created by WillArk on 5/10/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "ArenaInfoList.h"
#include "CommonUtils.h"
// シングルトンインスタンス
ArenaInfoList* ArenaInfoListInstance = NULL;

/**
 * シングルトンインスタンスを取得。
 */
ArenaInfoList* ArenaInfoList::shared()
{
    if( ArenaInfoListInstance == NULL )
    {
        ArenaInfoListInstance = new ArenaInfoList();
    }
    
    return ArenaInfoListInstance;
}

/*
 * コンストラクタ。
 */
ArenaInfoList::ArenaInfoList()
{
    arenaList = new CCMutableArray<ArenaInfo*>;
}

/*
 * デストラクタ。
 */
ArenaInfoList::~ArenaInfoList()
{
    
}

/*
 * オブジェクトの追加。
 */
void ArenaInfoList::addObject( ArenaInfo* info )
{
    arenaList->addObject( info );
    info->autorelease();
}

/*
 * オブジェクトの解放。
 */
void ArenaInfoList::removeAllObjects()
{
    arenaList->removeAllObjects();
}

/*
 * 件数の取得。
 */
int ArenaInfoList::getCount()
{
    return arenaList->count();
}

/*
 * オブジェクトを取得。
 */
ArenaInfo* ArenaInfoList::getObject( int index )
{
    if (index < arenaList->count()) {
        return arenaList->getObjectAtIndex(index);
    }
    
    return NULL;
}

void ArenaInfoList::updateWithJson(Json::Value json){
    removeAllObjects();
    for (int i=0; i<json.size(); i++) {
        ArenaInfo * info = new ArenaInfo();
        info->updateWithJson(json[i]);
        addObject(info);
    }
}