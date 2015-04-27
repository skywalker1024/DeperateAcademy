//
//  ParticleAnime.h
//  BraveFrontier

//  Created by WillArk on 10/5/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_ParticleAnime_h
#define BraveFrontier_ParticleAnime_h

#include "cocos2d.h"

USING_NS_CC;

class ParticleAnime : public CCParticleSystemQuad
{
	public:
		// コンストラクタ
		ParticleAnime();
		// デストラクタ
		~ParticleAnime();
        // 生成処理
        static ParticleAnime* create( string path );
		// 有効フラグの取得
		bool getIsEnable();
		// 待機フレームの取得
		int getWaitFrame();
		// 待機フレームの設定
		void setWaitFrame( int value );
		// アニメIDの取得
		string getAnimeID();
		// アニメIDの設定
		void setAnimeID( string value );
		// 開始フラグの取得
		bool getIsStart();
		// 開始フラグの設定
		void setIsStart( bool value );
        // x座標の取得
        float getAnimeX();
        // y座標の取得
        float getAnimeY();
        // 定期処理
        void process();
        // レイヤーIDを設定
        void setLayerID( CCLayer * value );
        // 座標設定
        void setPosition( float x, float y );
        // zオーダー設定
        void setZorder( int value );
        // ポーズフラグを設定
        void setPauseFlg( bool value );
        // ポーズフラグを取得
        bool getPauseFlg();
        // 削除処理
        void deleteAnime();
    
    
	protected:

	private:
        // レイヤーID
        CCLayer * layerID;
		// 待機フレーム
		int waitFrame;
		// アニメID
		string animeID;
		// 開始フラグ
		bool isStart;
        // ファイルパス
        string path;
        // Zオーダー
        int zOrder;
        // ポーズフラグ
        bool pauseFlg;
    
};

#endif

