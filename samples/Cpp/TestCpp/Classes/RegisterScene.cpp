//
//  RegisterScene.cpp
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//


#include "RegisterScene.h"
#include "GameConst.h"
#include "GraphicUtils.h"
#include "CommonUtils.h"
RegisterScene::RegisterScene()
{
    m_confirmButton = NULL;
}

RegisterScene::~RegisterScene(){
    
    editBoxSprite->release();
}

CCScene * RegisterScene::scene(){
    CCScene* scene = CCScene::create();
    scene->addChild(RegisterScene::create());
    return scene;
}

bool RegisterScene::init(){
    if (!BaseScene::init()) {
        return false;
    }
    setTouchEnabled(true);
    return true;
}

void RegisterScene::onEnter(){
    BaseScene::onEnter();
    GraphicUtils::drawString(this, "输入姓名", CommonUtils::getScreenWidth() / 2 , CommonUtils::getScreenHeight() - 300, getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_CENTER_MIDDLE, 40);
    
    CCSize editBoxSize = CCSizeMake( 200, 32 );
    editBox = CCEditBox::create( editBoxSize, CCScale9Sprite::create("img/base_panel.png"));
    // Positionは画面の遥か外側のためccp(1000,1000)
    editBox->setPosition( ccp( 2000, 2000 ) );
    editBox->setText( "" );
    
    editBox->setMaxLength(8);
    
    editBox->setReturnType( kKeyboardReturnTypeDefault );
    editBox->setInputMode( kEditBoxInputModeSingleLine );
    editBox->setDelegate(this);
    editBox->setVisible( false );
    this->addChild(editBox);
    
    // 画像でかぶせる
    editBoxSprite = GameSprite::init( "img/handle_name_frame.png" );
    editBoxSprite->setAnchorPoint(ccp(0.5,1));
    editBoxSprite->setSize( 400, 64 );
    editBoxSprite->setPosition( CommonUtils::getScreenWidth() / 2,  960);
    this->addChild(editBoxSprite);
    
    
    m_confirmButton = CCControlButton::create("确认", DEFAULT_FONT_NAME, 40);
    m_confirmButton->setPosition(CommonUtils::getScreenWidth() / 2, 500);
    this->addChild(m_confirmButton);
    
    m_randomButton = CCControlButton::create("随机姓名", DEFAULT_FONT_NAME, 40);
    m_randomButton->setPosition(CommonUtils::getScreenWidth() / 2, 1000);
    this->addChild(m_randomButton);
    
    float nx = CommonUtils::getScreenWidth() / 2 - 143;
    float ny = 900;
    
    userName = GraphicUtils::drawString( this, "", nx, ny, 200, 32, ccc3(255,255,255), TEXT_ALIGN_LEFT_TOP, 40 );
}

void RegisterScene::onExit(){
    BaseScene::onExit();
}

bool RegisterScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    if (m_confirmButton->ccTouchBegan(pTouch, pEvent)) {
        CCLog("touch button");
        return true;
    }
    
    if (m_randomButton->ccTouchBegan(pTouch, pEvent)) {
        CCLog("touch rand");
        return true;
    }
    
    editBox->touchDownAction( NULL, CCControlEventTouchUpInside );
    
    return true;
}

void RegisterScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    m_confirmButton->ccTouchCancelled(pTouch, pEvent);
    m_randomButton->ccTouchCancelled(pTouch, pEvent);
}
void RegisterScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    m_confirmButton->ccTouchCancelled(pTouch, pEvent);
    m_randomButton->ccTouchCancelled(pTouch, pEvent);
}
void RegisterScene::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){
    m_confirmButton->ccTouchCancelled(pTouch, pEvent);
    m_randomButton->ccTouchCancelled(pTouch, pEvent);
}

void RegisterScene::editBoxEditingDidBegin(CCEditBox* editBox)
{
    CCLog("editBox %p DidBegin !", editBox);
}

void RegisterScene::editBoxEditingDidEnd(CCEditBox* editBox)
{
    CCLog("editBox %p DidEnd !", editBox);
    
}

void RegisterScene::editBoxTextChanged(CCEditBox* editBox, const std::string& text)
{
    //modi by chenwei
    CCLog("editBox getMaxLength  %d", editBox->getMaxLength());
    
    userName->changeString( text );
}

void RegisterScene::editBoxReturn(CCEditBox* editBox)
{
    string text = editBox->getText();
    // 編集終了ときの処理
    userName->changeString( editBox->getText() );
}



