//
//  StringLabelList.cpp
//  BraveFrontier

//  Created by WillArk on 8/10/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "StringLabelList.h"
#include "CommonUtils.h"
#include "TagString.h"
#include "UserFontSetting.h"

/*
 * コンストラクタ。
 */
StringLabelList::StringLabelList()
{
    autorelease();
    labelList = new CCMutableArray<StringLabel*>;
    
    is_draw = false;
    isVisible = true;
    
    actionSprite = NULL;
    
    zOrder = 0;
    opacity = 255;
    
    shadowFlg = true;
    autoKaigyouFlg = true;
    

    shadowLabel = new CCMutableArray<StringLabel*>;
    
    orgString = "";
    
    useTag = true;
    
    fontName = UserFontSetting::shared()->getActiveFont();
    
    layerID = NULL;
}

/*
 * デストラクタ。
 */
StringLabelList::~StringLabelList(void)
{

    CCLog( "delete StringLabelList %d", this );
    
    labelList->release();
    shadowLabel->release();
}

/*
 * 文字列の追加。
 */
void StringLabelList::addObject( StringLabel* label )
{
    
    string str = string( label->getString() );
    if( str == " " ) return;
    
    // 影
    if( shadowFlg )
    {

        StringLabel* strLabel = StringLabel::init( label->getString(), ccc3(0,0,0), label->cocos2d::CCLabelTTF::getFontSize() );
        strLabel->setOffsetX( label->getOffsetX() + 1 );
        strLabel->setOffsetY( label->getOffsetY() + 1 );
        
        strLabel->setAnchorPoint( label->getAnchorPoint());
        strLabel->setAlign( label->getAlign() );
        labelList->addObject( strLabel );
        shadowLabel->addObject(strLabel);
        /*
        shadowLabel = StringLabel::init( label->getString(), ccc3(0,0,0), label->cocos2d::CCLabelTTF::getFontSize() );
        
        shadowLabel->setOffsetX( label->getOffsetX() + 1 );
        shadowLabel->setOffsetY( label->getOffsetY() + 1 );
        
        shadowLabel->setAnchorPoint( label->getAnchorPoint());
        shadowLabel->setAlign( label->getAlign() );
        labelList->addObject( shadowLabel );

        */
    }
    
    labelList->addObject( label );
}


/**
 * ベースｘ座標の取得。
 */
float StringLabelList::getBaseX()
{
	return baseX;
}

/*
 * ベースｘ座標の設定。
 */
void StringLabelList::setBaseX( float val )
{
	baseX = val;
}

/**
 * ベースｙ座標の取得。
 */
float StringLabelList::getBaseY()
{
	return baseY;
}

/*
 * ベースｙ座標の設定。
 */
void StringLabelList::setBaseY( float val )
{
	baseY = val;
}

/*
 * レイヤーIDの設定。
 */
void StringLabelList::setLayerID( CCLayer * value )
{
    layerID = value; 
}

/*
 * レイヤーIDの取得。
 */
CCLayer * StringLabelList::getLayerID()
{
    return layerID;
}

/*
 * ラベルリストの取得。
 */
CCMutableArray<StringLabel*>* StringLabelList::getLabelList()
{
    return labelList;
}

/*
 * 文字列の変更。
 */
