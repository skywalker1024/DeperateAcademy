//
//  TagString.cpp
//  BraveFrontier

//  Created by WillArk on 7/23/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "TagString.h"
#include "CommonUtils.h"
#include "StringLabel.h"
#include "StringLabelList.h"
#include "ParamList.h"
#include "StringComparator.h"
#include "GameConst.h"

/*
 * コンストラクタ。
 */
TagString::TagString()
{
    parseList = new CCMutableArray<ColorString*>;
    
    lineSpace = 1;
    autorelease();
    
    autoKaigyouFlg = true;
}

/*
 * デストラクタ。
 */
TagString::~TagString()
{
    parseList->removeAllObjects();
    parseList->release();
}

/*
 * 描画処理。
 */
/*
void TagString::draw()
{
    
    int linecnt = getLineCount();
    
    float basex = x;
    float basey = y;
    
    
    
    
    // アライン設定
    if( baseAlign == TEXT_ALIGN_CENTER_TOP )
    {
        basex = x + ( ( width - getStringWidth() )/2 );
    }
   
    if( baseAlign == TEXT_ALIGN_RIGHT_TOP )
    {
        basex = x + width - getStringWidth();
    }
  
    if( baseAlign == TEXT_ALIGN_LEFT_MIDDLE )
    {
        basey = y + ( ( height - getStringHeight() )/2 );
    }
    
    if( baseAlign == TEXT_ALIGN_CENTER_MIDDLE )
    {
        basex = x + ( ( width  - getStringWidth()  )/2 );
        basey = y + ( ( height - getStringHeight() )/2 );
    }
    
    if( baseAlign == TEXT_ALIGN_RIGHT_MIDDLE )
    {
        basex = x + width - getStringWidth();
        basey = y + ( ( height - getStringHeight() )/2 );
    }

    if( baseAlign == TEXT_ALIGN_CENTER_BOTTOM )
    {
        basex = x + ( ( width  - getStringWidth()  )/2 );
        basey = y + height - getStringHeight();
    }
    
    if( baseAlign == TEXT_ALIGN_RIGHT_BOTTOM )
    {
        basex = x + width - getStringWidth();
        basey = y + height - getStringHeight();
    }
 
    float dispx = basex;
    float dispy = basey;
    
        
    // 描画処理
    for( int i = 0; i < linecnt; i++ )
    {
        CCMutableArray<ColorString*> *list = getStringList( i );
        
        float lh = getStringLineHeight( i );
        float lw = getStringLineWidth( i );
        
        // 下合わせ
        dispy += lh;
 
        CCLog( "lh=%f i=%d", lh, i );
        
        for( int j = 0; j < list->count(); j++ )
        {
            ColorString* cstr = list->getObjectAtIndex( j );
            
            // アライン
            if( j == 0 )
            {
                if( cstr->getAlign() == ALIGN_LEFT   ) dispx = x;
                if( cstr->getAlign() == ALIGN_CENTER ) dispx = x + ((width-lw)/2);
                if( cstr->getAlign() == ALIGN_RIGHT  ) dispx = x + width - lw;
            }    
            
            // テキストを設定
            StringLabel* label = cstr->getStrLabel();
            
            label->setAlign( TEXT_ALIGN_LEFT_BOTTOM );
            label->setPosition( layerID, dispx, dispy );
            
            GameLayer::shared()->addChild( layerID, label );
             
            // ラベルサイズ取得
            CCSize size = label->getContentSize();
            dispx += size.width;
        }
        
        dispx  = basex;
    }
    

    
}
*/
 
/*
 * 文字列リストを取得。
 */
CCMutableArray<ColorString*> *TagString::getStringList( int line )
{
    CCMutableArray<ColorString*> *list = new CCMutableArray<ColorString*>;
    list->autorelease();
    
    for( int i = 0; i < parseList->count(); i++ )
    {
        ColorString* cstr = parseList->getObjectAtIndex( i );
        if( cstr->getLine() != line ) continue;
        
        list->addObject( cstr );
    }
    
    return list;
}


/*
 * 解析処理。
 */
