//
//  ResponseParser.h
//  BraveFrontier

//  Created by WillArk on 11/13/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_ResponseParser_h
#define BraveFrontier_ResponseParser_h

#include "cocos2d.h"
USING_NS_CC;

#include "NetworkManager.h"
class LoadingLayer;
class ResponseParser : public CCObject
{
public:
    // コンストラクタ
    ResponseParser();
    // デストラクタ
    ~ResponseParser();
    CREATE_FUNC(ResponseParser);
    virtual bool init();
    void ResponseParse(CCHttpClient* client, CCHttpResponse* response);
protected:

};

#endif

