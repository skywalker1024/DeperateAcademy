//
//  StringLabelList.h
//  BraveFrontier

//  Created by WillArk on 8/10/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_StringLabelList_h
#define BraveFrontier_StringLabelList_h

#include "cocos2d.h"
#include "StringLabel.h"

USING_NS_CC;

class StringLabelList : public CCNode
{
	public:
		// コンストラクタ
		StringLabelList();
		// デストラクタ
		~StringLabelList(void);
		// ベースｘ座標の取得
		float getBaseX();
		// ベースｘ座標の設定
		void setBaseX( float value );
		// ベースｙ座標の取得
		float getBaseY();
		// ベースｙ座標の設定
		void setBaseY( float value );
        // 文字列の追加
        void addObject( StringLabel* label );
        // レイヤーIDの設定
        void setLayerID( CCLayer * layer );
        // レイヤーIDの取得
        CCLayer * getLayerID();
        // ラベルリストの取得
        CCMutableArray<StringLabel*>* getLabelList();
        // 描画処理
        void draw();
        // 座標設定
        void setPosition( float x, float y );
        // ベース座標設定
        void setBasePosition( float x, float y );
        // 座標更新
        void updatePosition();
        //  透明度設定
        void setOpacity( int opacity );
        // 表示設定
        void setIsVisible( bool flg );
        // 表示設定を取得
        bool getIsVisible();
        // レイヤーから解放
        void removeLayer();
        // 文字列の変更
        void changeString( string str );
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
        // zオーダーの設定
        void setZorder( int value );
        // アクション開始
        void runStringAction( CCAction* action );
        // アクション停止
        void stopAllActions();
        // 文字列の高さを取得
        int getStringHeight();
        // 文字列の幅を取得
        int getStringWidth();

        // 影を設定
        void setShadowFlg( bool value );
        // アクション中の件数を取得
        bool isRunningAction();
        // 空文字列か
        bool empty();
        // 元の文字列取得
        string getString();
        // 自動改行フラグの設定
        void setAutoKaigyouFlg( bool flg );

        // タグ使用フラグの設定
        void setUseTagFlg( bool flg );
        CCRect getRect();

	protected:

	private:
		// ベースｘ座標
		float baseX;
		// ベースｙ座標
		float baseY;
        // レイヤーID
        CCLayer * layerID;
        // 文字列リスト
        CCMutableArray<StringLabel*> *labelList;
    
        // 描画フラグ
        bool is_draw;
        // 表示フラグ
        bool isVisible;
    
        // ベースカラー
        ccColor3B baseColor;
        // ベース表示位置
        int baseAlign;
        // ベースフォントサイズ
        int baseFontSize;
        // 描画幅
        float width;
        // 描画高さ
        float height;
        // 行間
        float lineSpace;
        // zオーダー
        int zOrder;
        // アニメ用スプライト
        CCSprite* actionSprite;
        // 透明度
        int opacity;
        // 陰フラグ
        bool shadowFlg;
        // アクションフラグ
        bool actionFlg;
        // 影用文字列

        //StringLabel* shadowLabel;
        CCMutableArray<StringLabel*>* shadowLabel;    // テキスト枠

        // フォント名
        string fontName;
        // 元の文字列
        string orgString;
        // 自動改行フラグ
        bool autoKaigyouFlg;

        // タグ使用フラグ
        bool useTag;
    
    
};

#endif
