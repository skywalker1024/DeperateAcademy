//
//  WideUseFrame.h
//  BraveFrontier
//
//  Created by 本山 順一 on 13/01/22.
//
//

#ifndef BraveFrontier_WideUseFrame_h
#define BraveFrontier_WideUseFrame_h

#include "cocos2d.h"
#include "GameSprite.h"

USING_NS_CC;

class WideUseFrame : public CCObject
{
    public:
        // コンストラクタ
        WideUseFrame();
        // デストラクタ
        ~WideUseFrame();
    
        // 初期化
        static WideUseFrame* init( CCLayer * layerid, float x, float y, float w, float h );
        // 描画処理
        void draw();
    
        // ｘ座標の取得
        float getX();
        // ｘ座標の設定
        void setX( float value );
        // ｙ座標の取得
        float getY();
        // ｙ座標の設定
        void setY( float value );
        // 幅の取得
        float getWidth();
        // 幅の設定
        void setWidth( float value );
        // 高さの取得
        float getHeight();
        // 高さの設定
        void setHeight( float value );
        // レイヤーIDの取得
        CCLayer * getLayerID();
        // レイヤーIDの設定
        void setLayerID( CCLayer * value );
        // 表示設定
        void setIsVisible( bool value );
        // 表示設定を取得
        void getIsVisible();
        // ベースカラー設定
        void setBaseColor( ccColor3B color );
    
    
    protected:
    
    private:
        //  スプライト生成
        void createSprite();
    
        // ｘ座標
        float x;
        // ｙ座標
        float y;
        // 幅
        float width;
        // 高さ
        float height;
    
        // ベーススプライト
        GameSprite* baseSprite;
    
        // レイヤーID
        CCLayer * layerID;
        // スプライトリスト
        CCMutableArray<GameSprite*> *spriteList;
};

#endif