void StringLabelList::changeString( string str )
{
//    CCLog( "StringLabelList::changeString str=%s count=%d", str.c_str(), labelList->count() );

    //str="52<color=255:165:0>個</color>";
    
    orgString = str;
    
    string log_font = UserFontSetting::shared()->getActiveFont();
    
    UserFontSetting::shared()->setActiveFont( fontName );
    
    if( layerID )
    {
        for( int i = 0; i < labelList->count(); i++ )
        {
            StringLabel* label = labelList->getObjectAtIndex( i );
            
            layerID->removeChild(label);
        }
        for( int i = 0; i < shadowLabel->count(); i++ )
        {
            StringLabel* label = shadowLabel->getObjectAtIndex( i );
            
            layerID->removeChild(label);
        }
    }
    
    labelList->removeAllObjects();

    shadowLabel->removeAllObjects();

    
    TagString* tstr = new TagString();
    
    tstr->setWidth( width );
    tstr->setHeight( height );
    tstr->setBaseColor( baseColor );
    tstr->setBaseAlign( baseAlign );
    tstr->setBaseFontSize( baseFontSize );
    tstr->setTagStr( str );
    tstr->setAutoKaigyouFlg( autoKaigyouFlg );
    
    tstr->setLineSpace( lineSpace );
    

    CCMutableArray<StringLabel*>*parse_list = tstr->parse(useTag);
    
    for( int i = 0; i < parse_list->count(); i++ )
    {
        StringLabel*label = parse_list->getObjectAtIndex( i );
        
        label->setScale( getScale() );
        
        addObject( label );
        
        //labelList->addObject(parse_list->getObjectAtIndex( i ));
    }
    
    is_draw = false;
    
    
    setPosition( baseX, baseY );
    //龚畅优添加判断 快速点击浮层时 位置错误bug修复。在run action的时候draw位置会错误
    if (!isRunningAction()) {
    draw();
    }
    
    UserFontSetting::shared()->setActiveFont( log_font );

}


/*
 * 描画処理。
 */
void StringLabelList::draw()
{
    
    if( isRunningAction() )
    {
        CCPoint point = CCDirector::sharedDirector()->convertToUI( actionSprite->getPosition() );
        setBasePosition( point.x, point.y );
        setOpacity( actionSprite->getOpacity() );
        setScale( actionSprite->getScale() );
    }
    else if( actionSprite )
    {
        CCPoint point = CCDirector::sharedDirector()->convertToUI( actionSprite->getPosition() );
        setBasePosition( point.x, point.y );
        setOpacity( actionSprite->getOpacity() );
        setScale( actionSprite->getScale() );
        actionSprite = NULL;
    }
    
    
    for( int i = 0; i < labelList->count(); i++ )
    {
        StringLabel* label = labelList->getObjectAtIndex( i );
        
        label->setScale( getScale() );

        if (shadowLabel->containsObject(label))
        {
            if( !shadowFlg )
            {
                label->setVisible( false );
            }
        }
        
        /*

        if( label == shadowLabel )
        {
            if( !shadowFlg ) label->setVisible( false );
        }

        */
        if( layerID && (!layerID->getChildren() || !layerID->getChildren()->containsObject(label)))
        {
            layerID->addChild( label, zOrder );
        }
        /*
        else
        {
            GameLayer::shared()->reorderChid(layerID, zOrder, label );
        }
        */
    }
    
    
    //updatePosition();
    
}

/*
 * レイヤーから解放。
 */
void StringLabelList::removeLayer()
{
    for( int i = 0; i < labelList->count(); i++ )
    {
        StringLabel* label = labelList->getObjectAtIndex( i );
        
        layerID->removeChild(label);
    }
}

/*
 * 座標設定。
 */
void StringLabelList::setPosition( float x, float y )
{
    
    for( int i = 0; i < labelList->count(); i++ )
    {
        StringLabel* label = labelList->getObjectAtIndex( i );
        
        label->setPosition( x + label->getOffsetX(), y + label->getOffsetY() );
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        //Hack: Heureustic font adjustment to deal with size different between iOS and Android fonts
        
        //(Only use for Google Play - Amazon doesn't need it)
        static int cachedUseHeureusticFontAdjustment = -1;
        
        if(cachedUseHeureusticFontAdjustment < 0) {
            if(!IS_KINDLE) {
                cachedUseHeureusticFontAdjustment = 1;
            } else {
                cachedUseHeureusticFontAdjustment = 0;
            }
        }
        
        //(If Google Play, apply)
        if(cachedUseHeureusticFontAdjustment > 0) {
            
            if(fontName == HIRAGINO_FONT_NAME) {
                label->setPosition( x + label->getOffsetX(), y + label->getOffsetY() - 0 * int(baseFontSize/5));
            }
        }
#endif

    }

    baseX = x;
    baseY = y;

}

