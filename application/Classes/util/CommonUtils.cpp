//
//  CommonUtils.cpp
//  SampleGame2
//
//  Created by 株式会社 ウィルアーク on 3/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CommonUtils.h"
#include "StringComparator.h"
/*
 * 数値から文字列への変換。
 */
string CommonUtils::IntToString( int number )
{
    stringstream ss;
    ss << number;
    return ss.str();
}

/*
 * 数値から文字列への変換。
 */
const char* CommonUtils::IntToCString( int number )
{
	static string tempbuffer;
	tempbuffer = IntToString( number );
    return tempbuffer.c_str();
}

/*
 * 数値から文字列への変換。
 */
string CommonUtils::FloatToString( float number )
{
    stringstream ss;
    ss << number;
    return ss.str();
}

/*
 * 文字列から数値への変換。
 */
int CommonUtils::StrToInt( const string &str )
{
    int ret = 0;
    
    stringstream ss;
    ss << str;
    ss >> ret;
    
    return ret;
}

/*
 * 文字列から数値への変換。
 */
int CommonUtils::StrToInt( const char* str )
{
    int ret = 0;
    
    stringstream ss;
    ss << string( str );
    ss >> ret;
    
    return ret;
}

/*
 * 文字列から数値への変換。
 */
unsigned int CommonUtils::StrToUInt( const string &str )
{
    unsigned int ret = 0;
    
    stringstream ss;
    ss << str;
    ss >> ret;
    
    return ret;
}

/*
 * 文字列から数値への変換。
 */
float CommonUtils::StrToFloat( const string &str )
{
    float ret = 0;
    
    stringstream ss;
    ss << str;
    ss >> ret;
    
    return ret;
}

/*
 * 文字列から数値への変換。
 */
float CommonUtils::StrToFloat( const char* str )
{
    float ret = 0;
    
    stringstream ss;
    ss << string( str );
    ss >> ret;
    
    return ret;
}

/*
 * 文字列から数値への変換。
 */
long CommonUtils::StrToLong( const string &str )
{
    long ret = 0;
    
    stringstream ss;
    ss << string( str );
    ss >> ret;
    
    return ret;
}

/*
 * 文字列結合。
 */
string CommonUtils::appendStr( const char* str1, const char* str2 )
{
    return string(str1) + str2;
}

/*
 * 文字列分割。
 */
vector<string> CommonUtils::split( const string &str, const char* delim)
{
    vector<string> result;
    size_t current = 0, found;
    
    while( ( found = str.find_first_of( delim, current ) ) != string::npos )
    {
        result.push_back( string( str, current, found - current ) );
        current = found + 1;
    }
    
    result.push_back( string( str, current, str.size() - current ) );
    
    return result;
}

/*
 * 文字列幅の取得。
 */
float CommonUtils::getStringWidth( const string &str, int fontsize )
{
    float width = 0;
    
    vector< string > sList = StringComparator::comparate( str );
    
    for( int i = 0; i < sList.size(); i++ )
    {
        float font_width = fontsize;
        
        // 半角
        if( sList[i].length() == 1 )
        {
            width += ((font_width/3)*2);
        }
        // 全角
        else
        {
            width += font_width;
        }
    }
    
    return width;
}
