//
//  StringLabel.h
//  SampleGame2
//
//  Created by 株式会社 ウィルアーク on 4/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef BraveFrontier_StringLabel_h
#define BraveFrontier_StringLabel_h


#include "cocos2d.h"

USING_NS_CC;

class StringLabel : public CCLabelTTF
{
    public:
        // コンストラクタ
        StringLabel();
        // 初期化処理
        static StringLabel* init( const char* str, ccColor3B color, int font_size );
        static StringLabel* init( const char* str, ccColor3B color, int align, int font_size );
        static StringLabel* init( const char* str, float x, float y, ccColor3B color, int align, int font_size );
        static StringLabel* init( const char* str, float x, float y, float w, float h, ccColor3B color, int align, int font_size );
        static StringLabel* init( const char* str, float x, float y, float w, float h, ccColor3B color, int align, const char* font_name, int font_size );
    
        static StringLabel* init( CCLayer * layerid, const char* str, float x, float y, ccColor3B color, int align, int font_size );
        static StringLabel* init( CCLayer * layerid, const char* str, float x, float y, float w, float h, ccColor3B color, int align, int font_size );
        static StringLabel* init( CCLayer * layerid, const char* str, float x, float y, float w, float h, ccColor3B color, int align, const char* font_name, int font_size );
    
        // 設定処理
        static StringLabel* set( CCLayer * layerid, const char* str, float x, float y, ccColor3B color, int align, int font_size );
        static StringLabel* set( CCLayer * layerid, const char* str, float x, float y, float w, float h, ccColor3B color, int align, int font_size );
        static StringLabel* set( CCLayer * layerid, const char* str, float x, float y, ccColor3B color, int align, int font_size, const char* font_name );
        static StringLabel* set( CCLayer * layerid, const char* str, float x, float y, float w, float h, ccColor3B color, int align, int font_size, const char* font_name );
    
    
        // 座標設定
        void setPosition( float x, float y );
        void setPosition( CCLayer * layerid, float x, float y );
    
        // 文字列の変更
        void changeString( const char* str );
        void setAlign( int value );
        int getAlign();
    
		// フォントサイズの取得
		int getFontSize();
		// フォントサイズの設定
		void setFontSize( int value );
        // x座標の取得
        float getX();
        // y座標の取得
        float getY();
        // 管理IDを設定
        void setMngID( string value );
        // 管理IDを取得
        string getMngID();
        // オフセットx座標を取得
        float getOffsetX();
        // オフセットy座標を取得
        float getOffsetY();
        // オフセットx座標を設定
        void setOffsetX( float value );
        // オフセットy座標を設定
        void setOffsetY( float value );
    
    
    private:
        // cocos側のAlign定数を取得
        static CCTextAlignment getCCAlign( int align );
        // 基準座標を反映
        CCPoint getAlignPosition( float x, float y );
        // アクティブなフォント名を取得
        static const char* getFontName();
    
    
        // 基準座標
        int align;
        // フォントサイズ
        int fontSize;
        // x座標
        float x;
        // y座標
        float y;
        // レイヤーID
        static CCLayer * layerid;
        // 管理ID
        string mngID;
    
        // オフセットx座標
        float offsetX;
        // オフセットy座標
        float offsetY;
    
};

#endif
