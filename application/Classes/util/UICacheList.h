//
//  UICacheList.h
//  BraveFrontier

//  Created by WillArk on 8/10/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_UICacheList_h
#define BraveFrontier_UICacheList_h

#include "cocos2d.h"
#include "UICache.h"
#include "ParticleAnime.h"
#include "GameSprite.h"
USING_NS_CC;

class UICacheList : public CCObject
{
public:
    
        // インスタンスの取得
        static UICacheList* shared();
        // コンストラクタ
        UICacheList();
        // デストラクタ
        ~UICacheList();
        // オブジェクトの解放
        void removeObject( UICache *pUICache );
      	// オブジェクトの解放
		void removeAllObjects();
		// 件数の取得
		int getCount();
        // スプライトを設定
        void setSprite( string group_id, string name, GameSprite* sprite );
        // 文字列ラベルを設定
        void setStringLabel( string group_id, string name, StringLabel* label );
        // 文字列ラベルリストを設定
        void setStringLabelList( string group_id, string name, StringLabelList* label );
        // 文字列を設定
        void setString( string group_id, string name, string str );
    
        // スプライトの取得
        GameSprite* getSprite( string group_id, string name );
        // スプライトのキャッシュを取得
        UICache* getSpriteCache( string key, string name );
        // 文字列ラベルの取得
        StringLabel* getStringLabel( string group_id, string name );
        // 文字列ラベルリストの取得
        StringLabelList* getStringLabelList( string group_id, string name );
        // 文字列を取得
        string getString( string group_id, string name );
    
        // 指定のデータが存在するか
        bool exist( string key );
        // 解放処理
        void remove( string key );
        // 文字列リストの解放
        void removeStringLabelList( string key, string name );
    
        // 表示設定
        void setIsVisible( string group_id, bool flg );
        // ポジションの取得
        CCPoint getPosition( string key );
        // ポジションの設定
        void setPosition( string key, CCPoint point );
        // int値の取得
        int getIntValue( string key );
        // int値のの設定
        void setIntValue( string key, int value );
        // パーティクルアニメの取得
        ParticleAnime* getParticleAnime( string key, string name );
        // パーティクルアニメの設定
        void setParticleAnime( string key, string name, ParticleAnime* anime );
        // スプライトバッチノードの設定
        void setBatchNode( string key, string name, CCSpriteBatchNode* value );
        // スプライトバッチノードの取得
        CCSpriteBatchNode* getBatchNode( string key, string name );

        // スプライトバッチノードの削除。
        void delCacheKey( string key );

	protected:

	private:
     	// キャッシュリスト
        typedef CCMutableDictionary<string, UICache*> CacheList;
		//CCMutableArray<UICache*> *cacheList;
        CacheList *cacheList;
        // キャッシュの取得
        UICache* getCache( string key );
    
};

#endif
