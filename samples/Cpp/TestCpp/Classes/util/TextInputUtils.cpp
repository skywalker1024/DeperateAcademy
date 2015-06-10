//
//  TextInputUtils.cpp
//  BraveFrontier
//
//  Created by kyogoku on 2013/05/22.
//
//

#include "TextInputUtils.h"

list<const char*> TextInputUtils::getNgWords()
{
    list<const char*> ng_word_list;
    ng_word_list.push_back("hoge");
    ng_word_list.push_back("fuga");
    ng_word_list.push_back("ほげ");
    return ng_word_list;
}


string TextInputUtils::filterText( string key, int limit, TEXT_MODE text_mode )
{
    return key;
    bool half_symbol_enable = true;
    bool full_symbol_enable = true;
    bool half_numeric_enable = true;
    bool full_numeric_enable = true;
    bool half_alphabet_enable = true;
    bool full_alphabet_enable = true;
    bool half_kana_enable = true;
    bool full_kana_enable = true;
    bool kanji_enable = true;
    bool all_enable = true;
    // 絵文字はデフォルトOFF
    bool emoji_enable = false;
    bool system_enable = true;
    
    const char* buff = key.c_str();
    
    if ( buff == NULL ) return key;
    
    // モードによるフラグ操作
    if ( text_mode == MODE_NO_SYMBOL )
    {
        // 記号類はすべてなし・ほか英数字漢字かななど
        half_symbol_enable = false;
        full_symbol_enable = false;
        system_enable = false;
        all_enable = false;
    }
    if ( text_mode == MODE_HALF_NUMERIC )
    {
        // 半角数字のみ
        half_symbol_enable = false;
        full_symbol_enable = false;
        full_numeric_enable = false;
        half_alphabet_enable = false;
        full_alphabet_enable = false;
        half_kana_enable = false;
        full_kana_enable = false;
        kanji_enable = false;
        system_enable = false;
        all_enable = false;
    }
    if ( text_mode == MODE_HALF_CHARACTER )
    {
        // 半角英数字のみ
        half_symbol_enable = false;
        full_symbol_enable = false;
        full_numeric_enable = false;
        full_alphabet_enable = false;
        half_kana_enable = false;
        full_kana_enable = false;
        kanji_enable = false;
        system_enable = false;
        all_enable = false;
    }
    if ( text_mode == MODE_SYSTEM_PROHIBITION )
    {
        // システム的な禁止文字[<,#*など]
        system_enable = false;
    }
    if ( all_enable && system_enable && emoji_enable )
    {
        return key;
    }
    
    string new_string;
    int count = 0;
    int pos = 0;
    int max_bytes = strlen( buff );
    //CCLog("max_bytes:%d", max_bytes);

    
    // BOM 読み飛ばし
    if( max_bytes >= 3 )
    {
        if( static_cast<unsigned char>( buff[0] ) == 0xEF &&
           static_cast<unsigned char>( buff[1] ) == 0xBB &&
           static_cast<unsigned char>( buff[2] ) == 0xBF )
        {
            pos += 3;
        }
    }
    
    while( pos < max_bytes )
    {
        //CCLog("binary:0x%x%x%x", buff[pos]&0xff,buff[pos+1]&0xff,buff[pos+2]&0xff);

        if ( count >= limit )
        {
            break;
        }
        // 1バイト文字
        if( ( buff[pos] & 0x80 ) == 0 )
        {
            char tmp_char = static_cast<unsigned char>(buff[pos]);
            ++pos;
            bool enable_flag = false;
            if ( all_enable )
            {
                enable_flag = true;
            }
            // 半角数字
            if ( half_numeric_enable && ( tmp_char >= 0x30 && tmp_char < 0x3a ) )
            {
                enable_flag = true;
            }
            // 半角英字
            if ( half_alphabet_enable && (( tmp_char >=0x41 && tmp_char < 0x5b )
                                          || ( tmp_char >=0x61 && tmp_char < 0x7b ) ) )
            {
                enable_flag = true;
            }
            // システム予約文字の場合
            // < > # ' * , "
            if ( !system_enable && (tmp_char == 0x3C || tmp_char == 0x3E || tmp_char == 0x23 || tmp_char == 0x27 || tmp_char == 0x2A || tmp_char == 0x2C || tmp_char == 0x22))
            {
                enable_flag = false;
            }
            if ( enable_flag )
            {
                new_string.append(1, tmp_char);
                ++count; // 文字数カウント
            }
        }
        else
        {
            //2バイト文字
            if ( (buff[pos] & 0xFF) >= 0xC0 && (buff[pos] & 0xFF) <= 0xDF )
            {
                if ( all_enable )
                {
                    new_string.append(1, buff[pos]);
                    new_string.append(1, buff[pos+1]);
                    ++count; // 文字数カウント
                }
                pos += 2;
                continue;
            }
            //3バイト文字
            if ( (buff[pos] & 0xFF) >= 0xE0 && (buff[pos] & 0xFF) <= 0xEF )
            {
                //CCLog("3 bytes string");

                bool enable_flag = false;
                if ( all_enable )
                {
                    enable_flag = true;
                }
                
                // E2から始まる文字
                if ((buff[pos] & 0xFF) == 0xE2)
                {
                    // 特殊絵文字
                    if ((buff[pos+1] & 0xFF) >= 0x80 && (buff[pos+1] & 0xFF) <= 0xB9 )
                    {
                        enable_flag = emoji_enable;
                    }
                    if ((buff[pos+1] & 0xFF) >= 0xFA && (buff[pos+1] & 0xFF) <= 0xFB )
                    {
                        enable_flag = emoji_enable;
                    }
                }
                // E3から始まる文字
                if ((buff[pos] & 0xFF) == 0xE3)
                {
                    // 全角かな
                    if (full_kana_enable && (buff[pos+1] & 0xFF) >= 0x81 && (buff[pos+1] & 0xFF) <= 0x83 )
                    {
                        enable_flag = true;
                    }
                    // 特殊絵文字
                    if ((buff[pos+1] & 0xFF) == 0x80 && (buff[pos+2] & 0xFF) >= 0x83)
                    {
                        enable_flag = emoji_enable;
                    }
                    // システム禁止
                    if ( !system_enable && (buff[pos+1] & 0xFF ) == 0x82 && (buff[pos+2] & 0xFF ) >= 0x94 && (buff[pos+2] & 0xFF ) <= 0x96 )
                    {
                        enable_flag = false;
                    }
                    if ((buff[pos+1] & 0xFF) >= 0x84 && (buff[pos+1] & 0xFF) <= 0x8F )
                    {
                        enable_flag = emoji_enable;
                    }
                }
                // E4~E9から始まる文字
                if ( kanji_enable && (buff[pos] & 0xFF) >= 0xE4 && (buff[pos] & 0xFF ) <= 0xE9 )
                {
                    // 漢字
                    enable_flag = true;
                }
                // EFから始まる文字
                if ((buff[pos] & 0xFF) == 0xEF)
                {
                    // 全角英数字1
                    if ((buff[pos+1] & 0xFF) == 0xBC )
                    {
                        // 全角数字
                        if (full_numeric_enable && (buff[pos+2] & 0xFF) >= 0x90 && (buff[pos+2] & 0xFF) <= 0x99 )
                        {
                            enable_flag = true;
                        }
                        // 全角英字
                        if (full_alphabet_enable && (buff[pos+2] & 0xFF) >= 0xA1 && (buff[pos+2] & 0xFF) <= 0xBA )
                        {
                            enable_flag = true;
                        }
                    }
                    // 全角英数字2+半角カナ
                    if ((buff[pos+1] & 0xFF) == 0xBD )
                    {
                        // 全角英字
                        if (full_alphabet_enable && (buff[pos+2] & 0xFF) >= 0x81 && (buff[pos+2] & 0xFF) <= 0x9A )
                        {
                            enable_flag = true;
                        }
                        // 半角カナ
                        if (half_kana_enable && (buff[pos+2] & 0xFF) >= 0xA6 && (buff[pos+2] & 0xFF) <= 0xBF )
                        {
                            enable_flag = true;
                        }
                    }
                    // 半角カナ2
                    if ((buff[pos+1] & 0xFF) == 0xBE )
                    {
                        // 半角カナ
                        if (half_kana_enable && (buff[pos+2] & 0xFF) >= 0x80 && (buff[pos+2] & 0xFF) <= 0x9F )
                        {
                            enable_flag = true;
                        }
                    }
                }
                if ( enable_flag )
                {
                    new_string.append(1, buff[pos]);
                    new_string.append(1, buff[pos+1]);
                    new_string.append(1, buff[pos+2]);
                    ++count; // 文字数カウント
                }
                pos += 3;
                continue;
            }
            bool enable_flag = false;
            // それ以外
            if ( all_enable )
            {
                enable_flag = true;
            }
            // 特殊絵文字
            if ((buff[pos] & 0xFF) == 0xF0 && (buff[pos+1] & 0xFF) == 0x9F )
            {
                if ( emoji_enable )
                {
                    if ( !enable_flag )
                    {
                        enable_flag = true;
                    }
                }
                else
                {
                    enable_flag = false;
                }
            }
            if ( enable_flag )
            {
                ++count;
            }
            for( char tmp = buff[pos] & 0xfc; (tmp & 0x80); tmp = tmp << 1 )
            {
                if ( enable_flag )
                {
                    new_string.append(1, buff[pos]);
                }
                ++pos; // 複数バイト文字
            }
        }
    }
    //CCLog("count:%d", count);
    //CCLog("new string:%s", new_string.c_str());
    
    return new_string;
}

