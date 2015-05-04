//
//  TitleScene.cpp
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//


#include "TitleScene.h"
#include "GameConst.h"
#include "GraphicUtils.h"
#include "HomeScene.h"
TitleScene::TitleScene()
{
}

TitleScene::~TitleScene(){
}

CCScene * TitleScene::scene(){
    CCScene* scene = CCScene::create();
    scene->addChild(TitleScene::create());
    return scene;
}

bool TitleScene::init(){
    if (!BaseScene::init()) {
        return false;
    }
    
    StringLabelList *test = GraphicUtils::drawString(this, "titleScene", 250, 250, getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_CENTER_MIDDLE, 100);
    CCLog("test %f %f", test->getPositionX(), test->getPositionY());
    return true;
}

void TitleScene::onEnter(){
    BaseScene::onEnter();
}

void TitleScene::onExit(){
    BaseScene::onExit();
}

bool TitleScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    
    pushStepScene("get_user_info.php", "", HomeScene::scene());
    return true;
}


