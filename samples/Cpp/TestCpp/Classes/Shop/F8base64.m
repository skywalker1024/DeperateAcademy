#import "F8Base64.h"

// 64進数のchar値を6bitの数値に変換するためのテーブル
// 64進数の並びは 0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ
const char tableForF8Base64CharToDec[256] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,62, 0, 0,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0,
    0,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,
    51,52,53,54,55,56,57,58,59,60,61,0, 0, 0, 0,63,
    0,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,
    25,26,27,28,29,30,31,32,33,34,35,0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// 6bitバイナリを64進数のchar値に変換するためのテーブル
// 64進数の並びは 0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ
const char tableForDecToF8Base64Char[64] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
    'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '-', '_',
};

// 64進数のchar値を6bit数値に変換するためのテーブル
const char tableForBase64CharToDec[256] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,62, 0, 0, 0,63,
    52,53,54,55,56,57,58,59,60,61, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,
    15,16,17,18,19,20,21,22,23,24,25,0, 0, 0, 0, 0,
    0,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
    41,42,43,44,45,46,47,48,49,50,51,0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// 6bitバイナリを64進数のchar値に変換するためのテーブル
const char tableForDecToBase64Char[64] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/',
};


// 64進数char文字列を数値に変換
NSUInteger F8Base64CharsToDec (const char *cp) {
    NSUInteger dec = 0;
    for (NSUInteger i = 0, l = strlen(cp); i < l; i++) {
        dec = (dec << 6) + tableForF8Base64CharToDec[cp[i]];
    }
    return dec;
}

NSUInteger base64CharsToDec (const char *cp)  {
    NSUInteger dec = 0;
    for (NSUInteger i = 0, l = strlen(cp); i < l; i++) {
        dec = (dec << 6) + tableForBase64CharToDec[cp[i]];
    }
    return dec;
}


// 上の関数とは変換テーブルが違うだけ
NSString* decToF8Base64String ( NSUInteger dec ) {
    
    if ( dec == 0 ) return @"0";
    
    // NSINteger は 32 or 64ビット で 64 は 6ビットなので char[6] あれば int 値を表現可能
    // 従って 6 + 1 (文字列終端）= 7を使う
    char _c[7], c[7];
    NSInteger counter = 0;
    
    while( dec ) {
        _c[counter++] = dec % 64;
        dec /= 64;
    }
    
    NSInteger i = 0;
    while ( counter-- ) {
        c[i++] = tableForDecToF8Base64Char[_c[counter]];
    }
    c[i] = 0; // 文字終端
    
    return [NSString stringWithUTF8String:c];
}


// 上の関数とは変換テーブルが違うだけ
NSString* decToBase64String ( NSUInteger dec ) {
    
    if ( dec == 0 ) return @"0";
    
    char _c[7], c[7];
    NSInteger counter = 0;
    
    while( dec ) {
        _c[counter++] = dec % 64;
        dec /= 64;
    }
    
    NSInteger i = 0;
    while ( counter-- ) {
        c[i++] = tableForDecToBase64Char[_c[counter]];
    }
    c[i] = 0; // 文字終端
    
    return [NSString stringWithUTF8String:c];
}



@implementation NSData (NSDataF8Base64)

+ (NSData *)dataWithF8Base64String:(NSString *)base64String {
    
    const char *cp = [base64String UTF8String];
    
    NSUInteger len = strlen(cp), remainder = len % 4;
    NSMutableData *data = [NSMutableData dataWithCapacity:len / 4 * 3 + (remainder + 1) / 2];
    NSUInteger i = 0, bin24, l = len / 4;
    unsigned char char3[3];
    
    while ( i < l ) {
        bin24 = tableForF8Base64CharToDec[cp[i*4]] << 18
        | tableForF8Base64CharToDec[cp[i*4 + 1]] << 12
        | tableForF8Base64CharToDec[cp[i*4 + 2]] << 6
        | tableForF8Base64CharToDec[cp[i*4 + 3]];
        i++;
        char3[0] = (bin24 >> 16) & 255;
        char3[1] = (bin24 >> 8) & 255;
        char3[2] = bin24 & 255;
        [data appendBytes:char3 length:3];
    }
    
    if ( remainder == 2 ) {
        bin24 = (tableForF8Base64CharToDec[cp[i*4]] << 6 | tableForF8Base64CharToDec[cp[i*4 + 1]]) >> 4;
        char3[0] = bin24;
        [data appendBytes:char3 length:1];
        
    } else if ( remainder == 3 ) {
        
        bin24 = (tableForF8Base64CharToDec[cp[i*4]] << 12 | tableForF8Base64CharToDec[cp[i*4 + 1]] << 6 | tableForF8Base64CharToDec[cp[i*4 + 2]]) >> 2;
        char3[0] = bin24 >> 8;
        char3[1] = bin24 & 255;
        [data appendBytes:char3 length:2];
        
    } else {
        // remainder == 1 の場合その余りは不正なので無視
    }
    
    return [NSData dataWithData:data];
}


