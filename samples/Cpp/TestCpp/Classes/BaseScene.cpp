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
#include "ConnectRequestList.h"
#include "LoadingLayer.h"
#include "UserInfo.h"
#include "LevelMstList.h"
BaseScene::BaseScene()
{
    uiCacheList = new UICacheList();
    m_backBtn = NULL;
    m_hasHead = false;
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

void BaseScene::pushStepScene(string url, string postData, CCScene * scene, string message){
    BaseRequest *baseRequest = new BaseRequest();
    baseRequest->setUrl(url);
    baseRequest->setData(postData);
    ConnectRequestList::shared()->addObject(baseRequest);
    
    LoadingLayer * loadingLayer = LoadingLayer::create();
    loadingLayer->setNextScene(scene);
    loadingLayer->setPrevScene(this);
    loadingLayer->setMessage(message);
    this->addChild(loadingLayer);
}

void BaseScene::pushStepScene(CCScene * scene){
    LoadingLayer * loadingLayer = LoadingLayer::create();
    loadingLayer->setNextScene(scene);
    loadingLayer->setPrevScene(this);
    this->addChild(loadingLayer);
}

/*
 * システムカラーの取得。
 */
ccColor3B BaseScene::getSystemColor( string key )
{
    ccColor3B color;
    
    // LVラベル
    if( key == COLOR_KEY_LV )
    {
        color = ccc3(195,214,155);
    }
    
    // HPラベル
    if( key == COLOR_KEY_HP )
    {
        color = ccc3(242,223,0);
    }
    
    // 攻撃ラベル
    if( key == COLOR_KEY_ATK )
    {
        color = ccc3(255,60,60);
    }
    
    // 防御ラベル
    if( key == COLOR_KEY_DEF )
    {
        color = ccc3(0,125,255);
    }
    
    // 回復ラベル
    if( key == COLOR_KEY_HEAL )
    {
        color = ccc3(176,255,123);
    }
    
    // BBLVラベル
    if( key == COLOR_KEY_BBLV )
    {
        color = ccc3(195,214,155);
    }
    
    // COST
    if( key == COLOR_KEY_COST )
    {
        color = ccc3(255,165,0);
    }
    
    // GOLD
    if( key == COLOR_KEY_GOLD )
    {
        color = ccc3(181,140,57);
    }
    
    // WHITE
    if( key == COLOR_KEY_WHITE )
    {
        color = ccc3(255,255,255);
    }
    
    // RED
    if( key == COLOR_KEY_RED )
    {
        color = ccc3(255,0,0);
    }
    
    // お知らせラベル
    if( key == COLOR_KEY_INFO )
    {
        color = ccc3(255,165,0);
    }
    
    return color;
}

void BaseScene::changeScene(CCScene * scene){
    CCDirector::sharedDirector()->replaceScene(scene);
}

void BaseScene::setHeader(){
    int screenWidth = CommonUtils::getScreenWidth();
    int screenHeight = CommonUtils::getScreenHeight();
    
    UserInfo * userInfo = UserInfo::shared();
    //name
    int x = 100;
    int y = screenHeight - 50;
    int width = 300;
    int fontSize = 40;
    GraphicUtils::drawString(this, userInfo->getName(), x, y, width, fontSize, getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_LEFT_TOP, fontSize);
    x += width;
    
    //钻石
    width = 100;
    GraphicUtils::drawString(this, "钻石", x, y, width, fontSize, getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_LEFT_TOP, fontSize);
    x += width;
    GraphicUtils::drawString(this, CommonUtils::IntToString( userInfo->getDiamond() ), x, y, 500, fontSize, getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_LEFT_TOP, fontSize);
    
    //第二行
    //lv
    x = 100;
    y = screenHeight - 100;
    width = 100;
    GraphicUtils::drawString(this, "等级", x, y, width, fontSize, getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_LEFT_TOP, fontSize);
    x += width;
    
    width = 200;
    GraphicUtils::drawString(this, CommonUtils::IntToString(userInfo->getLv()), x, y, width, fontSize, getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_LEFT_TOP, fontSize);
    x += width;
    
    
    //第三行 体力值
    x = 100;
    y = screenHeight - 150;
    width =150;
    GraphicUtils::drawString(this, "体力值", x, y, width, fontSize, getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_LEFT_TOP, fontSize);
    x += width;
    {
        string actionP = CCString::createWithFormat("%d/%d", userInfo->getActionP(), userInfo->getMaxActionP())->m_sString;
        m_staminaLabel = GraphicUtils::drawString(this, actionP, x, y, width, fontSize, getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_LEFT_TOP, fontSize);
        
        string rest = getRecoverRestTime( UserInfo::shared()->getActionRestTimer() );
        m_recoverTimeLabel = GraphicUtils::drawString(this, rest, 100, y - 50, screenWidth, fontSize, getSystemColor(COLOR_KEY_GOLD), TEXT_ALIGN_LEFT_TOP, fontSize);
        x += 150;
        
    }
    //经验值
    {
        GraphicUtils::drawString(this, "经验值", x, y, width, fontSize, getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_LEFT_TOP, fontSize);
        x += 150;
        LevelMst * levelMst = LevelMstList::shared()->getObject(userInfo->getLv() + 1);
        if (levelMst) {
           string expString = CCString::createWithFormat("%d/%d", userInfo->getExp(), levelMst->getExp())->m_sString;
            GraphicUtils::drawString(this, expString, x, y, 300, fontSize, getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_LEFT_TOP, fontSize);
        }else{
            GraphicUtils::drawString(this, "已顶级", x, y, width, fontSize, getSystemColor(COLOR_KEY_WHITE), TEXT_ALIGN_LEFT_TOP, fontSize);
        }
    }
    m_hasHead = true;
}

//返回按钮
void BaseScene::setBackBtn()
{
    CCLabelTTF * backLabel = CCLabelTTF::create("返回", DEFAULT_FONT_NAME, 60);
    m_backBtn = CCControlButton::create(backLabel, CCScale9Sprite::create("img/button1.png"));
    m_backBtn->setBackgroundSpriteForState(CCScale9Sprite::create("img/button2.png"), CCControlStateHighlighted);//按下后的图片
    
    int screenWidth = CommonUtils::getScreenWidth();
    int screenHeight = CommonUtils::getScreenHeight();
    
    m_backBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(BaseScene::onBackClick), CCControlEventTouchUpInside);
    m_backBtn->setPosition(ccp(100, screenHeight - 500));
    m_backBtn->setAnchorPoint(ccp(0,1));
    this->addChild(m_backBtn, 100);
}

