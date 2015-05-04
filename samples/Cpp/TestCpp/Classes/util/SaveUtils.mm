//
//  SaveUtils.cpp
//  BraveFrontier

//  Created by WillArk on 5/6/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "SaveUtils.h"
#import "LKKeychain.h"

/*
 * キーチェーンへのセーブ処理。
 * service_name:サービス名。
 * account_name:アカウント名。
 * password:パスワード。
 */
void SaveUtils::saveKeyChain( const char* service_name, string account_name, string password )
{
    NSString *ns_service = [ NSString stringWithCString:service_name encoding:NSUTF8StringEncoding ]; 
    NSString *ns_name = [ NSString stringWithCString:account_name.c_str() encoding:NSUTF8StringEncoding ]; 
    NSString *ns_pass = [ NSString stringWithCString:password.c_str() encoding:NSUTF8StringEncoding ]; 
     
    [ LKKeychain updatePassword:ns_pass account:ns_name service:ns_service ];    
}

/*
 * キーチェーンからのロード処理。
 */
CCArray* SaveUtils::loadKeyChain( const char* service_name )
{
    //CCLog( " -----------------" );
    //CCLog( " loadKeyChain" );
    
    NSString *ns_service = [ NSString stringWithCString:service_name encoding:NSUTF8StringEncoding ]; 

    
    NSArray* accounts = [LKKeychain getItemsWithService:ns_service];
    
    
    for( NSDictionary *d in accounts )
    {
        // キーを全て取得
        NSArray *keys = [ d allKeys ];
       
        for( int i = 0; i < [ keys count ]; i++ )
        {
            NSString *key = [ keys objectAtIndex:i ];
            NSData *value = [ d objectForKey:key ];
            
            NSLog(@" loadKeyChain key=%@ value=%@",key,value );
            
            //NSString *svalue= [[NSString alloc] initWithData:value encoding:NSUTF8StringEncoding];
            
            //const char* aaa = [ svalue cStringUsingEncoding:NSUTF8StringEncoding ];
            
            //CCLog("aaa=%s", aaa );

        }
    }
    
    return NULL;
    
}

/*
 * キーチェーンを削除。
 * account:アカウント名。
 * service_name:サービス名。
 */
void SaveUtils::deleteKeyChain( string account, const char* service_name )
{
    
     NSString *ns_account = [ NSString stringWithCString:account.c_str() encoding:NSUTF8StringEncoding ]; 
     NSString *ns_service = [ NSString stringWithCString:service_name encoding:NSUTF8StringEncoding ]; 
    
    [ LKKeychain deletePasswordWithAccount:ns_account service:ns_service ];    
}

/*
 * アカウント名の取得。
 * service_name:サービス名。
 */
std::string SaveUtils::getAccontNameFromKeyChain( const char *service_name )
{
    NSString *ns_service = [ NSString stringWithCString:service_name encoding:NSUTF8StringEncoding ]; 
    
    NSArray* accounts = [LKKeychain getItemsWithService:ns_service];
    
    const char* name = "";
    
    for( NSDictionary *d in accounts )
    {
        NSString *value = [ d objectForKey:@"acct" ];
        
        //if( value ) return [ value UTF8String ];
        name = [ value UTF8String ];
    }
    
    return name;
}


/*
 * パスワードの取得。
 * service_name:パスワード。
 */
std::string SaveUtils::getPasswordFromKeyChain( const char *service_name )
{
 
    const char* password = "";
    
    NSString *ns_service = [ NSString stringWithCString:service_name encoding:NSUTF8StringEncoding ]; 
    
    NSArray* accounts = [LKKeychain getItemsWithService:ns_service];
    
    for( NSDictionary *d in accounts )
    {
        NSString* pass = [LKKeychain getPasswordWithAccount:[ d objectForKey:(id)kSecAttrAccount] service:ns_service];
        
        password = [ pass UTF8String ];
        
    }
    
    return password;
}

void SaveUtils::saveIdentifierForVendorIntoKeyChain(std::string identifier)
{
    NSString *iden = [NSString stringWithCString:identifier.c_str() encoding:NSUTF8StringEncoding];
    NSString *service = [NSString stringWithCString:"sanguo-IdentifierForVendor" encoding:NSUTF8StringEncoding];
    [ LKKeychain updatePassword:iden account:iden service:service ];
}

std::string SaveUtils::getIdentifierForVendorFromKeyChain()
{
    const char* iden = "";
    NSString *service = [NSString stringWithCString:"sanguo-IdentifierForVendor" encoding:NSUTF8StringEncoding];
    
    NSArray* accounts = [LKKeychain getItemsWithService:service];
    
    for( NSDictionary *d in accounts )
    {
        NSString* identifier = [LKKeychain getPasswordWithAccount:[ d objectForKey:(id)kSecAttrAccount] service:service];
        
        iden = [ identifier UTF8String ];
        
    }
    
    return iden;
}

