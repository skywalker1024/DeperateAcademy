//
//  CommonUtils.cpp
//  SampleGame2
//
//  Created by 株式会社 ウィルアーク on 3/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CommonUtils.h"
#include "StringComparator.h"
#include "SaveUtils.h"

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


/*
 * スクリーン幅を取得。
 */
int CommonUtils::getScreenWidth()
{
    return CCDirector::sharedDirector()->getWinSize().width;
}


/*
 * スクリーン高さを取得。
 */
int CommonUtils::getScreenHeight()
{
    return CCDirector::sharedDirector()->getWinSize().height;
}

std::string CommonUtils::getChannelUserId()
{
    std::string identifierForVendor = SaveUtils::getIdentifierForVendorFromKeyChain();
    if (identifierForVendor == "") {
        identifierForVendor = CommonUtils::getDeviceID();
        if (identifierForVendor != "") {
            SaveUtils::saveIdentifierForVendorIntoKeyChain(identifierForVendor);
        }
    }
    //    printf("identifierForVendor = %s\n", identifierForVendor.c_str());
    return identifierForVendor;
}

bool CommonUtils::ReadIntoJson(std::vector<char> *buffer, Json::Value &root, bool debugOutput)
{
    //creating a const char holder for the downloaded data
    std::string stringHolder = "";
    
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        stringHolder += (*buffer)[i];
    }
    
    //reader will contain the extracted data in json format
    Json::Reader reader = Json::Reader();
    bool readerStatus = reader.parse(stringHolder, root);
    
    if (debugOutput) {
        Json::StyledWriter styledWriter = Json::StyledWriter();
        CCLOG("*****start of json***** %s", styledWriter.write(root).c_str() );    }
    
    return readerStatus;
}

vector<string> * CommonUtils::getCsvList( string path )
{
    vector<string> * csvlist = new vector<string>;
    
    //CCLog( "###CommonUtils::getCsvList path=%s", path.c_str() );
    
    // 読み込んだテキストの文字列データ
    unsigned long size = 0;
    unsigned char * pLoadedChar = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "r", &size);
    std::string * pLoadedString = new string((const char *)pLoadedChar, size);
    int spos = 0;
    CCLog("pLoadedString=%s pLoadedChar=%s",pLoadedString->c_str(), pLoadedChar);
    for( ;; )
    {
        // 改行コードで分割
        int kidx = pLoadedString->find_first_of("\n", spos );
        
        if( kidx == string::npos )
            break;
        
        string linestr = pLoadedString->substr( spos, kidx - spos );
        spos += ( kidx - spos );
        spos++;
        
        //将linestr中的\r替换掉
        int r_pos = 0;
        int r_index = linestr.find_first_of("\r", r_pos);
        if( r_index != string::npos ){
            linestr = linestr.substr(0, r_index);
        }
        csvlist->push_back(linestr);
    }
    
    delete pLoadedString;
    
    return csvlist;
}

int CommonUtils::getRandom( int min, int max )
{
    if( min > max )
    {
        int value = min;
        
        min = max;
        max = value;
    }
    
    int rand = 0;
    
    for( int i = 0; i < 10; i++ )
    {
        rand = arc4random() % ( ( max - min ) + 1 );
    }
    
    return rand + min;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

string CommonUtils::stringFormat( int value, int keta )
{
    ostringstream oss;
    oss.setf(ios::right); // 右詰め
    oss.fill('0'); // 0埋め
    oss.width(keta); // 桁数
    oss << value;
    string str = oss.str();
    
    return str;
}

long CommonUtils::getNowUnitxTime()
{
    struct timeval tim;
    gettimeofday(&tim, NULL);
    return tim.tv_sec;
}