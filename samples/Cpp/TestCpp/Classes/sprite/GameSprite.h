//
//  GameSprite.h
//  SampleGame2
//
//  Created by 杉山 浩 on 12/03/24.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef BraveFrontier_GameSprite_h
#define BraveFrontier_GameSprite_h

#include "cocos2d.h"

class TouchObject;

USING_NS_CC;

class GameSprite : public CCSprite
{
    public:
        // コンストラクタ
        GameSprite();
        // デストラクタ
        ~GameSprite();
        // スプライト初期化処理
        static GameSprite* init( const char *filename);
        static GameSprite* init( CCTexture2D *texture, CCRect rect );
        static GameSprite* initWithFrameName( string name );
    
    
        //static GameSprite* initForResource( const char *filename);
        //static GameSprite* initForLocal( const char *filename);
    
        static GameSprite* init( CCTexture2D *texture); 
        static GameSprite* initWithSize( CCTexture2D *texture, float w, float h );
        
    
    
        // 座標設定
        void setPosition( float x, float y );
        void setPositionX( float x );
        void setPositionY( float y );
        
        // 幅、高さの設定
        void setWidth( float w );
        void setHeight( float h );
        void setSize( float w, float h );
    
    
        // 座標の加算
        void incPosition( float x, float y );
        // gl x座標取得
        int getGlPositionX();
        // gl y座標取得
        int getGlPositionY();
        // x座標取得
        float getPositionX();
        // y座標取得
        float getPositionY();
        // 幅取得
        int getWidth();
        // 高さ取得
        int getHeight();
        // Left座標取得
        int getLeft();
        // Top座標取得
        int getTop();
        // レイヤーIDの設定
        void setLayerId( int value );
        // スプライトIDの取得
        //int getSpriteId();
        // レイヤーIDの取得
        int getLayerId();
        // カラーをクリア
        void clearColor();
        // 管理IDを設定
        void setMngID( string value );
        // 管理IDを取得
        string getMngID();
        // マスク設定
        void setMask();
        // マスク設定
        void clearMask();
    
        void setCachePos();
        float getCachePosX();
        float getCachePosY();
    
        // アニメスプライトを設定
        void setAnimeSprite( GameSprite* sprite );
        // アニメスプライトを取得
        GameSprite* getAnimeSprite();
    
        void setFileName( string name );
        string getFileName();
    
        //void draw();
        // デフォルトの透明度設定
        void setDefaultOpacity( int value );
        // デフォルトの透明度取得
        int getDefaultOpacity();

        // 汎用パラメータ
        int compParam1;
        int compParam2;

        string compParamStr1;

    protected:
    
    
    private:
    
        // タッチ領域の設定
        void setTouchRect();
        // 
    
        // レイヤーID
        int layerId;
    
        // スプライト座標
        float spx;
        float spy;
    
        // 管理ID
        string mngID;
    
        CCPoint cachePos;
    
        // アニメーションスプライト
        GameSprite* animeSprite;
    
        string fileName;
    
        int deafaultOpacity;
};


#endif
