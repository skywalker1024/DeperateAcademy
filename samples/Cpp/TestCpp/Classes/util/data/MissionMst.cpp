//
//  MissionMst.cpp
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "MissionMst.h"
#include "GameUtils.h"
#include "CommonUtils.h"
#include "DungeonMstList.h"
#include "GameConst.h"

/*
 * コンストラクタ。
 */
MissionMst::MissionMst()
{
    landID = "";
    
    startScript = "";
    endScript = "";
    
    battleBgImg = "";
    
    continueFlg = true;
}

/*
 * デストラクタ。
 */
MissionMst::~MissionMst()
{

}

/**
 * ミッションIDの取得。
 */
string MissionMst::getMissionID()
{
	return missionID;
}

/*
 * ミッションIDの設定。
 */
void MissionMst::setMissionID( string val )
{
	missionID = val;
}

/**
 * ミッション名の取得。
 */
string MissionMst::getMissionName()
{
	return missionName;
}

/*
 * ミッション名の設定。
 */
void MissionMst::setMissionName( string val )
{
	missionName = val;
}

/*
 * 大陸IDの設定
 */
void MissionMst::setLandID( string value )
{
    landID = value;
}

/*
 * 大陸IDの取得
 */
string MissionMst::getLandID()
{
    return landID;
}

/**
 * エリアIDの取得。
 */
string MissionMst::getAreaID()
{
	return areaID;
}

/*
 * エリアIDの設定。
 */
void MissionMst::setAreaID( string val )
{
	areaID = val;
}

/**
 * ダンジョンIDの取得。
 */
string MissionMst::getDungeonID()
{
	return dungeonID;
}

/*
 * ダンジョンIDの設定。
 */
void MissionMst::setDungeonID( string val )
{
	dungeonID = val;
}

/**
 * 順番の取得。
 */
int MissionMst::getDispOrder()
{
	return dispOrder;
}

/*
 * 順番の設定。
 */
void MissionMst::setDispOrder( int val )
{
	dispOrder = val;
}

/**
 * 難易度の取得。
 */
int MissionMst::getDifficulty()
{
	return difficulty;
}

/*
 * 難易度の設定。
 */
void MissionMst::setDifficulty( int val )
{
	difficulty = val;
}

/**
 * 戦闘回数の取得。
 */
int MissionMst::getBattleCnt()
{
	return battleCnt;
}

/*
 * 戦闘回数の設定。
 */
void MissionMst::setBattleCnt( int val )
{
	battleCnt = val;
}

/**
 * 消費行動力の取得。
 */
int MissionMst::getUseActionP()
{
    DungeonMst* dungeonMst = DungeonMstList::shared()->getObjectWithDungeonID(this->getDungeonID());
    if (GameUtils::checkIsForceHalfStamina() && dungeonMst
        && dungeonMst->getDungeonType() != DUNGEON_TYPE_TRIAL)
    {
        int returnValue = (useActionP + 1) / 2;
        if (returnValue <= 0)
        {
            return 1;
        }
        else
        {
            return returnValue;
        }
    }
    
	return useActionP;
}

/*
 * 消費行動力の設定。
 */
void MissionMst::setUseActionP( int val )
{
	useActionP = val;
}

/**
 * 画像の取得。
 */

string MissionMst::getImg()
{
	return img;
}

/*
 * 画像の設定。
 */
void MissionMst::setImg( string val )
{
	img = val;
}

/**
 * エフェクトタイプの取得。
 */
int MissionMst::getEffectType()
{
	return effectType;
}

/*
 * エフェクトタイプの設定。
 */
void MissionMst::setEffectType( int val )
{
	effectType = val;
}

/**
 * 必須ミッションの取得。
 */
string MissionMst::getNeedMissionID()
{
	return needMissionID;
}

/*
 * 必須ミッションの設定。
 */
void MissionMst::setNeedMissionID( string val )
{
	needMissionID = val;
}

/**
 * 説明の取得。
 */
string MissionMst::getDescription()
{
	return description;
}

/*
 * 説明の設定。
 */
void MissionMst::setDescription( string val )
{
	description = val;
}

/*
 * ミミック情報の設定。
 */
void MissionMst::setMimicInfo( string value )
{
    mimicInfo = value;
}

/*
 * ミミック情報の取得。
 */
string MissionMst::getMimicInfo()
{
    return mimicInfo;
}

/**
 * 通常戦闘BGMの取得。
 */
string MissionMst::getBgmNormalBattle()
{
	return bgmNormalBattle;
}

/*
 * 通常戦闘BGMの設定。
 */
void MissionMst::setBgmNormalBattle( string val )
{
	bgmNormalBattle = val;
}

/**
 * ボス戦闘BGMの取得。
 */
string MissionMst::getBgmBossBattle()
{
	return bgmBossBattle;
}

/*
 * ボス戦闘BGMの設定。
 */
void MissionMst::setBgmBossBattle( string val )
{
	bgmBossBattle = val;
}

/*
 * 天候エフェクトの取得。
 */
int MissionMst::getEffectWeather()
{
    return effectWeather;
}

/*
 * 天候エフェクトの設定。
 */
void MissionMst::setEffectWeather( int value )
{
    effectWeather = value;
}


/*
 * 特殊エフェクトの取得。
 */
int MissionMst::getEffectSpecial()
{
    return effectSpecial;
}

/*
 * 特殊エフェクトの設定。
 */
void MissionMst::setEffectSpecial( int value )
{
    effectSpecial = value;
}



/**
 * 開始スクリプトの取得。
 */
string MissionMst::getStartScript()
{
	return startScript;
}

/*
 * 開始スクリプトの設定。
 */
void MissionMst::setStartScript( string val )
{
    if( val == "0" ) return;
    
	startScript = val;
}

/**
 * 終了スクリプトの取得。
 */
string MissionMst::getEndScript()
{
	return endScript;
}

/*
 * 終了スクリプトの設定。
 */
void MissionMst::setEndScript( string val )
{
    
    if( val == "0" ) return;

	endScript = val;
}

/*
 * 背景エフェクトの設定。
 */
void MissionMst::setEffectBg( string value )
{
    effectBg = value;
}

/*
 * 背景エフェクトの取得。
 */
string MissionMst::getEffectBg()
{
    return effectBg;
}

/*
 * バトル背景画像の設定。
 */
void MissionMst::setBattleBgImg( string value )
{
    battleBgImg = value;
}

/*
 * バトル背景画像の取得。
 */
string MissionMst::getBattleBgImg()
{
    return battleBgImg;
}





