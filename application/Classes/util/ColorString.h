//
//  ColorString.h
//  BraveFrontier

//  Created by WillArk on 7/18/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_ColorString_h
#define BraveFrontier_ColorString_h

#include "cocos2d.h"
#include "StringLabel.h"


USING_NS_CC;

class ColorString : public CCObject
{
	public:
		// コンストラクタ
		ColorString();
        ColorString( string str, ccColor3B color, int font_size, int line, int anchor );
		// デストラクタ
		~ColorString();
		// 文字列の取得
		string getStr();
		// 文字列の設定
		void setStr( string value );
		// カラーの取得
		ccColor3B getColor();
		// カラーの設定
		void setColor( ccColor3B value );
        // フォントサイズの取得
        int getFontSize();
        // フォントサイズの設定
        void setFontSize( int value );
        // 行の取得
        int getLine();
        // 行の設定
        void setLine( int value );
        // 表示基準位置の取得
        int getAlign();
        // 表示基準位置の設定
        void setAlign( int value );
        // 文字列ラベル取得
        StringLabel* getStrLabel();
        // 文字列幅取得
        float getWidth();
        // 文字列高さ取得
        float getHeight();
    
    
	protected:

	private:
		// 文字列
		string str;
		// カラー
		ccColor3B color;
        // フォントサイズ
        int fontSize;
        // 行
        int line;
        // 表示基準
        int align;
        // ラベル
        StringLabel* strLabel;
    
};

#endif