CCMutableArray<StringLabel*>* TagString::parse()
{
    return parse(true);
}
CCMutableArray<StringLabel*>* TagString::parse( bool useTag )
{
    string cut = "";
    int start_idx = 0;
    
    float zen_width = 0;

    
    // 全角幅を取得
    {
        StringLabel* label_zen = StringLabel::init( "１", ccc3(0,0,0), baseFontSize );

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        zen_width = (int)(label_zen->getContentSize().width);
#else
        zen_width = label_zen->getContentSize().width;
#endif
    }
    

    
    /////////////////////////////////////////////
    // 変数タグの置換
    start_idx = 0;
    
    for( ;; )
    {
        int tag_start1 = tagStr.find( "<param=", start_idx );
        if( tag_start1 == string::npos ) break;
        
        int tag_start2 = tagStr.find( ">", tag_start1 );
        
        string param_str = tagStr.substr( tag_start1+7, tag_start2-(tag_start1+7) );
        
        // 変数の値取得
        string value = ParamList::shared()->getValue( param_str );
        
        if( !value.empty() )
        {
            // 文字列の置換
            tagStr.replace( tag_start1, tag_start2-tag_start1+1, value );
            start_idx = 0;
            continue;
        }
        
        start_idx = tag_start2 + 1;
    }
    
    //tagStr->getStringWidth()
      
    /////////////////////////////////////////////
    // 自動改行チェック
    if( autoKaigyouFlg )
    {
        vector< string > list = StringComparator::comparate( tagStr );
        
        bool tag_start = false;

        float total_size = 0;
        
        string conv_str = "";
        
        for( int i = 0; i < list.size(); i++ )
        {
            if (useTag)
            {
                if( list[i] == "<" )
                {
                    tag_start = true;
                }
                
                if( list[i] == ">" )
                {
                    tag_start = false;
                    conv_str.append( list[i] );
                    continue;
                }
            
                if( tag_start )
                {
                    // 改行チェック
                    if( list[i] == "b" )
                    {
                        if( list[i+1] == "r" )
                        {
                            total_size = 0;
                        }
                    }
                    
                    conv_str.append( list[i] );
                    continue;
                }
            }
            
            float strw = 0;

            // 半角
            if( list[i].length() == 1 )
            {
                StringLabel* label = StringLabel::init( list[i].c_str(), ccc3(0,0,0), baseFontSize );
                strw = label->getContentSize().width;
            }
            // 全角
            else
            {
                strw = zen_width;
            }
            
            
            total_size += strw;
            
            // 改行を挿入
            if( width > 0 && total_size > width )
            {
                //CCLog( "kaigyou2 total_size=%d", total_size );
                
                // 改行コードを入れる
                conv_str.append( "<br>" );
                total_size = strw;
            }

            else
            {
                if (list[i] == "\n")  total_size = 0;
            }
            conv_str.append( list[i] );
            
            
        }
        
        tagStr = conv_str;
    }
  
    
    /////////////////////////////////////////////
    // 改行、カラー、フォントサイズ、アンカー解析
   
    int line = 0;
    
    start_idx = 0;
    
    int active_anchor = 0;
    int active_font_size = baseFontSize;
    ccColor3B active_color = baseColor;
    
    //CCLog( "tag_str=%s", tagStr.c_str() );

    bool brflg = false;

    for( ;; )
    {
        
        // 開始タグ判定
        int tag_start = tagStr.find( "<", start_idx );
        

        if( tag_start != string::npos && useTag )
        {
            //  表示文字列を取得
            cut = tagStr.substr( start_idx, tag_start - (start_idx) );
            
            //CCLog( "cut=%s actuve=%d", cut.c_str(), active_anchor );
            
            if( !cut.empty() || brflg )
            {
                parseList->addObject( new ColorString( cut, active_color, active_font_size, line, active_anchor ) );
            }
            
                
            int tag_close = tagStr.find( ">", tag_start );
            
            // タグ文字列取得
            string param_str = tagStr.substr( tag_start+1, tag_close-(tag_start+1) );
            
            // アンカー
            if( param_str.find( "left" ) != string::npos )
            {
                active_anchor = ALIGN_LEFT;
            }
        
            if( param_str.find( "center" ) != string::npos )
            {
                active_anchor = ALIGN_CENTER;
            }
            
            if( param_str.find( "right" ) != string::npos )
            {
                active_anchor = ALIGN_RIGHT;
            }
            
            // 改行
            if( param_str.find( "br" ) != string::npos )
            {
                line += 1;
                brflg = true;
            }
                
            // カラー設定
            if( param_str.find( "color=" ) != string::npos )
            {
                // 色情報の切り出し
                string color_str = param_str.substr( 6, param_str.length()-6 );
                
                // 色成分に分解
                char *csv = const_cast<char*>( color_str.c_str() );
                int red   = CommonUtils::StrToInt( strtok(  csv, ":" ) );
                int green = CommonUtils::StrToInt( strtok( NULL, ":" ) );
                int blue  = CommonUtils::StrToInt( strtok( NULL, ":" ) );
                
                active_color = ccc3( red, green, blue );
                
            }
            
            // フォントサイズ
            if( param_str.find( "size=" ) != string::npos )
            {
                string size_str = param_str.substr( 5, param_str.length()-5 );
                
                active_font_size = CommonUtils::StrToInt( size_str );
            }
            
            // カラー 終了タグ
            if( param_str.find( "/color" ) != string::npos )
            {
                active_color = baseColor;
            }

            // アンカー 終了タグ
            if( param_str.find( "/center" ) != string::npos )
            {
                active_anchor = ALIGN_LEFT;
            }
            
            if( param_str.find( "/right" ) != string::npos )
            {
                active_anchor = ALIGN_LEFT;
            }
            
            // フォントサイズ 終了タグ
            if( param_str.find( "/size" ) != string::npos )
            {
                active_font_size = baseFontSize;
            }
            
            start_idx = tag_close + 1;
        }
        
        else
        {
            /*
            for( ;; )
            {
                // 改行コードがある場合
                tag_start = tagStr.find( "\n", start_idx );
                if (tag_start != string::npos)
                {
                    //  表示文字列を取得
                    cut = tagStr.substr( start_idx, tag_start - (start_idx) );
                    
                    if( !cut.empty() )
                    {
                        parseList->addObject( new ColorString( cut, active_color, active_font_size, line, active_anchor ) );
                        line += 1;
                    }
                    start_idx = tag_start + 1;
                }
                else
                {
                    break;
                }
            }
            */
            cut = tagStr.substr( start_idx, tagStr.length() - (start_idx) );
            
            if( !cut.empty() )
            {
                //CCLog( "cut=%s", cut.c_str() );
                
                parseList->addObject( new ColorString( cut, active_color, active_font_size, line, active_anchor ) );
            }
            
            break;
        }
        
    }
    

    
    int linecnt = getLineCount();
    
    float basex = 0;
    float basey = 0;
    
    
    
    // アライン設定
    if( baseAlign == TEXT_ALIGN_CENTER_TOP )
    {
        basex = ( ( width - getStringWidth() )/2 );
    }
    
    if( baseAlign == TEXT_ALIGN_RIGHT_TOP )
    {
        basex = width - getStringWidth();
    }
    
    if( baseAlign == TEXT_ALIGN_LEFT_MIDDLE )
    {
        basey = ( ( height - getStringHeight() )/2 );
    }
    
    if( baseAlign == TEXT_ALIGN_CENTER_MIDDLE )
    {
        basex = ( ( width  - getStringWidth()  )/2 );
        basey = ( ( height - getStringHeight() )/2 );
    }
    
    if( baseAlign == TEXT_ALIGN_RIGHT_MIDDLE )
    {
        basex = width - getStringWidth();
        basey = ( ( height - getStringHeight() )/2 );
    }
    
    if( baseAlign == TEXT_ALIGN_CENTER_BOTTOM )
    {
        basex = ( ( width  - getStringWidth()  )/2 );
        basey = height - getStringHeight();
    }
    
    if( baseAlign == TEXT_ALIGN_RIGHT_BOTTOM )
    {
        basex = width - getStringWidth();
        basey = height - getStringHeight();
    }
    
    if( baseAlign == TEXT_ALIGN_LEFT_BOTTOM )
    {
        basey = height - getStringHeight();
    }
    
    float dispx = basex;
    float dispy = basey;
    
    // 返却用のリスト
    CCMutableArray<StringLabel*>* ret = new CCMutableArray<StringLabel*>;
    ret->autorelease();
    
    // ラベルを生成
    for( int i = 0; i < linecnt; i++ )
    {
        CCMutableArray<ColorString*> *list = getStringList( i );
        
        float lh = getStringLineHeight( i );
        float lw = getStringLineWidth( i );
        
        // 下合わせ
        dispy += lh;
        
        for( int j = 0; j < list->count(); j++ )
        {
            ColorString* cstr = list->getObjectAtIndex( j );
            
            // アライン
            if( j == 0 )
            {
                if( cstr->getAlign() == ALIGN_LEFT   ) dispx = 0;
                if( cstr->getAlign() == ALIGN_CENTER ) dispx = ((width-lw)/2);
                if( cstr->getAlign() == ALIGN_RIGHT  ) dispx = width - lw;
            }    
            
            // テキストを設定
            StringLabel* label = cstr->getStrLabel();
            
            label->setAlign( TEXT_ALIGN_LEFT_BOTTOM );
            //label->setPosition( dispx, dispy );
            label->setOffsetX( dispx );
            label->setOffsetY( dispy );
            
            ret->addObject( label );
            
            // ラベルサイズ取得
            CCSize size = label->getContentSize();
            dispx += size.width;
        }
        
        dispx  = basex;
    }
    
    
    return ret;
    
    
    
    
}

