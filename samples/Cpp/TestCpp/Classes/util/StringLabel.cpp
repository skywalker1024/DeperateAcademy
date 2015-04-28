//
//  StringLabel.cpp
//  SampleGame2
//
//  Created by 株式会社 ウィルアーク on 4/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "StringLabel.h"
#include "CommonUtils.h"
#include "UserFontSetting.h"
#include "GameConst.h"
CCLayer * StringLabel::layerid = NULL;
/*
 * 初期化処理。
 * str:文字列。
 * color:カラー。
 * font_size:フォントサイズ。
 */
StringLabel* StringLabel::init( const char* str, ccColor3B color, int font_size )
{
    return init( str, 0, 0, 0, 0, color, TEXT_ALIGN_LEFT_TOP, getFontName(), font_size );
}

/*
 * 初期化処理。
 * str:文字列。
 * color:カラー。
 * align:表示基準位置。
 * font_size:フォントサイズ。
 */
StringLabel* StringLabel::init( const char* str, ccColor3B color, int align, int font_size )
{
    return init( str, 0, 0, 0, 0, color, align, getFontName(), font_size );
}


/*
 * 初期化処理。
 * str:文字列。
 * x:x座標。
 * y:y座標。
 * color:カラー。
 * align:表示基準位置。
 * font_size:フォントサイズ。
 */
StringLabel* StringLabel::init( const char* str, float x, float y, ccColor3B color, int align, int font_size )
{
    
    return init( str, x, y, 0, 0, color, align, getFontName(), font_size );
}

/*
 * 初期化処理。
 * str:文字列。
 * x:x座標。
 * y:y座標。
 * w:表示幅。
 * h:表示高さ。
 * color:カラー。
 * align:表示基準位置。
 * font_size:フォントサイズ。
 */
StringLabel* StringLabel::init( const char* str, float x, float y, float w, float h, ccColor3B color, int align, int font_size )
{
    return init( str, x, y, w, h, color, align, getFontName(), font_size );
}

/*
 * 初期化処理。
 * str:文字列。
 * x:x座標。
 * y:y座標。
 * w:表示幅。
 * h:表示高さ。
 * align:表示基準位置。
 * font_name:フォント名。 
 * font_size:フォントサイズ。
 */
StringLabel* StringLabel::init( const char* str, float x, float y, float w, float h, ccColor3B color, int align, const char* font_name, int font_size )
{
    return init( layerid, str, x, y, w, h, color, align, font_name, font_size );
}

/*
 * 初期化処理。
 * layerid:レイヤーID。
 * str:文字列。
 * x:x座標。
 * y:y座標。
 * color:カラー。
 * align:表示基準位置。
 * font_size:フォントサイズ。
 */
StringLabel* StringLabel::init( CCLayer * layerid, const char* str, float x, float y, ccColor3B color, int align, int font_size )
{
    return init( layerid, str, x, y, 0, 0, color, align, getFontName(), font_size );
}

/*
 * 初期化処理。
 * layerid:レイヤーID。
 * str:文字列。
 * x:x座標。
 * y:y座標。
 * w:表示幅。
 * h:表示高さ。
 * color:カラー。
 * align:表示基準位置。
 * font_size:フォントサイズ。
 */
StringLabel* StringLabel::init( CCLayer * layerid, const char* str, float x, float y, float w, float h, ccColor3B color, int align, int font_size )
{
    return init( layerid, str, x, y, w, h, color, align, getFontName(), font_size );

}

/*
 * 初期化処理。
 * layerid:レイヤーID。
 * str:文字列。
 * x:x座標。
 * y:y座標。
 * w:表示幅。
 * h:表示高さ。
 * color:カラー。
 * align:表示基準位置。
 * font_name:フォント名。
 * font_size:フォントサイズ。
 */
