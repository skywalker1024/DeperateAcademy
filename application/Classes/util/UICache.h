//
//  UICache.h
//  BraveFrontier

//  Created by WillArk on 8/10/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_UICache_h
#define BraveFrontier_UICache_h

#include "cocos2d.h"
#include "StringLabel.h"
#include "StringLabelList.h"
#include "ParticleAnime.h"
#include "GameSprite.h"
USING_NS_CC;

class UICache : public CCObject
{
	public:
		// コンストラクタ
		UICache();
		// デストラクタ
		~UICache();
		// スプライトの取得
		GameSprite* getSprite( string key );
		// スプライトの設定
		void setSprite( string key, GameSprite* value );

		// 文字列の取得
		StringLabel* getStringLabel( string key );
		// 文字列の設定
		void setStringLabel( string key, StringLabel* value );
        // 文字列の取得
        StringLabelList* getStringLabelList( string key );
        // 文字列の設定
        void setStringLabelList( string key, StringLabelList* value );
        // 文字列の解放
        void removeStringLabelList( string key  );
    
        // ポジションの取得
        CCPoint getPosition();
        // ポジションの設定
        void setPosition( CCPoint point );
        // 表示設定
        void setIsVisible( bool flg );
        // int値の取得
        int getIntValue();
        // int値のの設定
        void setIntValue( int value );
        // パーティクルアニメの取得
        ParticleAnime* getParticleAnime( string key );
        // パーティクルアニメの設定
        void setParticleAnime( string key, ParticleAnime* anime );
    
        // スプライトバッチノードの設定
        void setBatchNode( string key, CCSpriteBatchNode* value );
        // スプライトバッチノードの取得
        CCSpriteBatchNode* getBatchNode( string key );
    
        // 文字列オブジェクトの設定
        void setStringObject( string key, CCString* str );
        // 文字列オブジェクトの取得
        CCString* getStringObject( string key );

    
    
        // CCSpriteBatchNodeをラップするクラス
        class BatchNodeObject : public CCObject
        {
            public:
            
                BatchNodeObject()
                {
                    batchNode = NULL;
                    
                    autorelease();
                }
            
                ~BatchNodeObject()
                {
                    if( batchNode )
                    {
                        batchNode->release();
                    }
                }
                    
                void setBatchNode( CCSpriteBatchNode* node )
                {
                    batchNode = node;
                    batchNode->retain();
                }

                CCSpriteBatchNode* getBatchNode()
                {
                    return batchNode;
                }
            
                void setStartRetainCnt( int value )
                {
                    startRetainCnt = value;
                }
            
                int getStartRetainCnt()
                {
                    return startRetainCnt;
                }
            
            private:
                // バッチノードオブジェクト
                CCSpriteBatchNode* batchNode;
                // 参照カウンタ数
                int startRetainCnt;
        };
    
	protected:

	private:
        // ポジション
        CCPoint position;
        // int値
        int intValue;
    
        CCMutableDictionary<string, StringLabel*> *stringLabelList;
        CCMutableDictionary<string, GameSprite*> *spriteList;
        CCMutableDictionary<string, StringLabelList*> *stringLabelListEx;
        CCMutableDictionary<string, ParticleAnime*> *particleAnimeList;
        CCMutableDictionary<string, BatchNodeObject*> *batchNodeList;
        CCMutableDictionary<string, CCString*> *stringList;
    
    
    
    
     

};

#endif