/*
 * 文字列の高さを取得。
 */
float TagString::getStringHeight()
{
    float ret = 0;
    
    int linecnt = getLineCount();
    
    for( int i = 0; i < linecnt; i++ )
    {
        float value = getStringLineHeight( i );
        
        ret+= value;
    }
    
    return ret;
}

/*
 * 文字列の幅を取得。
 */
float TagString::getStringWidth()
{
    float ret = 0;
    
    int linecnt = getLineCount();
    
    for( int i = 0; i < linecnt; i++ )
    {
        float value = getStringLineWidth( i );
        
        if( ret < value ) ret = value;
    }
    
    return ret;
    
}

/*
 * 文字列１行の高さを取得。
 */
float TagString::getStringLineHeight( int line )
{
    float ret = 0;
    
    for( int i = 0; i < parseList->count(); i++ )
    {
        ColorString* cstr = parseList->getObjectAtIndex( i );
        
        if( cstr->getLine() != line ) continue;
        
        if( ret < cstr->getHeight() ) ret = cstr->getHeight();
    }
    
    return ret + lineSpace;
    
}

/*
 * 文字列１行の幅を取得。
 */
float TagString::getStringLineWidth( int line )
{
    float ret = 0;
    
    for( int i = 0; i < parseList->count(); i++ )
    {
        ColorString* cstr = parseList->getObjectAtIndex( i );
        
        if( cstr->getLine() != line ) continue;
        
        ret += cstr->getWidth();
    }
    
    return ret;
}