StringLabel* StringLabel::init( CCLayer * layerid, const char* str, float x, float y, float w, float h, ccColor3B color, int align, const char* font_name, int font_size )
{
    StringLabel* label = NULL;
    
    int retry = 0;
    
    string cmp = string( str );
    
    for( ;; )
    {
        if( retry > 5 ) break;
        
        label = new StringLabel();
        
        label->initWithString(str, font_name, font_size, CCSize( w, h ), kCCTextAlignmentLeft );
        label->setAlign( align );
        label->setFontSize( font_size );
        label->setPosition( layerid, x, y );
        label->setColor( color );
        label->setAnchorPoint( ccp( 0.5, 0.5 ) );    
        
        label->autorelease();
        
        label->x = x;
        label->y = y;
        label->layerid = layerid;

        // 文字が化ける事があるのでリトライ対応
        if( cmp.compare( label->getString() ) == 0 ) break;
        
        retry++;
    }
    
    
    return label;
}


/*
 * レイヤーへの設定処理。
 * layerid:レイヤーID。
 * str:文字列。
 * x:x座標。
 * y:y座標。
 * color:カラー。
 * align:表示基準位置。
 * font_size:フォントサイズ。
 */
StringLabel* StringLabel::set( CCLayer * layerid, const char* str, float x, float y, ccColor3B color, int align, int font_size )
{
    StringLabel* label = init( str, x, y, 0, 0, color, align, DEFAULT_FONT_NAME, font_size );
    
    layerid->addChild( label );
    
    return label;
    
}

/*
 * レイヤーへの設定処理。
 * layerid:レイヤーID。
 * str:文字列。
 * x:x座標。
 * y:y座標。
 * w:表示幅。
 * h:表示高さ。
 * color:カラー。
 * align:表示基準位置。
 * font_size:フォントサイズ。
 */
StringLabel* StringLabel::set( CCLayer * layerid, const char* str, float x, float y, float w, float h, ccColor3B color, int align, int font_size )
{
    StringLabel* label = init( str, x, y, w, h, color, align, DEFAULT_FONT_NAME, font_size );
    
    layerid->addChild(label);
    
    return label;
}


/*
 * レイヤーへの設定処理。
 * layerid:レイヤーID。
 * str:文字列。
 * x:x座標。
 * y:y座標。
 * color:カラー。
 * align:表示基準位置。
 * font_size:フォントサイズ。
 * font_name:フォント名。
 */
StringLabel* StringLabel::set( CCLayer * layerid, const char* str, float x, float y, ccColor3B color, int align, int font_size, const char* font_name )
{
    StringLabel* label = init( str, x, y, 0, 0, color, align, font_name, font_size );
    
    layerid->addChild( label );
    
    return label;

}

/*
 * レイヤーへの設定処理。
 * layerid:レイヤーID。
 * str:文字列。
 * x:x座標。
 * y:y座標。
 * w:表示幅。
 * h:表示高さ。
 * color:カラー。
 * align:表示基準位置。
 * font_size:フォントサイズ。
 * font_name:フォント名。
 */
StringLabel* StringLabel::set( CCLayer * layerid, const char* str, float x, float y, float w, float h, ccColor3B color, int align, int font_size, const char* font_name )
{
    StringLabel* label = init( str, x, y, w, h, color, align, font_name, font_size );
    
    layerid->addChild( label );
    
    return label;

}


/*
 * コンストラクタ。 
 */
StringLabel::StringLabel()
{
    align = TEXT_ALIGN_LEFT_TOP;
}

/*
 * cocos側のAlign定数を取得。
 */
/*
CCTextAlignment StringLabel::getCCAlign( int align )
{
    if( align == TEXT_ALIGN_LEFT ) return CCTextAlignmentLeft;
    if( align == TEXT_ALIGN_CENTER ) return CCTextAlignmentCenter;
    if( align == TEXT_ALIGN_RIGHT ) return CCTextAlignmentRight;
    
    return CCTextAlignmentLeft;
}
*/

/*
 * 座標の設定。
 * x:x座標。
 * y:y座標。
 */
