//
//  BaseScene.h
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//

#ifndef __TestCpp__BaseScene__
#define __TestCpp__BaseScene__
#include "cocos-ext.h"
#include "cocos2d.h"
USING_NS_CC;
USING_NS_CC_EXT;
#include "UICacheList.h"
#include "ConnectRequestList.h"
#include "CommonUtils.h"
#include "GameConst.h"
#include "GraphicUtils.h"
class BaseScene : public CCLayer, public CCBMemberVariableAssigner{
public:
    static CCScene * scene();
    BaseScene();
    virtual ~BaseScene();
    CREATE_FUNC(BaseScene);
    virtual bool init();
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher();
    void pushStepScene(string url, string postData, CCScene * scene, string message="");
    void pushStepScene(CCScene * scene);
    void changeScene(CCScene * scene);
    ccColor3B getSystemColor( string key );
    CCSpriteBatchNode* getCacheBatchNode( string key, string name );
    void setCacheBatchNode( string key, string name, CCSpriteBatchNode* batch_node );
private:
    StringLabelList * m_staminaLabel;
    StringLabelList * m_recoverTimeLabel;
    // UIキャッシュリスト
    UICacheList* uiCacheList;
    string getRecoverRestTime( int rest_time );
    void updateActionRestTime();
    bool m_hasHead;
protected:
    void draw();
    
   
    CCSprite* getCacheSprite( string key, string name );
    void setCacheSprite( string key, string name, GameSprite* sprite );
    StringLabelList* getCacheStringLabelList(string key, string name );
    StringLabelList* getCacheStringLabelList( string key, string name, string str, ccColor3B color, int align, int fontsize );
    StringLabelList* getCacheStringLabelList( string key, string name, string str, float w, float h, ccColor3B color, int align, int fontsize );
    void setCacheStringLabelList( string key, string name, StringLabelList* label );
    
    // キャッシュ パーティクルアニメを取得
    ParticleAnime* getCacheParticleAnime( string key, string name );
    // キャッシュ パーティクルアニメを設定
    void setCacheParticleAnime( string key, string name, ParticleAnime* anime );
    
    void setHeader();
    void setBackBtn();
    virtual void onBackClick();
    CCControlButton * m_backBtn;
};


#endif /* defined(__TestCpp__BaseScene__) */
