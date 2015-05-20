//
//  UserState.h
//  BraveFrontier

//  Created by WillArk on 5/31/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_UserState_h
#define BraveFrontier_UserState_h

#include "cocos2d.h"

USING_NS_CC;

class UserState : public CCObject
{
	public:
		// インスタンスの取得
		static UserState* shared();
    
        static void destroy();
    
private:
    // コンストラクタ
    UserState();
    // デストラクタ
    ~UserState();
    CC_SYNTHESIZE(bool, m_purchaseConnectFlg, PurchaseConnectFlg);
};
#endif
