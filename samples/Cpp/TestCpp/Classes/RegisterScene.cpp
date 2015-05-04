//
//  RegisterScene.cpp
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//


#include "RegisterScene.h"
#include "GameConst.h"
#include "GraphicUtils.h"

RegisterScene::RegisterScene()
{
}

RegisterScene::~RegisterScene(){
}

CCScene * RegisterScene::scene(){
    CCScene* scene = CCScene::create();
    scene->addChild(RegisterScene::create());
    return scene;
}

bool RegisterScene::init(){
    if (!BaseScene::init()) {
        return false;
    }
    setTouchEnabled(true);
    return true;
}

void RegisterScene::onEnter(){
    BaseScene::onEnter();
    GraphicUtils::drawString(this, "register", 200, 200, getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_CENTER_MIDDLE, 20);
}

void RegisterScene::onExit(){
    BaseScene::onExit();
}

bool RegisterScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    
    return true;
}


