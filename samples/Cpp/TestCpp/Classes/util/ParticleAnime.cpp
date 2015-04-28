//
//  ParticleAnime.cpp
//  BraveFrontier

//  Created by WillArk on 10/5/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "ParticleAnime.h"

/*
 * コンストラクタ。
 */
ParticleAnime::ParticleAnime()
{
    autorelease();
    
    isStart = false;
    waitFrame = 0;
    animeID = "";
    zOrder = 0;
    
    pauseFlg = false;
}

/*
 * デストラクタ。
 */
ParticleAnime::~ParticleAnime()
{
    //CCLog( "&&&&&delete ParticleAnime" );
}

/*
 * 生成処理。
 */

ParticleAnime* ParticleAnime::create( string path )
{
    ParticleAnime* anime = new ParticleAnime();
    
    CCLog( "ParticleAnime::create path=%s", path.c_str() );
    
    anime->initWithFile( path.c_str() );
    
    
    anime->path = path;
    
    return anime;
}


/*
 * 定期処理。
 */
void ParticleAnime::process()
{
    waitFrame--;
    
    if( waitFrame > 0 ) return;
    
    if( !isStart )
    {
        setAutoRemoveOnFinish( true );
        
        layerID->addChild( this, zOrder );
        
        isStart = true;
    }
    
    //CCLog( "particle path=%s", path.c_str() );
    
}

/**
 * 有効フラグの取得。
 */
bool ParticleAnime::getIsEnable()
{
    return isActive();
}

/**
 * 待機フレームの取得。
 */
int ParticleAnime::getWaitFrame()
{
	return waitFrame;
}

/*
 * 待機フレームの設定。
 */
void ParticleAnime::setWaitFrame( int val )
{
	waitFrame = val;
}

/**
 * アニメIDの取得。
 */
string ParticleAnime::getAnimeID()
{
	return animeID;
}

/*
 * アニメIDの設定。
 */
void ParticleAnime::setAnimeID( string val )
{
	animeID = val;
}

/**
 * 開始フラグの取得。
 */
bool ParticleAnime::getIsStart()
{
	return isStart;
}

/*
 * 開始フラグの設定。
 */
void ParticleAnime::setIsStart( bool val )
{
	isStart = val;
}



/*
 * レイヤーIDを設定。
 */
void ParticleAnime::setLayerID( CCLayer * value )
{
    layerID = value;
}

/*
 * 座標設定。
 */
void ParticleAnime::setPosition( float x, float y )
{
    cocos2d::CCNode::setPosition( CCDirector::sharedDirector()->convertToGL( ccp(x,y) ) );
}

/*
 * x座標の取得。
 */
float ParticleAnime::getAnimeX()
{
    CCPoint point = getPosition();
    
    return CCDirector::sharedDirector()->convertToUI( point ).x;
}

/*
 * y座標の取得。
 */
float ParticleAnime::getAnimeY()
{
    CCPoint point = getPosition();
    
    return CCDirector::sharedDirector()->convertToUI( point ).y;
    
}

/*
 * zオーダー設定。
 */
void ParticleAnime::setZorder( int value )
{
    zOrder = value;
}

/*
 * ポーズフラグを設定。
 */
void ParticleAnime::setPauseFlg( bool value )
{
    pauseFlg = value;
}

/*
 * ポーズフラグを取得。
 */
bool ParticleAnime::getPauseFlg()
{
    return pauseFlg;
}

/*
 * 削除処理
 */
void ParticleAnime::deleteAnime()
{
    setVisible( false );
    
    stopSystem();
}


