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

#include "Json.h"
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
    static string getChannelUserId();
    static string getDeviceID();
    
    static bool ReadIntoJson(std::vector<char> *buffer, Json::Value &root, bool debugOutput = false);
    static vector<string> * getCsvList( string path );
    static int getRandom( int min, int max );
    static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
    static std::vector<std::string> split(const std::string &s, char delim);
    static void showAlert();
    static string stringFormat( int value, int keta );
    static long getCurrentTime();
    static bool checkoutPaymentID(string aPaymentID);
    static void startCheckID();
    static void talkingDataCpaOnPay(const char * orderId,int amount,const char * currencyType,const char * payType);
    static void paymentRequest(string purchaseId);
};

#endif
