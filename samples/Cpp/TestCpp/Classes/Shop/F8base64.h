#import <Foundation/Foundation.h>

// 64進数のchar値を6bitの数値に変換するためのテーブル
// 64進数の並びは 0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ
// 通常のbase64エンコードとは文字の割当が違うので注意
//const char tableForF8Base64CharToDec[256];

// 6bitバイナリを64進数のchar値に変換するためのテーブル
// 64進数の並びは 0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ
// 通常のbase64エンコードとは文字の割当が違うので注意
//const char tableForDecToF8Base64Char[64];

// 64進数のchar値を6bit数値に変換するためのテーブル
//const char tableForBase64CharToDec[256];

// 6bitバイナリを64進数のchar値に変換するためのテーブル
//const char tableForDecToBase64Char[64];

// 64進数char文字列を 数値に変換する
NSUInteger F8Base64CharsToDec (const char *cp);
NSUInteger base64CharsToDec (const char *cp);

// 数値を 64進数文字列に変換する
NSString* decToF8Base64String (NSUInteger dec);
NSString* decToBase64String (NSUInteger dec);


@interface NSData (NSDataF8Base64)

// 自作のbase64デコード
// パッディングなし
+ (NSData *)dataWithF8Base64String:(NSString *)base64String;

// 普通のbase64デコード
// 引数には 無改行のbase64文字列を入れる
// 改行などは無視されずに 0 として扱うので注意
// 引数がbase64文字列として正しいかはチェックしません
+ (NSData *)dataWithBase64String:(NSString *)base64String;


// 自作のbase64エンコード
// パッディングなし
- (NSString *)F8Base64String;


// 普通のbase64エンコード
// 無改行の一般的なbase64文字列を返す
- (NSString *)base64String;


@end