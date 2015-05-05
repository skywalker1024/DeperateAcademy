//
//  DialogLayer.h
//  CrossKaiser
//
//  Created by 龚畅优 on 13-2-28.
//
//

#ifndef __CrossKaiser__DialogLayer__
#define __CrossKaiser__DialogLayer__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "DialogBaseLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;


class DialogLayer :public DialogBaseLayer{
protected:
    
    virtual void onEnter();


    bool onConfirmButtonClick();
    virtual void onCancel();
    
    CC_SYNTHESIZE(CCLabelTTF*, m_content, Content);
    CC_SYNTHESIZE(CCControlButton*, m_confirmButton, ConfirmButton);
    CC_SYNTHESIZE(CCControlButton*, m_cancelButton, CancelButton);
    CC_SYNTHESIZE(CCControlButton*, m_singleConfirmButton, SingleConfirmButton);
 
    CC_SYNTHESIZE_RETAIN(CCObject*, m_caller, Caller);
    CC_SYNTHESIZE(SEL_CallFunc,m_selector, Selector);
    CC_SYNTHESIZE_RETAIN(CCObject*, m_cancelCaller, CancelCaller);
    CC_SYNTHESIZE(SEL_CallFunc,m_cancelSelector, CancelSelector);
public:
    DialogLayer();
    virtual ~DialogLayer();
    static DialogLayer* showDialog(const char* content, int buttons, CCObject *caller = NULL, SEL_CallFunc onConfirmClick = NULL, CCObject *cancelCaller = NULL, SEL_CallFunc cancelSelector = NULL, const char* confirmString = "", const char * cancelString = "");
    void removeDialog();
    
    CREATE_FUNC(DialogLayer);
};
#endif /* defined(__CrossKaiser__DialogLayer__) */
