//
//  BaseRequest.h
//  BraveFrontier

//  Created by WillArk on 11/13/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_BaseRequest_h
#define BraveFrontier_BaseRequest_h

#include "cocos2d.h"

USING_NS_CC;


class BaseRequest : public CCObject
{
public:
    // コンストラクタ
    BaseRequest();
    // デストラクタ
    ~BaseRequest();

    string getFullUrl();
    string getFullData();
protected:

private:
    CC_SYNTHESIZE(string, m_url, Url);
    CC_SYNTHESIZE(string, m_data, Data);
};

#endif

