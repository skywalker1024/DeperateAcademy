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
,m_isDead(false)
{}

Boss::~Boss(){
}

bool Boss::init(){
    CCSprite *bossSprite = CCSprite::create("img/boss.jpg");
    this->addChild(bossSprite);
    int hp = 300;
    setHp(hp);
    setMaxHp(hp);
    
    this->setHpBar(CCScale9Sprite::create("img/bar_green.png"));
    m_hpBar->setAnchorPoint(ccp(0,0));
    this->getHpBar()->setPosition(ccp(-bossSprite->getContentSize().width / 2, -200));
    this->addChild(this->getHpBar());
    return true;
}

void Boss::decHp(int damage){
    m_hp -= damage;
    if (m_hp <= 0) {
        m_hp = 0;
    }
    this->getHpBar()->setScaleX((float) m_hp / m_maxHp);
    
    if (m_hp == 0) {
        dying();
    }
}

void Boss::dying(){
    m_isDead = true;
    this->runAction(CCSequence::createWithTwoActions(CCFadeOut::create(1.f), CCCallFunc::create(this, callfunc_selector(CCNode::removeFromParent))));
}

void Boss::useSkillAction(){
    CCSequence *sequence = CCSequence::create(CCMoveBy::create(.1f, ccp(0, 10)), CCMoveBy::create(.1f, ccp(0, -20)),CCMoveBy::create(.1f, ccp(0, 10)), NULL);
    this->runAction(sequence);//上下挪动，代表释放技能
}

void Boss::AttackedAction(float delayTime){
    CCSequence *sequence = CCSequence::create(CCDelayTime::create(delayTime), CCMoveBy::create(.1f, ccp(10, 0)), CCMoveBy::create(.1f, ccp(-20, 0)),CCMoveBy::create(.1f, ccp(10, 0)), NULL);
    this->runAction(sequence);//左右挪动，代表被击中
}