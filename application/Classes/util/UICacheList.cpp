//
//  UICacheList.cpp
//  BraveFrontier

//  Created by WillArk on 8/10/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "UICacheList.h"

UICacheList* UICacheListInstance = NULL;


/*
 * シングルトンインスタンスを取得。
 */
UICacheList* UICacheList::shared()
{
	if( UICacheListInstance == NULL )
	{
        
		UICacheListInstance= new UICacheList();
	}
    
	return UICacheListInstance;
}

/*
 * コンストラクタ。
 */
UICacheList::UICacheList()
{
    cacheList = new CCMutableDictionary<string, UICache*>();
}

/*
 * デストラクタ。
 */
UICacheList::~UICacheList()
{
    cacheList->release();
}

/*
 * オブジェクトの解放。
 */
void UICacheList::removeObject(UICache *pUICache)
{
    vector<string> keyArray = cacheList->allKeys();
    int size = keyArray.size();
    for(int i = 0; i < size; i++)
    {
        UICache *pTempCache = cacheList->objectForKey( keyArray[i] );
        if(pTempCache == pUICache)
        {
            cacheList->removeObjectForKey( keyArray[i] );
        }
    }
    
}

/*
 * オブジェクトの解放。
 */
void UICacheList::removeAllObjects()
{
	cacheList->removeAllObjects();
}

/*
 * 件数の取得。
 */
int UICacheList::getCount()
{
	return cacheList->count();
}

/*
 * 指定グループのデータが存在するか。
 */
bool UICacheList::exist( string key )
{

    if( cacheList->objectForKey( key ) ) return true;
    
    return false;
    
}

/*
 * 解放処理。
 */
void UICacheList::remove( string key )
{
    cacheList->removeObjectForKey( key );
    
}

/*
 * 文字列を設定。
 */
void UICacheList::setStringLabel( string key, string name, StringLabel* label )
{
    UICache* cache = getCache( key );
    
    cache->setStringLabel( name, label );
   
}

/*
 * 文字列リストを設定。
 */
void UICacheList::setStringLabelList( string key, string name, StringLabelList* list )
{
    UICache* cache = getCache( key );
    
    cache->setStringLabelList( name, list );
}

/*
 * 文字列リストの解放。
 */
void UICacheList::removeStringLabelList( string key, string name )
{
    UICache* cache = getCache( key );
    
    cache->removeStringLabelList( name );
}

/*
 * 文字列を設定。
 */
void UICacheList::setString( string key, string name, string str )
{
    UICache* cache = getCache( key );
    
    CCString* cstr = new CCString( str.c_str() );
    cstr->autorelease();
    
    cache->setStringObject( name, cstr );
}

/*
 * スプライトを設定。
 */
void UICacheList::setSprite( string key, string name, GameSprite* sprite )
{
    UICache* cache = getCache( key );
    
    cache->setSprite( name, sprite );
}
/*
 * スプライトの取得。
 */
GameSprite*  UICacheList::getSprite( string key, string name )
{
    if( !exist( key) ) return NULL;
    
    UICache* cache = getCache( key );
    
    return cache->getSprite( name );
}

/*
 * スプライトの取得。
 */
UICache* UICacheList::getSpriteCache( string key, string name )
{
    if( !exist( key) ) return NULL;
    
    UICache* cache = getCache( key );
    
    return cache;
}


/*
 * 文字列の取得。
 */
StringLabel* UICacheList::getStringLabel( string key, string name )
{
    if( !exist( key) ) return NULL;
    
    UICache* cache = getCache( key );
    
    return cache->getStringLabel( name );

}

/*
 * 文字列リストの取得。
 */
StringLabelList* UICacheList::getStringLabelList( string key, string name )
{
    if( !exist( key) ) return NULL;
 
    UICache* cache = getCache( key );
    
    return cache->getStringLabelList( name );
  
}

/*
 * 文字列を取得。
 */
string UICacheList::getString( string key, string name )
{
    if( !exist( key) ) return "";
    
    UICache* cache = getCache( key );
    
    CCString* cstr = cache->getStringObject( name );
    if( !cstr ) return "";
    
    return cstr->m_sString;
}


/*
 * 表示設定。
 */
void UICacheList::setIsVisible( string key, bool flg )
{
    if( !exist( key) ) return;
    
    UICache* cache = getCache( key );
    
    cache->setIsVisible( flg );
    
    
}

/*
 * ポジションの取得。
 */
CCPoint UICacheList::getPosition( string key )
{
    if( !exist( key) ) return ccp( 0, 0 );
    
    UICache* cache = getCache( key );
    
    return cache->getPosition();
}

/*
 * レイヤーポジションの設定。
 */
void UICacheList::setPosition( string key, CCPoint point )
{
    
    UICache* cache = getCache( key );
    
    cache->setPosition( point );
   
}

/*
 * int値の取得。
 */
int UICacheList::getIntValue( string key )
{
    if( !exist( key) ) return 0;
    
    UICache* cache = getCache( key );
    
    return cache->getIntValue();
}

/*
 * int値の設定。
 */
void UICacheList::setIntValue( string key, int value )
{
    UICache* cache = getCache( key );   
    
    cache->setIntValue( value );
}
/*
 * パーティクルアニメの取得。
 */
ParticleAnime* UICacheList::getParticleAnime( string key, string name )
{
    if( !exist( key ) ) return NULL;
    
    UICache* cache = getCache( key );
    
    return cache->getParticleAnime( name );
}

/*
 * パーティクルアニメの設定。
 */
void UICacheList::setParticleAnime( string key, string name, ParticleAnime* anime )
{
    UICache* cache = getCache( key );
    
    cache->setParticleAnime( name, anime );

}


/*
 * キャッシュの取得。
 */
UICache* UICacheList::getCache( string key )
{
    UICache* cache = cacheList->objectForKey( key );
    
    if( cache ) return cache;
    
    cache = new UICache();
    cacheList->setObject( cache, key );
    
    return cache;
    
}
/*
 * スプライトバッチノードの設定。
 */
void UICacheList::setBatchNode( string key, string name, CCSpriteBatchNode* value )
{
    UICache* cache = getCache( key );

    cache->setBatchNode( name, value );

}

/*
 * スプライトバッチノードの取得。
 */
CCSpriteBatchNode* UICacheList::getBatchNode( string key, string name )
{
    if( !exist( key ) ) return NULL;
    
    UICache* cache = getCache( key );
    
    return cache->getBatchNode( name );

}
/*
 * スプライトバッチノードの削除。
 */
void UICacheList::delCacheKey( string key )
{
    if( !exist( key ) ) return;
    
    cacheList->removeObjectForKey( key );
}


