//
//  GraphicUtils.cpp
//  BraveFrontier

//  Created by WillArk on 7/13/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "GraphicUtils.h"
#include "CommonUtils.h"
#include "GameSprite.h"
#include "StringLabel.h"
#include "ColorString.h"
#include "StringComparator.h"
#include "ParamList.h"
#include "TagString.h"
#include "StringLabelList.h"
#include "WideUseFrame.h"
#include "UserFontSetting.h"
#include "GameConst.h"
/*
 * コンストラクタ。
 */
GraphicUtils::GraphicUtils()
{

}

/*
 * デストラクタ。
 */
GraphicUtils::~GraphicUtils()
{

}

/*
 * 塗りつぶし。
 */
CCSprite* GraphicUtils::fillRect( CCLayer * layerid, float x, float y, float w, float h, ccColor3B color )
{
    return fillRect( layerid, x, y, w, h, 255, 0, color );
}

/*
 * 塗りつぶし。
 */
CCSprite* GraphicUtils::fillRect( CCLayer * layerid, float x, float y, float w, float h, int zorder, ccColor3B color )
{
    return fillRect( layerid, x, y, w, h, 255, zorder, color );
}

/*
 * 塗りつぶし。
 */
CCSprite* GraphicUtils::fillRect( CCLayer * layerid, float x, float y, float w, float h, int opacity, int zorder, ccColor3B color )
{
    
    CCSprite* sprite = new CCSprite();
    //sprite->autorelease();
    
    sprite->CCSprite::create("img/fill.png");
    sprite->setContentSize(CCSize(w, h));
    sprite->setColor(color );
    sprite->setAnchorPoint( ccp( 0.0, 1.0 ) );
    sprite->setPosition( ccp(x, y) );
    sprite->setOpacity( opacity );
    //sprite->autorelease();
    
    if( layerid )
    {
        layerid->addChild(sprite, zorder);
    }

    return sprite;
}


/*
 * 塗りつぶし。
 */
CCSprite* GraphicUtils::fillRect( CCSprite* sprite, CCLayer * layerid, float x, float y, float w, float h, int opacity, int zorder, ccColor3B color )
{
    
    //sprite->autorelease();
    
    sprite->CCSprite::create("img/fill.png");
    sprite->setContentSize(CCSize(w, h));
    sprite->setColor(color );
    sprite->setAnchorPoint( ccp( 0.0, 1.0 ) );
    sprite->setPosition( ccp(x, y) );
    sprite->setOpacity( opacity );
    //sprite->autorelease();
    
    if( layerid )
    {
        layerid->addChild(sprite, zorder);
    }
    
    return sprite;
}

/*
 * タグ付き文字列の描画。
 */
StringLabelList* GraphicUtils::initString( CCLayer * layerid, string str, float x, float y, float w, float h, ccColor3B base_color, int base_align, int font_size )
{
    return initString( layerid, str, x, y, w, h, base_color, base_align, font_size, 1 );
}

/*
 * タグ付き文字列の描画。
 */
StringLabelList* GraphicUtils::initString( CCLayer * layerid, string str, float x, float y, float w, float h, ccColor3B base_color, int base_align, int font_size, int line_space )
{
    
    return initString( layerid, str, x, y, w, h, base_color, base_align, font_size, line_space, true );
}

/*
 * タグ付き文字列の描画。
 */
StringLabelList* GraphicUtils::initString( CCLayer * layerid, string str, float x, float y, float w, float h, ccColor3B base_color, int base_align, int font_size, int line_space, bool auto_kaigyou )
{
    return initString( layerid, str, x, y, w, h, base_color, base_align, font_size, line_space, auto_kaigyou, true );
}
StringLabelList* GraphicUtils::initString( CCLayer * layerid, string str, float x, float y, float w, float h, ccColor3B base_color, int base_align, int font_size, int line_space, bool auto_kaigyou, bool useTag )
{
    StringLabelList* list = new StringLabelList();
    //list->autorelease();
    
    list->setBaseX( x );
    list->setBaseY( y );
    list->setLayerID( layerid );

    list->setWidth( w );
    list->setHeight( h );
    list->setBaseColor( base_color );
    list->setBaseAlign( base_align );
    list->setBaseFontSize( font_size );
    list->setLineSpace( line_space );
    list->setAutoKaigyouFlg( auto_kaigyou );

    list->setUseTagFlg(useTag);
    
    if( !str.empty() )
    {
        list->changeString( str );
    }
    
    if( layerid )
    {
        layerid->addChild(list);
    }
    
    return list;
}


