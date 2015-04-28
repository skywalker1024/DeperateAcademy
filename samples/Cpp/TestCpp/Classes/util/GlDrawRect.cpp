//
//  GlDrawRect.cpp
//  BraveFrontier

//  Created by WillArk on 2/11/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "GlDrawRect.h"

/*
 * コンストラクタ。
 */
GlDrawRect::GlDrawRect( float x, float y, float w, float h, float size, ccColor3B color )
{
    autorelease();
    
    this->x      = x;
    this->y      = y;
    this->width  = w;
    this->height = h;
    this->size   = size;
    this->color  = color;
    
    
}

/*
 * デストラクタ。
 */
GlDrawRect::~GlDrawRect()
{

}

/*
 * 描画処理。
 */
void GlDrawRect::draw()
{
    CCPoint cp = ccp( x, y );
    
    cp = CCDirector::sharedDirector()->convertToGL( cp );
    
    
    float xx = cp.x;
    float yy = cp.y;
    float ww = width ;
    float hh = height;

    ccDrawColor4B(color.r, color.g, color.b, 255);
    glLineWidth(1);

    for( int i = 0; i < size; i++ )
    {
        
        CCPoint vertices[] = { ccp(xx,yy), ccp(xx+ww,yy), ccp(xx+ww,yy-hh), ccp(xx,yy-hh), ccp(xx,yy) };
        ccDrawPoly( vertices, 5, true );
        
        xx += 0.5;
        yy -= 0.5;
        ww -= 1;
        hh -= 1;
    }
}


/**
 * ｘ座標の取得。
 */
float GlDrawRect::getX()
{
	return x;
}

/**
 * ｙ座標の取得。
 */
float GlDrawRect::getY()
{
	return y;
}

/**
 * 幅の取得。
 */
float GlDrawRect::getWidth()
{
	return width;
}

/**
 * 高さの取得。
 */
float GlDrawRect::getHeight()
{
	return height;
}

/**
 * カラーの取得。
 */
ccColor3B GlDrawRect::getColor()
{
	return color;
}