void BaseScene::onBackClick(){
    CCLog("please over ride me");
}

string BaseScene::getRecoverRestTime( int rest_time )
{
    string str = "";
    
    if( rest_time == 0 )
    {
        return "体力已满";
    }
    
    
    str = "体力恢复还有";
    str.append( " " );
    
    int minute = (rest_time % RECOVER_TIME) / 60;
    int second = rest_time % 60;
    
    // 分
    str.append( CommonUtils::IntToString( minute ) );
    str.append( ":" );
    
    // 秒
    str.append( CommonUtils::stringFormat( second, 2 ) );
    
    return str;
    
}

void BaseScene::updateActionRestTime()
{
    if( !m_hasHead )
    {
        return;
    }
    
    int log_p = UserInfo::shared()->getActionP();
    
    UserInfo::shared()->decActionRestTimer();
    
    if( m_staminaLabel && m_recoverTimeLabel )
    {
        // 変化がない場合
        if( log_p != UserInfo::shared()->getActionP() )
        {
            CCLog( "log_p=%d act_p=%d", log_p, UserInfo::shared()->getActionP() );
            
            // 回復した場合
            if( log_p < UserInfo::shared()->getActionP() )
            {
                UserInfo * userInfo = UserInfo::shared();
                string actionP = CCString::createWithFormat("%d/%d", userInfo->getActionP(), userInfo->getMaxActionP())->m_sString;
                m_staminaLabel->changeString(actionP);
            }
        }
        
        // 残り時間取得
        string rest = getRecoverRestTime( UserInfo::shared()->getActionRestTimer() );
        
        if( rest != m_recoverTimeLabel->getString() )
        {
            //CCLog( "GameScene::updateActionRestTime rest=%s", rest.c_str() );
            
            m_recoverTimeLabel->changeString( rest );
        }
    }
    
}

void BaseScene::draw(){
    updateActionRestTime();
}