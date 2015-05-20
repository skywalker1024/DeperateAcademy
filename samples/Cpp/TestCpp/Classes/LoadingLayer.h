//
//  LoadingLayer.h
//  BraveFrontier

//  Created by WillArk on 11/13/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_LoadingLayer_h
#define BraveFrontier_LoadingLayer_h

#include "cocos2d.h"
#include "DialogBaseLayer.h"
#include "BaseScene.h"
USING_NS_CC;

class LoadingLayer : public DialogBaseLayer
{
public:
    // コンストラクタ
    LoadingLayer();
    // デストラクタ
    ~LoadingLayer();
    CREATE_FUNC(LoadingLayer);
    bool init();
    virtual void onEnter();
protected:

private:
    static const int STATE_CONNECT_INIT       = 0;
    static const int STATE_CONNECT_LOOP       = 1;
    static const int STATE_NEXT               = 2;
    int state;
    void draw();
    int connectIndex;

public:
    void backToTitle();
    void retry();
    void noticeConfirm();
    void changeNextScene();
private:
    CC_SYNTHESIZE_RETAIN(CCScene*, m_nextScene, NextScene);
    CC_SYNTHESIZE(BaseScene*, m_prevScene, PrevScene);
    CC_SYNTHESIZE(bool, m_isFinished, IsFinished);
    CC_SYNTHESIZE(string, m_message, Message);
    
    void responseParser(CCHttpClient* client, CCHttpResponse* response);
};

#endif

