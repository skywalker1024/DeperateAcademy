//
//  ParticleAnimeList.h
//  BraveFrontier

//  Created by WillArk on 10/5/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_ParticleAnimeList_h
#define BraveFrontier_ParticleAnimeList_h

#include "cocos2d.h"
#include "ParticleAnime.h"

USING_NS_CC;

class ParticleAnimeList : public CCObject
{
	public:
		// インスタンスの取得
		static ParticleAnimeList* shared();
		// アニメを設定
		void addAnime( ParticleAnime* info);
		// アニメを解放
		void removeAllAnime();
        void removeAnime( ParticleAnime* anime );
		// 件数の取得
		int getCount();
		// オブジェクトの取得
		ParticleAnime* getObject( int index );
        // 存在チェック
        bool exist( string anime_id, float x, float y, int wait );
        // 定期処理
        void process();
        // ポーズ処理
        void pause();
        // レジューム処理
        void resume();
    
        // add by pengchao.ye
    CC_SYNTHESIZE(bool, m_removeFlg, RemoveFlg);
    
	protected:

	private:
		// コンストラクタ
		ParticleAnimeList();
		// デストラクタ
		~ParticleAnimeList();
		// infoリスト
		CCMutableArray<ParticleAnime*> *animeList;

};

#endif

