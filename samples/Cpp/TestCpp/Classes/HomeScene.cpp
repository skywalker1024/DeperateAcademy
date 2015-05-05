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
    
    return true;
}

void HomeScene::onEnter(){
    BaseScene::onEnter();
    setHeader();
    
    //创建button
    //出征（购买体力写在里面吧）
    //竞技场（排行榜和挑战）
    //强化（强化士兵 强化城墙）
    
    //钻石商店
}

void HomeScene::onExit(){
    BaseScene::onExit();
}

bool HomeScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    
    return true;
}


