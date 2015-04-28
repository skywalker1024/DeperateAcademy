//
//  TagString.h
//  BraveFrontier

//  Created by WillArk on 7/23/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_TagString_h
#define BraveFrontier_TagString_h

#include "cocos2d.h"
#include "ColorString.h"


USING_NS_CC;

class TagString : public CCObject
{
	public:
		// コンストラクタ
		TagString();
		// デストラクタ
		~TagString();
		// タグ付き文字列の取得
		string getTagStr();
		// タグ付き文字列の設定
		void setTagStr( string value );
		// ベースカラーの取得
		ccColor3B getBaseColor();
		// ベースカラーの設定
		void setBaseColor( ccColor3B value );
		// ベースアラインの取得
		int getBaseAlign();
		// ベースアラインの設定
		void setBaseAlign( int value );
		// ベースフォントサイズの取得
		int getBaseFontSize();
		// ベースフォントサイズの設定
		void setBaseFontSize( int value );
		// 描画幅の取得
		float getWidth();
		// 描画幅の設定
		void setWidth( float value );
		// 描画高さの取得
		float getHeight();
		// 描画高さの設定
		void setHeight( float value );
        // 行間の取得
        float getLineSpace();
        // 行間の設定
        void setLineSpace( float value );
        // 解析処理
        CCMutableArray<StringLabel*>* parse();

        CCMutableArray<StringLabel*>* parse( bool useTag );
        // フォント名の設定
        void setFontName( string name );
        // 自動改行フラグの設定
        void setAutoKaigyouFlg( bool flg );
    
	protected:

	private:
        
        // アンカー
        static const int ALIGN_LEFT    = 1;
        static const int ALIGN_CENTER  = 2;
        static const int ALIGN_RIGHT   = 3;
    
    
        // 文字列リストを取得
        CCMutableArray<ColorString*> *getStringList( int line );
        // 文字列の高さを取得
        float getStringHeight();
        // 文字列の幅を取得
        float getStringWidth();
        // 文字列１行の高さを取得
        float getStringLineHeight( int line );
        // 文字列１行の幅を取得
        float getStringLineWidth( int line );
        // 行数を取得
        int getLineCount();

		// タグ付き文字列
		string tagStr;
		// ベースカラー
		ccColor3B baseColor;
		// ベース表示位置
		int baseAlign;
		// ベースフォントサイズ
		int baseFontSize;
    
        //  フォント名
        string fontName;
    
		// 描画幅
		float width;
		// 描画高さ
		float height;
        // 解析後の文字列リスト
        CCMutableArray<ColorString*>*parseList;
        // 行間
        float lineSpace;
        // 自動改行フラグ
        bool autoKaigyouFlg;
};

#endif