/*
 * 行数を取得。
 */
int TagString::getLineCount()
{
    int cnt = 0;
    
    for( int i = 0; i < parseList->count(); i++ )
    {
        ColorString* cstr = parseList->getObjectAtIndex( i );
        
        if( cnt < cstr->getLine() ) cnt  =cstr->getLine();
    }
    
    return cnt + 1;
}


/**
 * タグ付き文字列の取得。
 */
string TagString::getTagStr()
{
	return tagStr;
}

/*
 * タグ付き文字列の設定。
 */
void TagString::setTagStr( string val )
{
	tagStr = val;
}

/**
 * ベースカラーの取得。
 */
ccColor3B TagString::getBaseColor()
{
	return baseColor;
}

/*
 * ベースカラーの設定。
 */
void TagString::setBaseColor( ccColor3B val )
{
	baseColor = val;
}

/**
 * ベースアンカーの取得。
 */
int TagString::getBaseAlign()
{
	return baseAlign;
}

/*
 * ベースアンカーの設定。
 */
void TagString::setBaseAlign( int val )
{
	baseAlign = val;
}

/**
 * ベースフォントサイズの取得。
 */
int TagString::getBaseFontSize()
{
	return baseFontSize;
}

/*
 * ベースフォントサイズの設定。
 */
void TagString::setBaseFontSize( int val )
{
	baseFontSize = val;
}

/**
 * 描画幅の取得。
 */
float TagString::getWidth()
{
	return width;
}

/*
 * 描画幅の設定。
 */
void TagString::setWidth( float val )
{
	width = val;
}

/**
 * 描画高さの取得。
 */
float TagString::getHeight()
{
	return height;
}

/*
 * 描画高さの設定。
 */
void TagString::setHeight( float val )
{
	height = val;
}

/*
 * 行間の取得。
 */
float TagString::getLineSpace()
{
    return lineSpace;
}

/*
 * 行間の設定。
 */
void TagString::setLineSpace( float value )
{
    lineSpace = value;
}

/*
 * フォント名の設定。
 */
void TagString::setFontName( string name )
{
    fontName = name;
}

/*
 * 自動改行フラグ。
 */
void TagString::setAutoKaigyouFlg( bool flg )
{
    autoKaigyouFlg = flg;
}

