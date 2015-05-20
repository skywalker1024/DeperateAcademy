//
//  UserState.cpp
//  BraveFrontier

//  Created by WillArk on 5/31/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "UserState.h"


UserState* UserStateInstance = NULL;

/*
 * シングルトンインスタンスを取得。
 */
UserState* UserState::shared()
{
	if( UserStateInstance == NULL )
	{
		UserStateInstance= new UserState();
	}
    
	return UserStateInstance;
}

void UserState::destroy()
{
    CC_SAFE_DELETE(UserStateInstance);
}

/*
 * コンストラクタ。
 */
UserState::UserState()
{
    m_purchaseConnectFlg = false;
}

/*
 * デストラクタ。
 */
UserState::~UserState()
{
    
}



