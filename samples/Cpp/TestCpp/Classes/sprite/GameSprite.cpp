//
//  GameSprite.cpp
//  SampleGame2
//
//  Created by 杉山 浩 on 12/03/24.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include "GameSprite.h"
#include "CommonUtils.h"

/*
 * コンストラクタ。 
 */

GameSprite::GameSprite()
{

    
    this->autorelease();
    
    fileName = "";
    
    mngID = "";
    spx = 0;
    spy = 0;
    
    compParam1 = 0;
    compParam2 = 0;

    /*
    if (!CCDirector::sharedDirector()->enableRetinaDisplay(true))
    {
        setScale( 0.5 );
    }
    */
    
    //initWithTexture(cocos2d::CCTexture2D *pTexture, const cocos2d::CCRect &rect)
    
    //initWithTexture(cocos2d::CCTexture2D *pTexture)
    
    setScale( 1.0 );
    
    //setTag( 0 );
    
    // アニメスプライト初期化
    animeSprite = NULL;
    
    deafaultOpacity = 255;
    
    layerId = 0;
}

/*
bool GameSprite::initWithTexture(CCTexture2D *pTexture )
{
    return CCSprite::initWithTexture( pTexture );
}
*/


/*
 * デストラクタ。
 */

GameSprite::~GameSprite()
{
    
    if( !fileName.empty() )
    {
        CCLog("delete GameSprite fileName=%s", fileName.c_str() );
    }

}

/*
 * スプライトの生成。
 * spriteId:スプライトID。
 * fileName:ファイル名。
 */
GameSprite* GameSprite::init( const char *file )
{
    
    GameSprite *sprite = new GameSprite();
    sprite->initWithFile( file );
    
    sprite->fileName = string( file );
    
    //GameSprite *sprite = static_cast<GameSprite*>(CCSprite::spriteWithFile(fileName));
    
    if (!sprite)
    {
        CCLog( "sprite=null" );
    }
    
    // 表示基準位置を左上に
    sprite->setAnchorPoint( ccp( 0, 1 ) );

    return sprite;
}

/*
 * スプライトの生成。
 * spriteId:スプライトID。
 * fileName:ファイル名。
 * rect:切り出し領域。
 */
GameSprite* GameSprite::init( CCTexture2D *texture, CCRect rect )
{
    
    CCRect srect = rect;
    
    
    GameSprite *sprite = new GameSprite();
    sprite->initWithTexture( texture, srect );
   
    
    return sprite;
}

/*
 * スプライトの生成。
 */
GameSprite* GameSprite::initWithFrameName( string name )
{
    GameSprite *sprite = new GameSprite();
    sprite->initWithSpriteFrameName( name.c_str() );
    
    // 表示基準位置を左上に
    sprite->setAnchorPoint( ccp( 0, 1 ) );

    return sprite;
}


/*
 * リソースからスプライトの生成。
 */
/*
GameSprite* GameSprite::initForResource( const char *filename)
{
    return init( CommonUtils::getResourcePath( filename ) );

}
*/

/*
 * ローカルからスプライトの生成。
 */
/*
GameSprite* GameSprite::initForLocal( const char *filename)
{
    return init( CommonUtils::getLocalPath( filename ) );
}
*/


/*
 * スプライトの生成。
 * spriteId:スプライトID。
 * texture:テクスチャ。
 */
GameSprite* GameSprite::init( CCTexture2D *texture )
{
    GameSprite *sprite = new GameSprite();
    sprite->CCSprite::initWithTexture( texture );

    //GameSprite *sprite = static_cast<GameSprite*>(CCSprite::spriteWithTexture( texture ) );
    
    // 表示基準位置を左上に
    sprite->setAnchorPoint( ccp( 0, 1 ) );
    
    return sprite;
}




/*
 * スプライトをサイズ指定で生成。
 */
GameSprite* GameSprite::initWithSize( CCTexture2D *texture, float w, float h )
{
    GameSprite *sprite = init( texture );
    
    if( w != sprite->getWidth() )
    {
        sprite->setScaleX( w / sprite->getWidth() );
    }
    
    if( h != sprite->getHeight() )
    {
        sprite->setScaleY( h / sprite->getHeight() );
    }
    
    return sprite;

}

/*
 * 幅の設定。
 */
void GameSprite::setWidth( float w )
{
    CCSize size = getContentSize();
    
    if( w != size.width )
    {
        setScaleX( w / size.width );
    }

}

/*
 * 高さの設定。
 */
void GameSprite::setHeight( float h )
{

    CCSize size = getContentSize();
    
    if( h != size.height )
    {
        setScaleY( h / size.height );
    }
}


/*
 * 幅高さの設定。
 */
void GameSprite::setSize( float w, float h )
{
    setWidth( w );
    setHeight( h );
}

/*
 * GL x座標を取得。
 */
int GameSprite::getGlPositionX()
{
    return getPosition().x;
}

