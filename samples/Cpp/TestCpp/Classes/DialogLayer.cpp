//
//  DialogLayer.cpp
//  CrossKaiser
//
//  Created by 龚畅优 on 13-2-28.
//
//

#include "DialogLayer.h"
#include "GameConst.h"
#include "CommonUtils.h"
#include "GraphicUtils.h"
DialogLayer::DialogLayer():
m_cancelButton(NULL),
m_confirmButton(NULL),
m_content(NULL),
m_caller(NULL),
m_selector(NULL)
,m_cancelCaller(NULL)
{}
DialogLayer::~DialogLayer(){
    CC_SAFE_RELEASE_NULL(m_cancelButton);
    CC_SAFE_RELEASE_NULL(m_confirmButton);
    CC_SAFE_RELEASE_NULL(m_content);
    CC_SAFE_RELEASE_NULL(m_caller);
    CC_SAFE_RELEASE_NULL(m_cancelCaller);
}

DialogLayer* DialogLayer::showDialog(const char* content, int buttons, CCObject *caller, SEL_CallFunc onConfirmClick, CCObject *cancelCaller, SEL_CallFunc cancelSelector, const char* confirmString, const char * cancelString){
    
    DialogLayer* pRet = new DialogLayer();
    int screenWidth = CommonUtils::getScreenWidth();
    int screenHeight = CommonUtils::getScreenHeight();
    
    GraphicUtils::drawString(pRet, content, 0, screenHeight / 2 + 200, screenWidth, 60, ccc3(255,255,255), TEXT_ALIGN_CENTER_TOP, 60);
    
    pRet->setCaller(caller);
    pRet->setSelector(onConfirmClick);
    pRet->setCancelCaller(cancelCaller);
    pRet->setCancelSelector(cancelSelector);
    
    CCLabelTTF * confirmLabel = CCLabelTTF::create("确定", DEFAULT_FONT_NAME, 60);
    CCLabelTTF * cancelLabel = CCLabelTTF::create("取消", DEFAULT_FONT_NAME, 60);
    
    pRet->setConfirmButton( CCControlButton::create(confirmLabel, CCScale9Sprite::create("img/button1.png", CCRect(0,0,256,256))) );
    pRet->setCancelButton( CCControlButton::create(cancelLabel, CCScale9Sprite::create("img/button2.png")) );
    if (strcmp(confirmString, "") != 0) {
        confirmLabel->setString(confirmString);
    }
    if (strcmp(cancelString, "") != 0) {
        cancelLabel->setString(cancelString);
    }
    pRet->addChild(pRet->getConfirmButton());
    pRet->addChild(pRet->getCancelButton());
    pRet->getConfirmButton()->addTargetWithActionForControlEvents(pRet, cccontrol_selector(DialogLayer::onConfirmButtonClick), CCControlEventTouchDown);
     pRet->getCancelButton()->addTargetWithActionForControlEvents(pRet, cccontrol_selector(DialogLayer::onCancel), CCControlEventTouchDown);
    if (buttons) {
        if (buttons == 1) {
            //singleConfirm
            pRet->getConfirmButton()->setVisible(true);
            pRet->getConfirmButton()->setEnabled(true);
            pRet->getCancelButton()->setVisible(false);
            pRet->getCancelButton()->setEnabled(false);
            pRet->getConfirmButton()->setPosition(ccp(screenWidth / 2, screenHeight / 2));
        }else if (buttons == 2){
            pRet->getConfirmButton()->setPosition(ccp(screenWidth / 2 - 200, screenHeight / 2));
            pRet->getCancelButton()->setPosition(ccp(screenWidth / 2 + 200, screenHeight / 2));
        }
    }
    CCDirector::sharedDirector()->getRunningScene()->addChild(pRet, 10);
    pRet->autorelease();
    return pRet;

}

void DialogLayer::onEnter()
{
    DialogBaseLayer::onEnter();
    m_confirmButton->setTouchPriority(DIALOG_BUTTON_PRIORITY);
    m_cancelButton->setTouchPriority(DIALOG_BUTTON_PRIORITY);
    
}

bool DialogLayer::onConfirmButtonClick(){
    this->retain();
    this->removeDialog();
    if(getCaller() && getSelector()){
        (getCaller()->*getSelector())();
    }
    this->release();
    return true;
}
void DialogLayer::onCancel(){
    this->retain();
    this->removeDialog();
    if(getCancelCaller() && getCancelSelector()){
        (getCancelCaller()->*getCancelSelector())();
    }
    this->release();
}

void DialogLayer::removeDialog(){
    this->getConfirmButton()->setEnabled(false);
    this->dismissDialog();
}