void StringLabel::setPosition( float x, float y )
{
    //CCSprite::setPosition( CommonUtils::convertPosition( x, y ) );
    if (layerid) {
        setPosition( layerid, x, y );
    }
}

/*
*
* 座標の設定。
* layerid:レイヤーID。
* x:x座標。
* y:y座標。
*/
void StringLabel::setPosition( CCLayer * layerid, float x, float y )
{
    
    this->x = x;
    this->y = y;
    this->layerid = layerid;
    
    CCPoint point =  getAlignPosition( x, y );
    
        
    //CCSprite::setPosition( CommonUtils::convertPosition( layerid, point.x, point.y ) );
    
    CCSprite::setPosition( CCDirector::sharedDirector()->convertToGL( ccp(point.x, point.y) ) );

}


/*
 * 文字列の変更。
 * str:変更する文字列。
 */
void StringLabel::changeString( const char* str )
{
    setString( str );
    
    setPosition( layerid, x, y );
}

/*
 * 基準座標を反映。
 */
CCPoint StringLabel::getAlignPosition( float x, float y )
{
    CCRect rect = this->getTextureRect();
    
    float labelw = rect.size.width;
    float labelh = fontSize;

    
    y += ( rect.size.height - fontSize ) / 2;
    
    if( align == TEXT_ALIGN_LEFT_TOP )
    {
        x+= ( labelw / 2 );
        y+= ( labelh / 2 );
    }
    
    if( align == TEXT_ALIGN_CENTER_TOP )
    {
        y+= ( labelh / 2 );
    }
    
    if( align == TEXT_ALIGN_RIGHT_TOP )
    {
        x-= ( labelw / 2 );
        y+= ( labelh / 2 );
    }
    
    if( align == TEXT_ALIGN_LEFT_MIDDLE )
    {
        x+= ( labelw / 2 );
    }
    
    if( align == TEXT_ALIGN_RIGHT_MIDDLE )
    {
        x-= ( labelw / 2 );
    }
    
    if( align == TEXT_ALIGN_LEFT_BOTTOM )
    {
        x+= ( labelw / 2 );
        y-= ( labelh / 2 );
    }
    
    if( align == TEXT_ALIGN_CENTER_BOTTOM )
    {
        y-= ( labelh / 2 );
    }
    
    if( align == TEXT_ALIGN_RIGHT_BOTTOM )
    {
        x-= ( labelw / 2 );
        y-= ( labelh / 2 );
    }
    
    return ccp( x,y );
}

/*
 * アクティブなフォント名を取得。
 */
const char* StringLabel::getFontName()
{
    return UserFontSetting::shared()->getActiveFont().c_str();
}


/*
 * 基準位置の設定。
 */
void StringLabel::setAlign( int val )
{
    align = val;
}

/*
 * 基準位置の取得。
 */
int StringLabel::getAlign()
{
    return align;
}


/*
 * フォントサイズの設定。
 */
void StringLabel::setFontSize( int val )
{
    fontSize = val;
}

/*
 * x座標の取得。
 */
float StringLabel::getX()
{
    return x;
}

/*
 * y座標の取得。
 */
float StringLabel::getY()
{
    return y;
}

/*
 * 管理IDを設定。
 */

void StringLabel::setMngID( string value )
{
    mngID = value;
}


/*
 * 管理IDを取得。
 */

string StringLabel::getMngID()
{
    return mngID;
}

/*
 * オフセットx座標を取得。
 */
float StringLabel::getOffsetX()
{
    return offsetX;
}

/*
 * オフセットy座標を取得。
 */
float StringLabel::getOffsetY()
{
    return offsetY;
}

/*
 * オフセットx座標を設定。
 */
void StringLabel::setOffsetX( float value )
{
    offsetX = value;
}

/*
 * オフセットy座標を設定。
 */
void StringLabel::setOffsetY( float value )
{
    offsetY = value;
}


