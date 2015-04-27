//
//  UICache.cpp
//  BraveFrontier

//  Created by WillArk on 8/10/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "UICache.h"

/*
 * コンストラクタ。
 */
UICache::UICache()
{
    autorelease();
    
    stringLabelList = new CCMutableDictionary<string, StringLabel*>();
    stringLabelListEx = new CCMutableDictionary<string, StringLabelList*>();
    particleAnimeList = new CCMutableDictionary<string, ParticleAnime*>();
    batchNodeList = new CCMutableDictionary<string, BatchNodeObject*>();
    stringList = new CCMutableDictionary<string,CCString*>();
}

/*
 * デストラクタ。
 */
UICache::~UICache()
{
    
    stringLabelList->release();
    stringLabelListEx->release();
    spriteList->release();
    particleAnimeList->release();
    stringList->release();
    
    // バッチノードの解放
    {
        vector<string>all_keys = batchNodeList->allKeys();
        
        for( int i = 0; i < batchNodeList->count(); i++ )
        {
            BatchNodeObject* node = batchNodeList->objectForKey( all_keys[i] );
            if( !node ) continue;
            
            node->getBatchNode()->removeAllChildrenWithCleanup( true );
        }
        
        batchNodeList->release();
    }
}

/**
 * スプライトの取得。
 */
GameSprite* UICache::getSprite( string key )
{
    
    
    return spriteList->objectForKey( key );
}

/*
 * スプライトの設定。
 */
void UICache::setSprite( string key, GameSprite* val )
{
    spriteList->removeObjectForKey( key );
    
    spriteList->setObject( val, key );
}


/**
 * 文字列の取得。
 */
StringLabel* UICache::getStringLabel( string key )
{
    return stringLabelList->objectForKey( key );
}

/*
 * 文字列の設定。
 */
void UICache::setStringLabel( string key, StringLabel* val )
{
    stringLabelList->removeObjectForKey( key );
    stringLabelList->setObject( val, key );
}
/**
 * 文字列リストの取得。
 */
StringLabelList* UICache::getStringLabelList( string key )
{
	return stringLabelListEx->objectForKey( key );
}

/*
 * 文字列リストの設定。
 */
void UICache::setStringLabelList( string key, StringLabelList* val )
{
    
    stringLabelListEx->removeObjectForKey( key );
    stringLabelListEx->setObject( val, key );
}

/*
 * 文字列の解放。
 */
void UICache::removeStringLabelList( string key  )
{
    stringLabelListEx->removeObjectForKey( key );
}

/*
 * レイヤーポジションの取得。
 */
CCPoint UICache::getPosition()
{
    return position;
}

/*
 * レイヤーポジションの設定。
 */
void UICache::setPosition( CCPoint val )
{
    position = val;
}

/*
 * int値の取得。
 */
int UICache::getIntValue()
{
    return intValue; 
}

/*
 * int値のの設定。
 */
void UICache::setIntValue( int value )
{
    intValue = value;
}
/*
 * パーティクルアニメの取得。
 */
ParticleAnime* UICache::getParticleAnime( string key )
{
    return particleAnimeList->objectForKey( key );
}

/*
 * パーティクルアニメの設定。
 */
void UICache::setParticleAnime( string key, ParticleAnime* anime )
{
    particleAnimeList->removeObjectForKey( key );
    particleAnimeList->setObject( anime, key );
}
/*
 * スプライトバッチノードの設定。
 */
void UICache::setBatchNode( string key, CCSpriteBatchNode* value )
{
    BatchNodeObject* node = new BatchNodeObject();
    node->setBatchNode( value );
    node->setStartRetainCnt( value->retainCount() );
    
    batchNodeList->removeObjectForKey( key );
    batchNodeList->setObject( node, key );
}

/*
 * スプライトバッチノードの取得。
 */
CCSpriteBatchNode* UICache::getBatchNode( string key )
{
    BatchNodeObject* node = batchNodeList->objectForKey( key );
    
    return node->getBatchNode();
    
}
/*
 * 文字列オブジェクトの設定。
 */
void UICache::setStringObject( string key, CCString* str )
{
    stringList->removeObjectForKey( key );
    stringList->setObject( str, key );
}

/*
 * 文字列オブジェクトの取得。
 */
CCString* UICache::getStringObject( string key )
{
    return stringList->objectForKey( key );
}


/*
 * 表示設定。
 */
void UICache::setIsVisible( bool flg )
{
    // 文字列の表示設定
    {
        vector<string> keys = stringLabelList->allKeys();
        
        for( int i = 0; i < keys.size(); i++ )
        {
            StringLabel* value = stringLabelList->objectForKey( keys[i] );
            
            value->setVisible( flg );
        }
    } 
    
     // 文字列リストの表示設定
    {
        vector<string> keys = stringLabelListEx->allKeys();
        
        for( int i = 0; i < keys.size(); i++ )
        {
            StringLabelList* value = stringLabelListEx->objectForKey( keys[i] );
            
            value->setIsVisible( flg );
        }
    } 
    
    // スプライトの表示設定
    {
        vector<string> keys = spriteList->allKeys();
        
        for( int i = 0; i < keys.size(); i++ )
        {
            GameSprite* value = spriteList->objectForKey( keys[i] );
            
            value->setVisible( flg );
        }
    }
}



