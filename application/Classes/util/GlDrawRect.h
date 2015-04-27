//
//  GlDrawRect.h
//  BraveFrontier

//  Created by WillArk on 2/11/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_GlDrawRect_h
#define BraveFrontier_GlDrawRect_h

#include "cocos2d.h"

USING_NS_CC;

class GlDrawRect : public CCNode
{
	public:
		// コンストラクタ
		GlDrawRect( float x, float y, float w, float h, float size, ccColor3B color );
		// デストラクタ
		~GlDrawRect();
		// ｘ座標の取得
		float getX();
		// ｙ座標の取得
		float getY();
		// 幅の取得
		float getWidth();
		// 高さの取得
		float getHeight();
		// カラーの取得
		ccColor3B getColor();
        // 描画処理
        void draw();
    
    
	protected:

	private:
		// ｘ座標
		float x;
		// ｙ座標
		float y;
		// 幅
		float width;
		// 高さ
		float height;
		// カラー
        ccColor3B color;
        // サイズ
        float size;
    
    
};

#endif

