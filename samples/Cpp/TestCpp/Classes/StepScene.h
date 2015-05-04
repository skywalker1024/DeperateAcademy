//
//  StepScene.h
//  BraveFrontier

//  Created by WillArk on 11/13/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_StepScene_h
#define BraveFrontier_StepScene_h

#include "cocos2d.h"
#include "BaseScene.h"

USING_NS_CC;


class StepScene : public BaseScene
{
public:
    // コンストラクタ
    StepScene();
    // デストラクタ
    ~StepScene();
    static CCScene * scene();
    CREATE_FUNC(StepScene);
    virtual bool init();
    
    virtual void onEnter();
    virtual void onExit();
protected:

private:
    static const int STATE_CONNECT_INIT       = 0;
    static const int STATE_CONNECT_LOOP       = 1;
    static const int STATE_NEXT               = 2;
    int state;
    void draw();
    int connectIndex;
    SEL_HttpResponse ResponseParse(CCHttpClient* client, CCHttpResponse* response);
    bool m_isFinish;
};

#endif

