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
private:
    
    // UIキャッシュリスト
    UICacheList* uiCacheList;
protected:
    CCSpriteBatchNode* getCacheBatchNode( string key, string name );
    void setCacheBatchNode( string key, string name, CCSpriteBatchNode* batch_node );
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
};


#endif /* defined(__TestCpp__BaseScene__) */
