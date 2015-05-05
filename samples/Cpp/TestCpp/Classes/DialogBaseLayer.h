//
//  DialogBaseLayer.h
//  CrossKaiser
//
//  Created by 龚畅优 on 13-2-28.
//
//

#ifndef __CrossKaiser__DialogBaseLayer__
#define __CrossKaiser__DialogBaseLayer__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class DialogBaseLayer :public CCLayerRGBA, public CCBSelectorResolver, public CCBMemberVariableAssigner
{
protected:
    bool init();
    virtual void onEnter();
    virtual void onExit();
    
    //Implements of virtual class CCBMemberVariableAssigner
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){return NULL;};
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){return NULL;};
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode){return NULL;};

    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void registerWithTouchDispatcher();
    
    void dismissDialog();
public:
    DialogBaseLayer();
    virtual ~DialogBaseLayer();
    
    CREATE_FUNC(DialogBaseLayer);
};
#endif /* defined(__CrossKaiser__DialogBaseLayer__) */