/*
 * タグ付き文字列の描画。
 */
StringLabelList* GraphicUtils::drawString( CCLayer * layerid, string str, float x, float y, float w, float h, ccColor3B base_color, int base_align, int font_size )
{
    return drawString( layerid, str, x, y, w, h, base_color, base_align, font_size, 1 );
}

/*
 * タグ付き文字列の描画。
 */
StringLabelList* GraphicUtils::drawString( CCLayer * layerid, string str, float x, float y, float w, float h, ccColor3B color, int align, int font_size, int line_space  )
{
    return drawString( layerid, str, x, y, w, h, color, align, font_size, line_space, true );
}

/*
 * タグ付き文字列の描画。
 */
StringLabelList* GraphicUtils::drawString( CCLayer * layerid, string str, float x, float y, float w, float h, ccColor3B color, int align, int font_size, int line_space, bool auto_kaigyou )
{

    return drawString( layerid, str, x, y, w, h, color, align, font_size, line_space, auto_kaigyou, true );
    
}
StringLabelList* GraphicUtils::drawString( CCLayer * layerid,string str, float x, float y, float w, float h, ccColor3B color, int align, int font_size, int line_space, bool auto_kaigyou, bool useTag )
{
    StringLabelList* list = initString( layerid, str, x, y, w, h, color, align, font_size, line_space, auto_kaigyou, useTag );
    
    list->updatePosition();
    list->draw();
    
    return list;

}
/*
 * タグ付き文字列の描画。
 */
StringLabelList* GraphicUtils::drawString( CCLayer * layerid, string str, float x, float y, ccColor3B base_color, int base_align, int font_size )
{
    return drawString( layerid, str, x, y, base_color, base_align, font_size, 1 );
}


/*
 * タグ付き文字列の描画。
 */
StringLabelList* GraphicUtils::drawString( CCLayer * layerid, string str, float x, float y, ccColor3B base_color, int base_align, int font_size, int line_space )
{
    float w = CommonUtils::getStringWidth( str, font_size );
    float h = font_size;
    
    switch ( base_align )
    {
        case TEXT_ALIGN_CENTER_TOP:
            x -= (w/2);
            break;
        case TEXT_ALIGN_RIGHT_TOP:
            x -= w;
            break;
        case TEXT_ALIGN_LEFT_MIDDLE:
            y -= (h/2);
            break;
        case TEXT_ALIGN_CENTER_MIDDLE:
            x -= (w/2);
            y -= (h/2);
            break;
        case TEXT_ALIGN_RIGHT_MIDDLE:
            x -= w;
            y -= (h/2);
            break;
        case TEXT_ALIGN_LEFT_BOTTOM:
            y -= h;
            break;
        case TEXT_ALIGN_CENTER_BOTTOM:
            x -= (w/2);
            y -= h;
            break;
        case TEXT_ALIGN_RIGHT_BOTTOM:
            x -= w;
            y -= h;
            break;
        default:
            break;
    }

    return drawString( layerid, str, x, y, w, h, base_color, base_align, font_size, line_space, false );
}

/*
 * 汎用フレームの描画
 */
void GraphicUtils::drawWideUseFrame( CCLayer * layerid, float x, float y, float w,  float h )
{
    WideUseFrame* frame = WideUseFrame::init( layerid, x, y, w, h );
    frame->draw();
}

/*
 * 短形の描画。
 */
GlDrawRect* GraphicUtils::drawRect( CCLayer * layerid, float x, float y, float w, float h, int size, ccColor3B color )
{
    
    GlDrawRect* drect = new GlDrawRect( x, y ,w, h, size, color );
    layerid->addChild(drect);
    
    return drect;
}




