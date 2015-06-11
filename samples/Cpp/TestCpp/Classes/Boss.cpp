//
//  Boss.cpp
//  CrossKaiser
//
//  Created by 龚畅优 on 13-8-28.
//
//

#include "Boss.h"
#include "CommonUtils.h"
Boss::Boss()
:m_hp(0)
,m_maxHp(0)
{}

Boss::~Boss(){
}

bool Boss::init(){
    CCSprite *bossSprite = CCSprite::create("img/boss.jpg");
    this->addChild(bossSprite);
    setHp(300);
    setMaxHp(300);
    
    this->setHpBar(CCProgressTimer::create(CommonUtils::createSprite("bar_loading_2.png", "img/arrow_and_bar.plist")));
    this->getHpBar()->setPosition(ccp(0, 100));
    this->addChild(this->getHpBar(), 100);
    return true;
}

void Boss::decHp(int damage){
    m_hp -= damage;
    this->getHpBar()->setPercentage((float) damage / m_maxHp);
    
}

void Boss::useSkillAction(){
    CCSequence *sequence = CCSequence::create(CCMoveBy::create(.1f, ccp(0, 10)), CCMoveBy::create(.1f, ccp(0, -20)),CCMoveBy::create(.1f, ccp(0, 10)), NULL);
    this->runAction(sequence);//上下挪动，代表释放技能
}

void Boss::AttackedAction(float delayTime){
    CCSequence *sequence = CCSequence::create(CCDelayTime::create(delayTime), CCMoveBy::create(.1f, ccp(10, 0)), CCMoveBy::create(.1f, ccp(-20, 0)),CCMoveBy::create(.1f, ccp(10, 0)), NULL);
    this->runAction(sequence);//左右挪动，代表被击中
}