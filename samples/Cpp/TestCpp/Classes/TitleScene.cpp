//
//  BaseScene.cpp
//  TestCpp
//
//  Created by 龚畅优 on 14-2-2.
//
//


#include "BaseScene.h"
#include "GameConst.h"
#include "GraphicUtils.h"
BaseScene::BaseScene()
{
    uiCacheList = new UICacheList();
}

BaseScene::~BaseScene(){
    uiCacheList->release();
}

CCScene * BaseScene::scene(){
    CCScene* scene = CCScene::create();
    scene->addChild(BaseScene::create());
    return scene;
}

bool BaseScene::init(){
    if (!CCLayer::init()) {
        return false;
    }
    setTouchEnabled(true);
    return true;
}

bool BaseScene::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
    CCAssert(false, "onAssignCCBMemberVariable ended without assigning any variables. Check variable name");
    return false;
}

void BaseScene::onEnter(){
    CCLayer::onEnter();
}

void BaseScene::onExit(){
    CCLayer::onExit();
    
    uiCacheList->removeAllObjects();
}

bool BaseScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    return true;
}

void BaseScene::registerWithTouchDispatcher(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -122, true);
}


/*
 * キャッシュ バッチノードの取得。
 */
CCSpriteBatchNode* BaseScene::getCacheBatchNode( string key, string name )
{
    return uiCacheList->getBatchNode( key, name );
}

/*
 * キャッシュ バッチノードの設定。
 */
void BaseScene::setCacheBatchNode( string key, string name, CCSpriteBatchNode* batch_node )
{
    uiCacheList->setBatchNode( key, name, batch_node );
}


/*
 * UI スプライトの取得。
 */
CCSprite* BaseScene::getCacheSprite( string key, string name )
{
    return uiCacheList->getSprite( key, name );
}

/*
 * キャッシュ スプライトの設定。
 */
void BaseScene::setCacheSprite( string key, string name, GameSprite* sprite )
{
    uiCacheList->setSprite( key, name, sprite );
}


/*
 * UI 文字列リストの取得。
 */
StringLabelList*  BaseScene::getCacheStringLabelList( string key, string name, string str, ccColor3B color, int align, int fontsize )
{
    return getCacheStringLabelList( key, name, str, GAME_CANVAS_WIDTH, fontsize, color, align, fontsize );
}

/*
 * UI 文字列リストの取得。
 */
StringLabelList*  BaseScene::getCacheStringLabelList( string key, string name, string str, float w, float h, ccColor3B color, int align, int fontsize )
{
    StringLabelList* label = uiCacheList->getStringLabelList( key, name );
    
    if( !label )
    {
        label = GraphicUtils::initString( this, "", 0, 0, w, h,color, align, fontsize );
        
        uiCacheList->setStringLabelList( key, name, label );
    }
    
    label->changeString( str );
    label->draw();
    
    return label;
}
/*
 * UI 文字列リストの設定。
 */
void BaseScene::setCacheStringLabelList( string key, string name, StringLabelList* label )
{
    uiCacheList->setStringLabelList( key, name, label );
}

/*
 * キャッシュ パーティクルアニメを取得。
 */
ParticleAnime* BaseScene::getCacheParticleAnime( string key, string name )
{
    return uiCacheList->getParticleAnime( key, name );
}

/*
 * キャッシュ  パーティクルアニメを設定。
 */
void BaseScene::setCacheParticleAnime( string key, string name, ParticleAnime* anime )
{
    if( getCacheParticleAnime( key, name ) ) return;
    
    uiCacheList->setParticleAnime( key, name, anime );
}


