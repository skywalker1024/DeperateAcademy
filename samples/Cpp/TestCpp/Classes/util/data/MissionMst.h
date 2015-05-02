//
//  MissionMst.h
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_MissionMst_h
#define BraveFrontier_MissionMst_h

#include "cocos2d.h"

USING_NS_CC;

class MissionMst : public CCObject
{
	public:
		// コンストラクタ
		MissionMst();
		// デストラクタ
		~MissionMst();
		// ミッションIDの取得
		string getMissionID();
		// ミッションIDの設定
		void setMissionID( string value );
		// ミッション名の取得
		string getMissionName();
		// ミッション名の設定
		void setMissionName( string value );
        // 大陸IDの設定
        void setLandID( string value );
        // 大陸IDの取得
        string getLandID();
		// エリアIDの取得
		string getAreaID();
		// エリアIDの設定
		void setAreaID( string value );
		// ダンジョンIDの取得
		string getDungeonID();
		// ダンジョンIDの設定
		void setDungeonID( string value );
		// 順番の取得
		int getDispOrder();
		// 順番の設定
		void setDispOrder( int value );
		// 難易度の取得
		int getDifficulty();
		// 難易度の設定
		void setDifficulty( int value );
		// 戦闘回数の取得
		int getBattleCnt();
		// 戦闘回数の設定
		void setBattleCnt( int value );
		// 消費行動力の取得
		int getUseActionP();
		// 消費行動力の設定
		void setUseActionP( int value );
		// 画像の取得
		string getImg();
		// 画像の設定
		void setImg( string value );
		// エフェクトタイプの取得
		int getEffectType();
		// エフェクトタイプの設定
		void setEffectType( int value );
		// 必須ミッションの取得
		string getNeedMissionID();
		// 必須ミッションの設定
		void setNeedMissionID( string value );
		// 説明の取得
		string getDescription();
		// 説明の設定
		void setDescription( string value );
        // ミミック情報の設定
        void setMimicInfo( string value );
        // ミミック情報の取得
        string getMimicInfo();
        // 通常戦闘BGMの取得
        string getBgmNormalBattle();
        // 通常戦闘BGMの設定
        void setBgmNormalBattle( string value );
        // ボス戦闘BGMの取得
        string getBgmBossBattle();
        // ボス戦闘BGMの設定
        void setBgmBossBattle( string value );    
        // 天候エフェクトの取得
        int getEffectWeather();
        // 天候エフェクトの設定
        void setEffectWeather( int value );
        // 特殊エフェクトの取得
        int getEffectSpecial();
        // 特殊エフェクトの設定
        void setEffectSpecial( int value );
        // 開始スクリプトの取得
        string getStartScript();
        // 開始スクリプトの設定
        void setStartScript( string value );
        // 終了スクリプトの取得
        string getEndScript();
        // 終了スクリプトの設定
        void setEndScript( string value );
        // 背景エフェクトの設定
        void setEffectBg( string value );
        // 背景エフェクトの取得
        string getEffectBg();
        // バトル背景画像の設定
        void setBattleBgImg( string value );
        // バトル背景画像の取得
        string getBattleBgImg();
    
	protected:

	private:
		// ミッションID
		string missionID;
		// ミッション名
		string missionName;
        // 大陸ID
        string landID;
		// エリアID
		string areaID;
		// ダンジョンID
		string dungeonID;
		// 順番
		int dispOrder;
		// 難易度
		int difficulty;
		// 戦闘回数
		int battleCnt;
		// 消費行動力
		int useActionP;
		// 画像
		string img;
		// エフェクトタイプ
		int effectType;
		// 必須ミッション
		string needMissionID;
		// 説明
		string description;
        // ミミック情報
        string mimicInfo;
        // 通常戦闘BGM
        string bgmNormalBattle;
        // ボス戦闘BGM
        string bgmBossBattle;
        // 天候エフェクト
        int effectWeather;
        // 特殊エフェクト
        int effectSpecial;
        // 開始スクリプト
        string startScript;
        // 終了スクリプト
        string endScript;
        // 背景エフェクト
        string effectBg;
        // バトル背景画像
        string battleBgImg;
        // コンティニューフラグ
        CC_SYNTHESIZE( bool, continueFlg, ContinueFlg );
    
    

};

#endif
