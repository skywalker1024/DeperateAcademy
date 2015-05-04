//
//  SaveUtils.h
//  BraveFrontier

//  Created by WillArk on 5/6/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_SaveUtils_h
#define BraveFrontier_SaveUtils_h

#include "cocos2d.h"

USING_NS_CC;

class SaveUtils : public CCObject
{
	public:
        // セーブ処理
        static void saveUserDefaults( string key, string value, bool bySection = false );
		// ロード処理
        static const char* loadUserDefaults( string key, bool bySection = false);
        // キーチェーンへのセーブ処理
        static void saveKeyChain( const char* service_name, string account_name, string password ); 
        // キーチェーンからのロード処理
        static CCArray* loadKeyChain( const char* service_name ); 
        // キーチェーンを削除
        static void deleteKeyChain( string account, const char* service_name );
    
        static const char* loadAccontNameFromKeyChain( const char *service_name );
        // アカウント名の取得。
        static string getAccontNameFromKeyChain( const char *service_name );
        // パスワードの取得。
        static string getPasswordFromKeyChain( const char *service_name );
    
        static void saveIdentifierForVendorIntoKeyChain(std::string identifier);
        static string getIdentifierForVendorFromKeyChain();
    
        static string loadUserString(string key, bool bySection = false);
	protected:

	private:
        static string getSectionKey(string key, bool bySection);
};

#endif
