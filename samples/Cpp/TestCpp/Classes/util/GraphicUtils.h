//
//  GraphicUtils.h
//  BraveFrontier

//  Created by WillArk on 7/13/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_GraphicUtils_h
#define BraveFrontier_GraphicUtils_h

#include "cocos2d.h"
#include "ColorString.h"
#include "StringLabelList.h"
#include "GlDrawRect.h"
#include "WideUseFrame.h"


USING_NS_CC;

class GraphicUtils : public CCObject
{
	public:
		// コンストラクタ
		GraphicUtils();
		// デストラクタ
		~GraphicUtils();
        // 塗りつぶし
        static CCSprite* fillRect( CCLayer * layerid, float x, float y, float w, float h, ccColor3B color );
        static CCSprite* fillRect( CCLayer * layerid, float x, float y, float w, float h, int zorder, ccColor3B color );
        static CCSprite* fillRect( CCLayer * layerid, float x, float y, float w, float h, int opacity, int zorder, ccColor3B color );
    
        static CCSprite* fillRect( CCSprite* sprite, CCLayer * layerid, float x, float y, float w, float h, int opacity, int zorder, ccColor3B color );

    
        // タグ付き文字列の描画
       
        static StringLabelList* initString( CCLayer * layerid,string str, float x, float y, float w, float h, ccColor3B base_color, int base_anc, int font_size );
        static StringLabelList* initString( CCLayer * layerid,string str, float x, float y, float w, float h, ccColor3B base_color, int base_anc, int font_size, int line_space );

        static StringLabelList* initString( CCLayer * layerid,string str, float x, float y, float w, float h, ccColor3B base_color, int base_anc, int font_size, int line_space, bool auto_kaigyou );

        static StringLabelList* initString( CCLayer * layerid,string str, float x, float y, float w, float h, ccColor3B base_color, int base_anc, int font_size, int line_space, bool auto_kaigyou, bool useTag );

        static StringLabelList* drawString( CCLayer * layerid,string str, float x, float y, ccColor3B base_color, int base_anc, int font_size );
        static StringLabelList* drawString( CCLayer * layerid,string str, float x, float y, ccColor3B base_color, int base_anc, int font_size, int line_space );
        static StringLabelList* drawString( CCLayer * layerid,string str, float x, float y, float w, float h, ccColor3B base_color, int base_anc, int font_size );
        static StringLabelList* drawString( CCLayer * layerid,string str, float x, float y, float w, float h, ccColor3B base_color, int base_anc, int font_size, int line_space );
    
        static StringLabelList* drawString( CCLayer * layerid,string str, float x, float y, float w, float h, ccColor3B base_color, int base_anc, int font_size, int line_space, bool auto_kaigyou );

    
        static StringLabelList* drawString( CCLayer * layerid,string str, float x, float y, float w, float h, ccColor3B base_color, int base_anc, int font_size, int line_space, bool auto_kaigyou, bool useTag );
    

    
        // 文字列幅の取得
        static float getStringWidth( string str, int fontsize );

        // 汎用フレームの描画
        static void drawWideUseFrame( CCLayer * layerid,  float x, float y, float w, float h );
        // 短形の描画
        static GlDrawRect* drawRect( CCLayer * layerid, float x, float y, float w, float h, int size, ccColor3B color );
    
	protected:

	private:
    
        //static void drawStringLine( CCLayer * layerid, string str, float x, float y, float w, float h, ccColor3B color, int anc, int font_size );
        
        // 文字列のタグ解析
        //static CCMutableArray<ColorString*> *parseTagString( string str, ccColor3B base_color,  int bsse_font_size );
    

};

#endif
