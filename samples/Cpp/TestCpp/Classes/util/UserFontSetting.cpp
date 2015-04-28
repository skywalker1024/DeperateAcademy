//
//  UserFontSetting.cpp
//  BraveFrontier

//  Created by WillArk on 2/27/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "UserFontSetting.h"
#include "GameConst.h"


UserFontSetting* UserFontSettingInstance = NULL;

/*
 * シングルトンインスタンスを取得。
 */
UserFontSetting* UserFontSetting::shared()
{
	if( UserFontSettingInstance == NULL )
	{
		UserFontSettingInstance= new UserFontSetting();
	}

	return UserFontSettingInstance;
}

/*
 * コンストラクタ。
 */
UserFontSetting::UserFontSetting()
{
    defaultFont = DEFAULT_FONT_NAME;
    
    resetFont();
}

/*
 * デストラクタ。
 */
UserFontSetting::~UserFontSetting()
{

}

/**
 * デフォルトフォント名の取得。
 */
string UserFontSetting::getDefaultFont()
{
	return defaultFont;
}

/*
 * デフォルトフォント名の設定。
 */
void UserFontSetting::setDefaultFont( string val )
{
	defaultFont = val;
}

/**
 * 有効なフォントファイル名の取得。
 */
string UserFontSetting::getActiveFont()
{
	return activeFont;
}

/*
 * 有効なフォントファイル名の設定。
 */
void UserFontSetting::setActiveFont( string val )
{
	activeFont = val;
}

/*
 * デフォルトフォントに戻す。
 */
void UserFontSetting::resetFont()
{
    activeFont = defaultFont;
}