/*
 * GL y座標を取得。
 */
int GameSprite::getGlPositionY()
{
    return getPosition().y;
}

/*
 * x座標を取得。
 */
float GameSprite::getPositionX()
{
    
    return CCDirector::sharedDirector()->convertToUI( getPosition() ).x;
    
    //return spx;
}

/*
 * y座標を取得。
 */
float GameSprite::getPositionY()
{
    return CCDirector::sharedDirector()->convertToUI( getPosition() ).y;

    //return spy;
}

/*
 * 幅取得
 */
int GameSprite::getWidth()
{
    return getContentSize().width * getScaleX();
}

/*
 * 高さ取得
 */
int GameSprite::getHeight()
{
    return getContentSize().height * getScaleY();
}

/*
 * Left座標取得
 */
int GameSprite::getLeft()
{
    return getPosition().x - ( getWidth() / 2 );
}

/*
 * Top座標取得
 */
int GameSprite::getTop()
{
    return getPosition().y - ( getHeight() / 2 );  
}

/*
 * 座標の設定。
 * x:x座標。
 * y:y座標。
 */
void GameSprite::setPosition( float x, float y )
{
    spx = x;
    spy = y;
    
    CCSprite::setPosition( ccp( spx, spy ) );
}

/*
 * 座標の設定。
 * x:x座標。
 */
void GameSprite::setPositionX( float x )
{
    spx = x;
    
     CCSprite::setPosition( ccp( spx, spy ) );
}

/*
 * 座標の設定。
 * y:y座標。
 */
void GameSprite::setPositionY( float y )
{
    spy = y;
    
    CCSprite::setPosition( ccp( spx, spy ) );
}

/*
 * 座標の加算。
 * x:加算x座標。
 * y:加算y座標。
 */
void GameSprite::incPosition( float x, float y )
{
    spx += x;
    spy += y;
    
    CCSprite::setPosition( ccp( spx, spy ) );
 }


/**
 * スプライトIDの取得。
 */
/*
int GameSprite::getSpriteId()
{
    return spriteId;    
}
*/

/**
 * レイヤーIDの設定。
 */
void GameSprite::setLayerId( int value )
{
    layerId = value;
}

/**
 * レイヤーIDの取得。
 */
int GameSprite::getLayerId()
{
    return layerId;
}

/*
 * カラーをクリア。
 */
void GameSprite::clearColor()
{
    setColor( ccc3(255,255,255) ); 
}

/*
 * 管理IDを設定。
 */

void GameSprite::setMngID( string value )
{
    mngID = value;
}


/*
 * 管理IDを取得。
 */

string GameSprite::getMngID()
{
    return mngID;
}

/*
 * マスクを設定。
 */
void GameSprite::setMask()
{
    setColor( ccc3(100,100,100) );
}

/*
 * マスクをクリア。
 */
void GameSprite::clearMask()
{
    clearColor();
}

void GameSprite::setCachePos()
{
    cachePos = CCPoint( getPositionX(), getPositionX() );
}

float GameSprite::getCachePosX()
{
    return cachePos.x;
}

float GameSprite::getCachePosY()
{
    return cachePos.y;
}

/*
 * アニメスプライトを設定
 */
void GameSprite::setAnimeSprite( GameSprite* sprite )
{
    animeSprite = sprite;
}

/*
 * アニメスプライトを取得
 */
GameSprite* GameSprite::getAnimeSprite()
{
    return animeSprite;
}

void GameSprite::setFileName( string name )
{
    fileName = name;
}


string GameSprite::getFileName()
{
    return fileName;
    
}
/*
void GameSprite::draw()
{
    CCSprite::draw();
    CCLog( "GameSprite::draw()" );
    
    //ccGLBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    
}
*/

/*
 * デフォルトの透明度設定。
 */
void GameSprite::setDefaultOpacity( int value )
{
    deafaultOpacity = value;
}

/*
 * デフォルトの透明度取得。
 */
int GameSprite::getDefaultOpacity()
{
    return deafaultOpacity;
}

CCRect GameSprite::getRect(){
    // ノードの短形を取得
    float left = cocos2d::CCNode::getPositionX();
    float bottom = cocos2d::CCNode::getPositionY();
    

    // 幅、高さを取得（拡大率も含める）
    float width = getContentSize().width;
    float height = getContentSize().height;
    
    width *= getScaleX();
    height *= getScaleY();
    
    CCPoint anc = getAnchorPoint();
    
    // 左上基準で判定
    if( anc.x == 0.5 ) left -= width / 2;
    if( anc.x == 1.0 ) left -= width;
    if( anc.y == 0.5 ) bottom  -= height / 2;
    if( anc.y == 1.0 ) bottom  -= height;
    
    
    // GLの座標系なので高さを変換
    CCRect rect = CCRectMake( left, bottom , width, height );
    CCLog("GameSprite::getRect x=%f y=%f width=%f height=%f", left, bottom, width, height);
    return rect;
}