int TextInputUtils::count( string key )
{
    
    const char* buff = key.c_str();
    
    if ( buff == NULL ) return 0;
    
    int count = 0;
    int pos = 0;
    int max_bytes = strlen( buff );
    //CCLog("max_bytes:%d", max_bytes);

    
    // BOM 読み飛ばし
    if( max_bytes >= 3 )
    {
        if( static_cast<unsigned char>( buff[0] ) == 0xEF &&
           static_cast<unsigned char>( buff[1] ) == 0xBB &&
           static_cast<unsigned char>( buff[2] ) == 0xBF )
        {
            pos += 3;
        }
    }
    
    while( pos < max_bytes )
    {
        // 1バイト文字
        if( ( buff[pos] & 0x80 ) == 0 )
        {
            ++pos;
            ++count; // 文字数カウント
        }
        else
        {
            //2バイト文字
            if ( (buff[pos] & 0xFF) >= 0xC0 && (buff[pos] & 0xFF) <= 0xDF )
            {
                ++count; // 文字数カウント
                pos += 2;
                continue;
            }
            //3バイト文字
            if ( (buff[pos] & 0xFF) >= 0xE0 && (buff[pos] & 0xFF) <= 0xEF )
            {
                ++count; // 文字数カウント
                pos += 3;
                continue;
            }
            ++count;
            for( char tmp = buff[pos] & 0xfc; (tmp & 0x80); tmp = tmp << 1 )
            {
                ++pos; // 複数バイト文字
            }
        }
    }
    
    return count;
}

