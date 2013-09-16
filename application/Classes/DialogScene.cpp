//
//  DialogScene.cpp
//  TestCpp
//
//  Created by 龚畅优 on 13-9-16.
//
//

#include "DialogScene.h"

DialogScene::DialogScene()
:m_dialog(NULL)
,m_leftNPC(NULL)
,m_rightNPC(NULL)
{}

DialogScene::~DialogScene(){}

CCScene * DialogScene::scene(){
    CCScene* scene = CCScene::create();
    DialogScene *layer = DialogScene::create();
    scene->addChild(layer);
    return scene;
}

bool DialogScene::init(){
    if (CCLayer::init()) {
        CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
        CCBReader reader = CCBReader(ccNodeLoaderLibrary);
        CCLayer *DialogScene = (CCLayer*)reader.readNodeGraphFromFile("ccbi/dialog.ccbi",this);
        this->addChild(DialogScene);
        this->setTouchEnabled(true);
        return true;
    }
    return false;
}

bool DialogScene::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_dialog", CCLabelTTF*, m_dialog);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_leftNPC", CCSprite*, m_leftNPC);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_rightNPC", CCSprite*, m_rightNPC);
    CCAssert(false, "onAssignCCBMemberVariable ended without assigning any variables. Check variable name");
    return false;
}

void DialogScene::onEnter(){
    CCLayer::onEnter();
}

bool DialogScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    return true;
}
void DialogScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    CCLayer::ccTouchEnded(pTouch, pEvent);
    npcAction();
}

void DialogScene::registerWithTouchDispatcher(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -122, true);
}

void DialogScene::npcAction(){
    float width = m_leftNPC->getContentSize().width;
    CCFiniteTimeAction *moveTo = CCMoveTo::create(.5f, ccp(width, 0));
    CCFiniteTimeAction *showDialog = CCCallFunc::create(this, callfunc_selector(DialogScene::showDialog));
    m_leftNPC->runAction(CCSequence::create(moveTo, showDialog, NULL));
    
}

void DialogScene::showDialog(){
    m_dialog->setString(CCString::createWithFormat("ss %ld", random())->getCString());
}