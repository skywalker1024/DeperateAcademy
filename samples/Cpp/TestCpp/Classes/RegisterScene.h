//
//  RegisterScene.h
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//

#ifndef __TestCpp__RegisterScene__
#define __TestCpp__RegisterScene__
#include "BaseScene.h"

class RegisterScene : public BaseScene, public CCEditBoxDelegate{
public:
    static CCScene * scene();
    RegisterScene();
    virtual ~RegisterScene();
    CREATE_FUNC(RegisterScene);
    virtual bool init();

    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void editBoxEditingDidBegin(CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(CCEditBox* editBox);
    virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(CCEditBox* editBox);
    
private:
    CCEditBox* editBox;
    GameSprite* editBoxSprite;
    // 名前保持用
    StringLabelList* userName;
    CCControlButton * m_randomButton;
    CCControlButton * m_confirmButton;
    
    void create_user(CCObject *sender, CCControlEvent controlEvent);
    void getRandomName(CCObject *sender, CCControlEvent controlEvent);
};


#endif /* defined(__TestCpp__RegisterScene__) */
