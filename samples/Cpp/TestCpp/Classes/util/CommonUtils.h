//
//  CommonUtils.h
//  SampleGame2
//
//  Created by 株式会社 ウィルアーク on 3/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef BraveFrontier_CommonUtils_h
#define BraveFrontier_CommonUtils_h

#include "cocos2d.h"

USING_NS_CC;

//stringと数値の相互変換
#define itos(i) ( CommonUtils::IntToString(i) )
#define lltos(ll) ( CommonUtils::LLToString(ll) )
#define stoi(s) ( CommonUtils::StrToInt(s) )
#define stof(s) ( CommonUtils::StrToFloat(s) )
#define stol(s) ( CommonUtils::StrToLong(s) )
#define stoll(s) ( CommonUtils::StrtoLL(s) )

class CommonUtils
{
public:
    
    /* 共通 */
    
    // 数値から文字列への変換
    static string IntToString( int number );
    static const char* IntToCString( int number );
    static string FloatToString( float number );
    // 文字列から数値への変換
    static int StrToInt( const string &str );
    static int StrToInt( const char* str );
        static unsigned int StrToUInt( const string &str );
    static float StrToFloat( const string &str );
    static float StrToFloat( const char* str );
    static long StrToLong( const string &str );
    // 文字列結合
    static string appendStr( const char* str1, const char* str2 );
    // 文字列分割
    static vector<string> split( const string &str, const char* delim );
    static float getStringWidth( const string &str, int fontsize );
    
    static int getScreenWidth();
    static int getScreenHeight();
};

#endif