+ (NSData *)dataWithBase64String:(NSString *)base64String {
    
    const char *cp = [base64String UTF8String];
    NSUInteger padCnt = 0;
    if ( cp[strlen(cp) - 1] == '=' ) {
        padCnt++;
    }
    if ( cp[strlen(cp) - 2] == '=' ) {
        padCnt++;
    }
    
    NSUInteger len = strlen(cp);
    NSMutableData *data = [NSMutableData dataWithCapacity:len / 4 * 3 - padCnt];
    NSUInteger i = 0, bin24, l = len / 4 - 1;
    unsigned char char3[3];
    
    while ( i < l ) {
        bin24 = tableForBase64CharToDec[cp[i*4]] << 18
        | tableForBase64CharToDec[cp[i*4 + 1]] << 12
        | tableForBase64CharToDec[cp[i*4 + 2]] << 6
        | tableForBase64CharToDec[cp[i*4 + 3]];
        i++;
        char3[0] = (bin24 >> 16) & 255;
        char3[1] = (bin24 >> 8) & 255;
        char3[2] = bin24 & 255;
        [data appendBytes:char3 length:3];
    }
    
    if ( padCnt == 2 ) {
        bin24 = (tableForBase64CharToDec[cp[i*4]] << 6 | tableForBase64CharToDec[cp[i*4 + 1]]) >> 4;
        char3[0] = bin24;
        [data appendBytes:char3 length:1];
        
    } else if ( padCnt == 1 ) {
        
        bin24 = (tableForBase64CharToDec[cp[i*4]] << 12 | tableForBase64CharToDec[cp[i*4 + 1]] << 6 | tableForBase64CharToDec[cp[i*4 + 2]]) >> 2;
        char3[0] = bin24 >> 8;
        char3[1] = bin24 & 255;
        [data appendBytes:char3 length:2];
        
    } else {
        // remainder == 1 の場合その余りは不正なので無視
    }
    
    return [NSData dataWithData:data];
}



- (NSString *)F8Base64String {
    
    const unsigned char *cp = [self bytes];
    NSUInteger len = [self length], remainder = len % 3;
    NSMutableData *data = [NSMutableData dataWithCapacity:len / 3 * 4 + (remainder ? 0 : remainder + 1)];
    
    NSUInteger i = 0, bin24, l = len / 3;
    while ( i < l ) {
        bin24 = cp[i*3] << 16 | cp[i*3 + 1] << 8 | cp[i*3 + 2];
        i++;
        [data appendBytes:&tableForDecToF8Base64Char[(bin24 >> 18) & 63] length:1];
        [data appendBytes:&tableForDecToF8Base64Char[(bin24 >> 12) & 63] length:1];
        [data appendBytes:&tableForDecToF8Base64Char[(bin24 >> 6) & 63] length:1];
        [data appendBytes:&tableForDecToF8Base64Char[bin24 & 63] length:1];
    }
    
    if ( remainder == 1 ) {
        bin24 = cp[i*3] << 4;
        [data appendBytes:&tableForDecToF8Base64Char[bin24 >> 6] length:1];
        [data appendBytes:&tableForDecToF8Base64Char[bin24 & 63] length:1];
        
    } else if ( remainder == 2 ) {
        bin24 = (cp[i*3] << 8 | cp[i*3 + 1]) << 2;
        [data appendBytes:&tableForDecToF8Base64Char[bin24 >> 12] length:1];
        [data appendBytes:&tableForDecToF8Base64Char[(bin24 >> 6) & 63] length:1];
        [data appendBytes:&tableForDecToF8Base64Char[bin24 & 63] length:1];
    }
    
    // 文字終端
    const char nullByte = 0;
    [data appendBytes:&nullByte length:1];
    
    return [NSString stringWithUTF8String:(const char *)[data bytes]];
}

- (NSString *)base64String {
    
    const unsigned char *cp = [self bytes];
    NSUInteger len = [self length], remainder = len % 3;
    NSMutableData *data = [NSMutableData dataWithCapacity:len / 3 * 4 + (remainder ? 0 : 4) + 1];
    
    NSUInteger i = 0, bin24, l = len / 3;
    while ( i < l ) {
        bin24 = cp[i*3] << 16 | cp[i*3 + 1] << 8 | cp[i*3 + 2];
        i++;
        [data appendBytes:&tableForDecToBase64Char[(bin24 >> 18) & 63] length:1];
        [data appendBytes:&tableForDecToBase64Char[(bin24 >> 12) & 63] length:1];
        [data appendBytes:&tableForDecToBase64Char[(bin24 >> 6) & 63] length:1];
        [data appendBytes:&tableForDecToBase64Char[bin24 & 63] length:1];
    }
    
    if ( remainder == 1 ) {
        bin24 = cp[i*3] << 4;
        [data appendBytes:&tableForDecToBase64Char[bin24 >> 6] length:1];
        [data appendBytes:&tableForDecToBase64Char[bin24 & 63] length:1];
        [data appendBytes:[@"==" UTF8String] length:2];
        
    } else if ( remainder == 2 ) {
        bin24 = (cp[i*3] << 8 | cp[i*3 + 1]) << 2;
        [data appendBytes:&tableForDecToBase64Char[bin24 >> 12] length:1];
        [data appendBytes:&tableForDecToBase64Char[(bin24 >> 6) & 63] length:1];
        [data appendBytes:&tableForDecToBase64Char[bin24 & 63] length:1];
        [data appendBytes:[@"=" UTF8String] length:1];
    }
    
    // 文字終端
    const char nullByte = 0;
    [data appendBytes:&nullByte length:1];
    
    return [NSString stringWithUTF8String:(const char *)[data bytes]];
}

@end