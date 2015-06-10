//
//  TestScene.cpp
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//


#include "TestScene.h"
#include "CommonUtils.h"
TestScene::TestScene()
{
}

TestScene::~TestScene(){
}

CCScene * TestScene::scene(){
    CCScene* scene = CCScene::create();
    scene->addChild(TestScene::create());
    return scene;
}

bool TestScene::init(){
    if (!BaseScene::init()) {
        return false;
    }
    
    return true;
}

void TestScene::onEnter(){
    BaseScene::onEnter();
    
    
    ParticleAnime * particle = ParticleAnime::create("plist/fireBall.plist");
    particle->CCNode::setPosition(ccp(500, 500));
    addChild(particle);
    
    
}

void TestScene::onExit(){
    BaseScene::onExit();
}

bool TestScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    BaseScene::ccTouchBegan(pTouch, pEvent);
    
    //add bezier
    float x1 = 400;//  CommonUtils::getRandom(10, 20);
    float y1 = 0;// CommonUtils::getRandom(-800, -700);
    
    float x2 = -300;// CommonUtils::getRandom(300, 400);
    float y2 = 300;//CommonUtils::getRandom(-400, 0);
    CCLog("x1=%f y1=%f x2=%f y2=%f", x1,y1, x2,y2);
    ccBezierConfig config;
    config.controlPoint_1 = ccp(x1,y1);
    config.controlPoint_2 = ccp(x2,y1);
    config.endPosition = ccp(500,900);
    
    ParticleAnime * particle = ParticleAnime::create("plist/fireBall.plist");
    particle->CCNode::setPosition(ccp(500, 500));
    addChild(particle);
    particle->runAction(CCBezierTo::create(1.f, config));
//    CCSprite * myWallSprite = CCSprite::create("img/wall_red.png");
//    myWallSprite->setPosition(ccp(500,500));
//    myWallSprite->runAction(CCBezierTo::create(1.f, config));
//    addChild(myWallSprite);
    return false;
}

void TestScene::onQuestClick(){
    //changeScene(MapScene::scene());
}

void TestScene::onEvoClick(){
    //changeScene(EvolutionScene::scene());
}

void TestScene::onArenaClick(){
    //pushStepScene("get_arena_list.php", "", ArenaMapScene::scene());
}

