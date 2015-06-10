#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
#include "TitleScene.h"
#include "AppMacros.h"
#include "Battle.h"
USING_NS_CC;
#include "stdio.h"
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
//    SimpleAudioEngine::end();
	//cocos2d::extension::CCArmatureDataManager::purgeArmatureSystem();
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// As an example, load config file
	// XXX: This should be loaded before the Director is initialized,
	// XXX: but at this point, the director is already initialized
	//CCConfiguration::sharedConfiguration()->loadConfigFile("configs/config-example.plist");

    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    
    pDirector->setOpenGLView(pEGLView);
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    ResolutionPolicy resolution = screenSize.width / designResolutionSize.width > screenSize.height / designResolutionSize.height ? kResolutionFixedHeight : kResolutionFixedWidth;
    // Set the design resolution
    pEGLView->setDesignResolutionSize(designResolutionSize.width,
                                      designResolutionSize.height,
                                      resolution);
    
	CCSize frameSize = pEGLView->getFrameSize();
    pDirector->setContentScaleFactor(1);
    
    CCScene * pScene = TitleScene::scene();
    
    pDirector->runWithScene(pScene);

    return true;
}


// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
