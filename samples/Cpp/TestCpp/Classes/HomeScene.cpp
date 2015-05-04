//
//  HomeScene.cpp
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//


#include "HomeScene.h"
#include "GameConst.h"
#include "GraphicUtils.h"
#include "Battle.h"
HomeScene::HomeScene()
{
}

HomeScene::~HomeScene(){
}

CCScene * HomeScene::scene(){
    CCScene* scene = CCScene::create();
    scene->addChild(HomeScene::create());
    return scene;
}

bool HomeScene::init(){
    if (!BaseScene::init()) {
        return false;
    }
    setTouchEnabled(true);
    
     StringLabelList * title = GraphicUtils::drawString(this, "homescene中文事实上", 100, 100, 960, 100, getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_LEFT_MIDDLE, 40);
    return true;
}

void HomeScene::onEnter(){
    BaseScene::onEnter();
   
    
}

void HomeScene::onExit(){
    BaseScene::onExit();
}

bool HomeScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    
    return true;
}