bool TextInputUtils::checkPassword( string key )
{
    const char* buff = key.c_str();
    
    if ( buff == NULL ) return false;
    
    int pos = 0;
    int max_bytes = strlen( buff );
    //CCLog("max_bytes:%d", max_bytes);

    
    // BOM 読み飛ばし
    if( max_bytes >= 3 )
    {
        if( static_cast<unsigned char>( buff[0] ) == 0xEF &&
           static_cast<unsigned char>( buff[1] ) == 0xBB &&
           static_cast<unsigned char>( buff[2] ) == 0xBF )
        {
            pos += 3;
        }
    }
    
    while( pos < max_bytes )
    {
        // 1バイト文字
        if( ( buff[pos] & 0x80 ) == 0 )
        {
            char tmp_char = static_cast<unsigned char>(buff[pos]);
            ++pos;
            bool enable_flag = false;
            // 半角数字
            if ( tmp_char >= 0x30 && tmp_char < 0x3a )
            {
                enable_flag = true;
            }
            // 半角英字
            if ( ( tmp_char >=0x41 && tmp_char < 0x5b )
                                          || ( tmp_char >=0x61 && tmp_char < 0x7b ) )
            {
                enable_flag = true;
            }
            if ( !enable_flag )
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    
    return true;
}

bool TextInputUtils::checkNgWord(string text)
{
    // NGワードをセット
    list<const char*> ng_word_list = getNgWords();
    // iterator
    list<const char*>::iterator ite = ng_word_list.begin();
    while ( ite != ng_word_list.end() )
    {
        string::size_type idx = text.find( *ite );
        if ( idx != string::npos )
        {
            return true;
            break;
        }
        ++ite;
    }
    return false;
}

string TextInputUtils::replace(string text, string from, string to)
{
    string result_str = text;
    size_t pos = 0;
    while ( pos=result_str.find(from, pos), pos != string::npos )
    {
        result_str.replace(pos, from.length(), to);
        pos += to.length();
    }
    
    return result_str;
}