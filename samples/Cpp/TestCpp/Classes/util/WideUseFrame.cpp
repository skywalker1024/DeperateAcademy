//
//  WideUseFrame.cpp
//  BraveFrontier
//
//  Created by 本山 順一 on 13/01/22.
//
//

#include "WideUseFrame.h"
#include "CommonUtils.h"


/*
 * コンストラクタ。
 */
WideUseFrame::WideUseFrame()
{
    autorelease();
    
    // スプライトリスト
    spriteList = new CCMutableArray<GameSprite*>;
    
    
}

/*
 * デストラクタ。
 */
WideUseFrame::~WideUseFrame()
{
    spriteList->release();
}

/*
 *  初期化。
 */
WideUseFrame* WideUseFrame::init( CCLayer * layerid, float x, float y, float w, float h )
{
    
    WideUseFrame* frame = new WideUseFrame();
    
    frame->setLayerID( layerid );
    frame->setX( x );
    frame->setY( y );
    frame->setWidth( w );
    frame->setHeight( h );
    
    frame->createSprite();
    
    return frame;
}

/*
 * 描画処理。
 */
void WideUseFrame::draw()
{
    for( int i = 0; i < spriteList->count(); i++ )
    {
        GameSprite* sprite = spriteList->getObjectAtIndex( i );
        layerID->reEntry(sprite->getZOrder(), sprite);
    }
}

/*
 * 表示設定。
 */
void WideUseFrame::setIsVisible( bool value )
{
    for( int i = 0; i < spriteList->count(); i++ )
    {
        GameSprite* sprite = spriteList->getObjectAtIndex( i );
        
        sprite->setVisible( value );
    }
}

/*
 * ベースカラー設定
 */
void WideUseFrame::setBaseColor( ccColor3B color )
{
    baseSprite->setColor( color );
}


/*
 *  スプライト生成。
 */
void WideUseFrame::createSprite()
{
    // コーナーの丸くなっている分をすべてオフセットさせるため
    float offset = 25/2;
    
    // ベース
    {
        float frameWidth = 2;
        
        baseSprite = GameSprite::init( "img/wide_use/wide_use_frame_base.png" );
        
        baseSprite->setPosition( x+frameWidth, y+frameWidth );
        baseSprite->setSize( width-(frameWidth*2), height-(frameWidth/2) );
        baseSprite->setAnchorPoint( ccp( 0, 1 ) );
        baseSprite->setOpacity( 128 );
        spriteList->addObject( baseSprite );
    }
    
    // 縦枠
    {
        // 左
        {
            GameSprite* sprite = GameSprite::init( "img/wide_use/wide_use_frame_line_left.png" );

            sprite->setHeight( height-(offset*2) );
            sprite->setPosition( x, y+offset );
            sprite->setAnchorPoint( ccp( 0, 1 ) );
            spriteList->addObject( sprite );
        }
        
        // 右
        {            
            GameSprite* sprite = GameSprite::init( "img/wide_use/wide_use_frame_line_right.png" );
            
            sprite->setHeight( height-(offset*2) );
            sprite->setPosition( x+width, y+offset );
            sprite->setAnchorPoint( ccp( 1, 1 ) );
            spriteList->addObject( sprite );
        }
    }
    
    // 横枠
    {
        // 上
        {
            GameSprite* sprite = GameSprite::init( "img/wide_use/wide_use_frame_line_top.png" );
            
            sprite->setWidth( width-(offset*2) );
            sprite->setPosition( x+offset, y );
            sprite->setAnchorPoint( ccp( 0, 1 ) );
            spriteList->addObject( sprite );
        }
        
        // 下
        {
            GameSprite* sprite = GameSprite::init( "img/wide_use/wide_use_frame_line_bottom.png" );
            
            sprite->setWidth( width-(offset*2) );
            sprite->setPosition( x+offset, y+height );
            sprite->setAnchorPoint( ccp( 0, 0 ) );
            spriteList->addObject( sprite );
        }
    }
    
    // コーナー
    {
        // 左
        {
            // 上
            {
                GameSprite* sprite = GameSprite::init( "img/wide_use/wide_use_frame_corner_lt.png" );
                
                sprite->setPosition( x, y );
                sprite->setAnchorPoint( ccp( 0, 1 ) );
                spriteList->addObject( sprite );
            }
            
            // 下
            {
                GameSprite* sprite = GameSprite::init( "img/wide_use/wide_use_frame_corner_lb.png" );
                
                sprite->setPosition( x, y+height );
                sprite->setAnchorPoint( ccp( 0, 0 ) );
                spriteList->addObject( sprite );
            }
        }
        
        // 右
        {
            // 上
            {
                GameSprite* sprite = GameSprite::init( "img/wide_use/wide_use_frame_corner_rt.png" );
                
                sprite->setPosition( x+width, y );
                sprite->setAnchorPoint( ccp( 1, 1 ) );
                spriteList->addObject( sprite );
            }
            
            // 下
            {
                GameSprite* sprite = GameSprite::init( "img/wide_use/wide_use_frame_corner_rb.png" );
                
                sprite->setPosition( x+width, y+height );
                sprite->setAnchorPoint( ccp( 1, 0 ) );
                spriteList->addObject( sprite );
            }
        }
    }
}


/**
 * ｘ座標の取得。
 */
float WideUseFrame::getX()
{
	return x;
}

/*
 * ｘ座標の設定。
 */
void WideUseFrame::setX( float val )
{
	x = val;
}

/**
 * ｙ座標の取得。
 */
float WideUseFrame::getY()
{
	return y;
}

/*
 * ｙ座標の設定。
 */
void WideUseFrame::setY( float val )
{
	y = val;
}

/**
 * 幅の取得。
 */
float WideUseFrame::getWidth()
{
	return width;
}

/*
 * 幅の設定。
 */
void WideUseFrame::setWidth( float val )
{
	width = val;
}

/**
 * 高さの取得。
 */
float WideUseFrame::getHeight()
{
	return height;
}

/*
 * 高さの設定。
 */
void WideUseFrame::setHeight( float val )
{
	height = val;
}

/**
 * レイヤーIDの取得。
 */
CCLayer * WideUseFrame::getLayerID()
{
	return layerID;
}

/*
 * レイヤーIDの設定。
 */
void WideUseFrame::setLayerID( CCLayer * val )
{
	layerID = val;
}

