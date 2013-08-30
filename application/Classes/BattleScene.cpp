//
//  BattleScene.cpp
//  CrossKaiser
//
//  Created by 龚畅优 on 13-8-27.
//
//

#include "BattleScene.h"
#include "Poker.h"

BattleScene::BattleScene(){}
BattleScene::~BattleScene(){}
CCScene * BattleScene::scene(){
    CCScene* scene = CCScene::create();
    BattleScene *layer = BattleScene::create();
    scene->addChild(layer);
    return scene;
}

bool BattleScene::init(){
    if (CCLayer::init()) {
        Poker *poker = Poker::create();
        this->addChild(poker);
        return true;
    }
    return false;
}