/*
 * ベース座標設定。
 */
void StringLabelList::setBasePosition( float x, float y )
{
    baseX = x;
    baseY = y;
    
    updatePosition();
    
}

/*
 * 座標更新。
 */
void StringLabelList::updatePosition()
{
    if( actionSprite )
    {
    //    actionSprite->stopAllActions();
    }
    
    setPosition( baseX, baseY );
}


/*
 * 文字列の高さを取得。
 */
int StringLabelList::getStringHeight()
{
    float min_top = -1;
    float max_bottom = -1;
    bool firstT = true;
    bool firstB = true;
    
    for( int i = 0; i < labelList->count(); i++ )
    {
        StringLabel* label = labelList->getObjectAtIndex( i );
        
        CCSize size = label->getContentSize();
        
        float top       = label->getY() - (size.height/2);
        float bottom    = label->getY() + (size.height/2);
        
        if( firstT || min_top > top )
        {
            min_top = top;
            firstT = false;
        }
        
        if( firstB || max_bottom < bottom )
        {
            max_bottom = bottom;
            firstB = false;
        }
    }
    
    return max_bottom - min_top;
}

/*
 * 文字列の幅を取得。
 */
/*
int StringLabelList::getStringWidth()
{
    float min_left = -1;
    float max_right = -1;
    
    
    for( int i = 0; i < labelList->count(); i++ )
    {
        StringLabel* label = labelList->getObjectAtIndex( i );
        
        CCSize size = label->getContentSize();
        
        
        
        
        float width = size.width * label->getScale();

        CCLog( "getStringWidth() str=%s i=%d width=%f",  label->getString(), i, width );


        float left     = label->getX() - (width/2);
        float right    = label->getX() + (width/2);
        
        if( min_left < 0 || min_left > left )
        {
            min_left = left;
        }
        
        if( max_right < 0 || max_right < right )
        {
            max_right = right;
        }
    }
    
    return max_right - min_left;
}
*/

int StringLabelList::getStringWidth()
{
    float width = 0;
    
    for( int i = 0; i < labelList->count(); i++ )
    {
        StringLabel* label = labelList->getObjectAtIndex( i );
        
        CCSize size = label->getContentSize();
        
        width += size.width * label->getScale();
        
    }
    
    return width/2;
}


/*
 *  透明度設定。
 */
void StringLabelList::setOpacity( int opacity )
{
    for( int i = 0; i < labelList->count(); i++ )
    {
        StringLabel* label = labelList->getObjectAtIndex( i );
        label->setOpacity( opacity );
    }
    
    this->opacity = opacity;
}


/*
 * 表示設定。
 */
void StringLabelList::setIsVisible( bool flg )
{
    
    isVisible = flg;
    
    for( int i = 0; i < labelList->count(); i++ )
    {
        StringLabel* label = labelList->getObjectAtIndex( i );
        label->setVisible( flg );
    }
}

/*
 * 表示設定を取得。
 */
bool StringLabelList::getIsVisible()
{
    return isVisible;
}

/**
 * ベースカラーの取得。
 */
ccColor3B StringLabelList::getBaseColor()
{
	return baseColor;
}

/*
 * ベースカラーの設定。
 */
void StringLabelList::setBaseColor( ccColor3B val )
{
	baseColor = val;
}

/**
 * ベースアンカーの取得。
 */
int StringLabelList::getBaseAlign()
{
	return baseAlign;
}

/*
 * ベースアンカーの設定。
 */
void StringLabelList::setBaseAlign( int val )
{
	baseAlign = val;
}

/**
 * ベースフォントサイズの取得。
 */
int StringLabelList::getBaseFontSize()
{
	return baseFontSize;
}

/*
 * ベースフォントサイズの設定。
 */
void StringLabelList::setBaseFontSize( int val )
{
	baseFontSize = val;
}

