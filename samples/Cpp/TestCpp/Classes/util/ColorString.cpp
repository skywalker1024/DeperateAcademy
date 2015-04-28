//
//  ColorString.cpp
//  BraveFrontier

//  Created by WillArk on 7/18/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "ColorString.h"
#include "GameConst.h"
/*
 * コンストラクタ。
 */
ColorString::ColorString()
{
    
    
    autorelease();
}

/*
 * コンストラクタ。
 */
ColorString::ColorString( string str, ccColor3B color, int font_size, int line, int align )
{
    this->str = str;
    this->color = color;
    this->fontSize = font_size;
    this->line = line;
    this->align = align;
    
    strLabel = StringLabel::init( str.c_str(), color, TEXT_ALIGN_LEFT_TOP, font_size );
    
    autorelease();
}


/*
 * デストラクタ。
 */
ColorString::~ColorString()
{

}

/*
 * 文字列ラベル取得。
 */
StringLabel* ColorString::getStrLabel()
{
    return strLabel;
}

/*
 * 文字列幅取得。
 */
float ColorString::getWidth()
{
    return strLabel->getContentSize().width; 
}

/*
 * 文字列高さ取得。
 */
float ColorString::getHeight()
{
    return fontSize;
}


/**
 * 文字列の取得。
 */
string ColorString::getStr()
{
	return str;
}

/*
 * 文字列の設定。
 */
void ColorString::setStr( string val )
{
	str = val;
}

/**
 * カラーの取得。
 */
ccColor3B ColorString::getColor()
{
	return color;
}

/*
 * カラーの設定。
 */
void ColorString::setColor( ccColor3B val )
{
	color = val;
}

/*
 * フォントサイズの取得。
 */
int ColorString::getFontSize()
{
    return fontSize;
}

/*
 * フォントサイズの設定。
 */
void ColorString::setFontSize( int value )
{
    fontSize = value;
}

/*
 * 行の取得。
 */
int ColorString::getLine()
{
    return line;
}

/*
 * 行の設定。
 */
void ColorString::setLine( int value )
{
    line = value;
}

/*
 * 表示基準位置の取得。
 */
int ColorString::getAlign()
{
    return align; 
}

/*
 * 表示基準位置の設定。
 */
void ColorString::setAlign( int value )
{
    align = value;
}

