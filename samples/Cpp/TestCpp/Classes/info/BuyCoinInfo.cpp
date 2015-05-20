//
//  BuyCoinInfo.cpp
//  BraveFrontier

//  Created by WillArk on 6/6/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "BuyCoinInfo.h"

// シングルトンインスタンス
BuyCoinInfo* buyCoinInfoInstance = NULL;

/**
 * シングルトンインスタンスを取得
 */
BuyCoinInfo* BuyCoinInfo::shared()
{
    if( buyCoinInfoInstance == NULL )
    {
        buyCoinInfoInstance = new BuyCoinInfo();
    }
    
    return buyCoinInfoInstance;
}

/*
 * コンストラクタ。
 */
BuyCoinInfo::BuyCoinInfo()
{
    m_purchaseState = 0;
}

/*
 * デストラクタ。
 */
BuyCoinInfo::~BuyCoinInfo()
{

}