/**
 * 描画幅の取得。
 */
float StringLabelList::getWidth()
{
	return width;
}

/*
 * 描画幅の設定。
 */
void StringLabelList::setWidth( float val )
{
	width = val;
}

/**
 * 描画高さの取得。
 */
float StringLabelList::getHeight()
{
	return height;
}

/*
 * 描画高さの設定。
 */
void StringLabelList::setHeight( float val )
{
	height = val;
}

/*
 * 行間の取得。
 */
float StringLabelList::getLineSpace()
{
    return lineSpace;
}

/*
 * 行間の設定。
 */
void StringLabelList::setLineSpace( float value )
{
    lineSpace = value;
}

// zオーダーの設定
void StringLabelList::setZorder( int value )
{
    zOrder = value;
    
    for( int i = 0; i < labelList->count(); i++ )
    {
        StringLabel* label = labelList->getObjectAtIndex( i );
        
        layerID->reorderChild(label, zOrder);
    }
}

/*
 * アクション開始。
 */
void StringLabelList::runStringAction( CCAction* action )
{

    if( actionSprite )
    {
        this->removeChild( actionSprite, true );
        actionSprite = NULL;
    }
    
    if( !actionSprite )
    {
        actionSprite = CCSprite::create( "img/fill.png" );
        this->addChild( actionSprite );
  
    }
    
    
    actionSprite->stopAllActions();
    
    actionSprite->setVisible( false );
    actionSprite->setOpacity( opacity );
    actionSprite->setPosition( ccp(baseX, baseY) );
    actionSprite->runAction( action );
    
    
    
    //actionSprite->numberOfRunningActions()
}

/*
 * アクション中の件数を取得。
 */
bool StringLabelList::isRunningAction()
{
    if( !actionSprite ) return false;
    
    if( actionSprite->numberOfRunningActions() > 0 )
    {
        return true;
    }
    
    return false;
}

/*
 * アクション停止。
 */
void StringLabelList::stopAllActions()
{
    if( !actionSprite ) return ;

    if ( isRunningAction() )
    {
        actionSprite->stopAllActions();
    }
}

/*
 * 影を設定。
 */
void StringLabelList::setShadowFlg( bool value )
{
    shadowFlg = value;
}

/*
 * 空文字列か。
 */
bool StringLabelList::empty()
{
    if( labelList->count() == 0 ) return true;
    
    return false;
}

/*
 * 元の文字列取得。
 */
string StringLabelList::getString()
{
    return orgString;
}

/*
 * 自動改行フラグ。
 */
void StringLabelList::setAutoKaigyouFlg( bool flg )
{
    autoKaigyouFlg = flg;
}
/*
 * タグ使用フラグの設定。
 */
void StringLabelList::setUseTagFlg( bool flg )
{
    useTag = flg;
}

CCRect StringLabelList::getRect()
{
    float w = -1;
    for( int i = 0; i < labelList->count(); i++ )
    {
        StringLabel* label = labelList->getObjectAtIndex( i );
        if (!shadowLabel->containsObject(label))
        {
            CCSize size = label->getContentSize();
            
            float width = size.width * label->getScale();
            if (w < 0 || w < width) w = width;
        }
    }
    
    float min_top = -1;
    float max_bottom = -1;
    
    for( int i = 0; i < labelList->count(); i++ )
    {
        StringLabel* label = labelList->getObjectAtIndex( i );
        if (!shadowLabel->containsObject(label))
        {
            CCSize size = label->getContentSize();
            
            float top       = label->getY() - (size.height/2);
            float bottom    = label->getY() + (size.height/2);
            
            if( min_top < 0 || min_top > top )
            {
                min_top = top;
            }
            
            if( max_bottom < 0 || max_bottom < bottom )
            {
                max_bottom = bottom;
            }
        }
    }
    
    float h = max_bottom - min_top;
    
    float x = getBaseX();
    float y = getBaseY();
        
    return CCRect(x, y, w, h);
}




