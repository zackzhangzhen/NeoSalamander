#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "layer/BgLayer.h";
#include "utility/Utility.h"
#include "sprite/ZSprite.h"
#include "layer/ObjectLayer.h"
using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //CCScene *pScene = HelloWorld::scene();
	CCScene *pScene = CCScene::create();
	pScene->addChild(new BgLayer());

	CCRepeatForever* ac = Utility::getAnimationAction("pic\\explosion\\", "png",26, false);

	/*CCSprite *player = CCSprite::spriteWithFile("Stewie.png", 
		CCRectMake(0, 0, 55, 62) );*/

	CCSprite *player = CCSprite::create();
	player->setPosition(ccp(200,200));
	player->runAction(ac);

	for(int i = 0; i < 0; i ++)
	{
		ZSprite* sprite = new ZSprite("pic\\object\\stewie.png",NeoConstants::MOVE_DOWN,200);
		sprite->addToCCNode(pScene, 0);
	}

	ObjectLayer* l = ObjectLayer::createObjectLayer();
	l->scheduleObjects();
	pScene->addChild(l,1);
	//pScene->addChild(player,2);
    // run
	pDirector->runWithScene(pScene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
