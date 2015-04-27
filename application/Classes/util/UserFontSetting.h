//
//  UserFontSetting.h
//  BraveFrontier

//  Created by WillArk on 2/27/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_UserFontSetting_h
#define BraveFrontier_UserFontSetting_h

#include "cocos2d.h"

USING_NS_CC;

class UserFontSetting : public CCObject
{
	public:
		// インスタンスの取得
		static UserFontSetting* shared();
		// デフォルトフォント名の取得
		string getDefaultFont();
		// デフォルトフォント名の設定
		void setDefaultFont( string value );
		// 有効なフォントファイル名の取得
		string getActiveFont();
		// 有効なフォントファイル名の設定
		void setActiveFont( string value );
        // デフォルトフォントに戻す
        void resetFont();
    
	protected:

	private:
		// コンストラクタ
		UserFontSetting();
		// デストラクタ
		~UserFontSetting();
		// デフォルトフォント名
		string defaultFont;
		// 有効なフォントファイル名
		string activeFont;

};

#endif

