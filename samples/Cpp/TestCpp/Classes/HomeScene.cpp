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
#include "MapScene.h"
#include "EvolutionScene.h"
#include "ArenaMapScene.h"
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
    
    int screenWidth = CommonUtils::getScreenWidth();
    int screenHeight = CommonUtils::getScreenHeight();
    //创建button
    //出征（购买体力写在里面吧）
    {
        CCLabelTTF * questLabel = CCLabelTTF::create("出征", DEFAULT_FONT_NAME, 60);
        CCControlButton * questBtn = CCControlButton::create(questLabel, CCScale9Sprite::create("img/button1.png", CCRect(0, 0, 256, 256)));
        questBtn->setBackgroundSpriteForState(CCScale9Sprite::create("img/button2.png"), CCControlStateHighlighted);//按下后的图片
        
        questBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(HomeScene::onQuestClick), CCControlEventTouchDown);
        questBtn->setPosition(ccp(screenWidth / 2 - 100, screenHeight / 2));
        this->addChild(questBtn);
    }
    //竞技场（排行榜和挑战）
    {
        CCLabelTTF * arenaLabel = CCLabelTTF::create("群雄逐鹿", DEFAULT_FONT_NAME, 60);
        CCControlButton * arenaBtn = CCControlButton::create(arenaLabel, CCScale9Sprite::create("img/button1.png", CCRect(0, 0, 256, 256)));
        arenaBtn->setBackgroundSpriteForState(CCScale9Sprite::create("img/button2.png"), CCControlStateHighlighted);//按下后的图片
        
        arenaBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(HomeScene::onArenaClick), CCControlEventTouchDown);
        arenaBtn->setPosition(ccp(screenWidth / 2 + 100, screenHeight / 2));
        this->addChild(arenaBtn);
    }
    //强化（强化士兵 强化城墙）
    {
        CCLabelTTF * evoLabel = CCLabelTTF::create("强化士兵", DEFAULT_FONT_NAME, 60);
        CCControlButton * evoBtn = CCControlButton::create(evoLabel, CCScale9Sprite::create("img/button1.png"));
        evoBtn->setBackgroundSpriteForState(CCScale9Sprite::create("img/button2.png"), CCControlStateHighlighted);//按下后的图片
        
        evoBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(HomeScene::onEvoClick), CCControlEventTouchUpInside);
        evoBtn->setPosition(ccp(screenWidth / 2 - 100, screenHeight / 2 - 400));
        this->addChild(evoBtn);
    }
    //钻石商店
}

void HomeScene::onExit(){
    BaseScene::onExit();
}

bool HomeScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    BaseScene::ccTouchBegan(pTouch, pEvent);
    return false;
}

void HomeScene::onQuestClick(){
    changeScene(MapScene::scene());
}

void HomeScene::onEvoClick(){
    changeScene(EvolutionScene::scene());
}

void HomeScene::onArenaClick(){
    pushStepScene("get_arena_list.php", "", ArenaMapScene::scene());
}

