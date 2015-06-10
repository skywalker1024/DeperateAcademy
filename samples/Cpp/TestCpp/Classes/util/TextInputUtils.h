//
//  TextInputUtils.h
//  BraveFrontier
//
//  Created by kyogoku on 2013/05/22.
//
//

#ifndef __BraveFrontier__TextInputUtils__
#define __BraveFrontier__TextInputUtils__

#include "cocos2d.h"

USING_NS_CC;

class TextInputUtils
{
public:
    // テキストモード
    enum TEXT_MODE
    {
        MODE_ALL,
        MODE_NO_SYMBOL,
        MODE_HALF_NUMERIC,
        MODE_HALF_CHARACTER,
        MODE_SYSTEM_PROHIBITION,
    };
    // テキストにフィルターをかける
    static string filterText( string key, int limit, TEXT_MODE text_mode );
    // 文字数をカウント
    static int count( string key );
    // パスワードチェック[半角英数以外が含まれていたらfalse]
    static bool checkPassword( string text );
    // NGワードチェック
    static bool checkNgWord( string text );
    // 文字置換
    static string replace( string text, string from, string to );
    
protected:
    
private:
    static list<const char*> getNgWords();
};

#endif /* defined(__BraveFrontier__TextInputUtils__) */
