//
//  ParamList.cpp
//  BraveFrontier

//  Created by WillArk on 7/20/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "ParamList.h"
#include "CommonUtils.h"


ParamList* ParamListInstance = NULL;

/*
 * シングルトンインスタンスを取得。
 */
ParamList* ParamList::shared()
{
	if( ParamListInstance == NULL )
	{
		ParamListInstance= new ParamList();
	}

	return ParamListInstance;
}

/*
 * コンストラクタ。
 */
ParamList::ParamList()
{
	infoList = new CCMutableDictionary<string,CCString*>();
}

/*
 * デストラクタ。
 */
ParamList::~ParamList()
{
    infoList->release();
}

/*
 * オブジェクトの解放。
 */
void ParamList::removeAllObjects()
{
	infoList->removeAllObjects();
}

/*
 * 件数の取得。
 */
int ParamList::getCount()
{
	return infoList->count();
}


/*
 * 値の設定。
 */
void ParamList::setValue( string key, int value )
{
    string str = CommonUtils::IntToString( value );
    
    CCString* cstr = new CCString( str.c_str() );
    cstr->autorelease();
    
    setValue( key, cstr );
}

/*
 * 値の設定。
 */
void ParamList::setValue( string key, string value )
{
    CCString* cstr = new CCString( value.c_str() );
    cstr->autorelease();
    
    setValue( key, cstr );
}

/*
 * 値の設定。
 */
void ParamList::setValue( string key, CCString* value )
{
    infoList->removeObjectForKey( key );
    
    infoList->setObject( value, key );
}

/*
 * 値の取得。
 */
string ParamList::getValue( string key )
{
    CCString* cstr = infoList->objectForKey( key );
    if( !cstr ) return ""; 
    
    return cstr->m_sString;
}

/*
 * キーの取得。
 */
vector<string> ParamList::allKeys()
{
    return infoList->allKeys();
}

