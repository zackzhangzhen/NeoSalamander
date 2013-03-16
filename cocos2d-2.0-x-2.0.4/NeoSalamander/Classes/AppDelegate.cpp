#include "AppDelegate.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
	 InitializeCriticalSection(&GlobalFlag::m_csObject);
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
	DeleteCriticalSection(&GlobalFlag::m_csObject);
}

bool AppDelegate::applicationDidFinishLaunching()
{
	//seed the random algorhitm
	 srand (time(NULL));

    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //CCScene *pScene = HelloWorld::scene();
	//CCScene *pScene = CCScene::create();
	//pScene->addChild(new BgLayer());
	//pScene->addChild(new ScriptLayer(), 10);


	//ObjectLayer* l = ObjectLayer::createObjectLayer();
	//l->scheduleObjects();
	//l->addGameMenu();
	//pScene->addChild(l,1);

	/*CCActionInterval* ac = Utility::getAnimationAction("pic\\explosion\\", "png",26, false, false);

	CCSprite *player = CCSprite::spriteWithFile("Stewie.png", 
		CCRectMake(0, 0, 55, 62) )

	CCSprite *player = CCSprite::create();
	player->setPosition(ccp(200,200));
	player->runAction(ac);

	ObjectLayer* l = ObjectLayer::createObjectLayer();
	l->scheduleObjects();*/
	//pScene->addChild(l,1);


	// Create a label and initialize with string "Hello World".
	//CCLabelTTF* pLabel = CCLabelTTF::create("Hello World\nyeah", "Arial", 24, CCSizeMake(/*68*/NeoConstants::WIN_WIDTH/2, 480),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);

    // Get window size and place the label upper. 
    //CCSize size = CCDirector::sharedDirector()->getWinSize();
    //pLabel->setPosition(ccp(size.width/2, size.height - 150));
	//pLabel->setOpacity(100);

	//CCFadeIn* pCCFadeIn= CCFadeIn::actionWithDuration(5);
	//CCFadeOut* pCCFadeOut= CCFadeOut::actionWithDuration(5);
	//CCDelayTime *delayAction = CCDelayTime::actionWithDuration(5);
	//pLabel->runAction(CCSequence::actions(pCCFadeIn, delayAction, pCCFadeOut, NULL));

	//CCScaleTo* scale = CCScaleTo::actionWithDuration(5,24);
	//pLabel->runAction(scale);
	
	//CCBlink* blink = CCBlink::actionWithDuration(5,6);
	//pLabel->runAction(blink);



		
	//CCTintTo* tint = CCTintTo::actionWithDuration(5,100,50,60);
	//pLabel->runAction(tint);
	

    // Add the label to HelloWorld layer as a child layer.
    //pScene->addChild(pLabel, 5);
	//pScene->addChild(player,2);

	// run
	//pDirector->runWithScene(pScene);

	//ZTitleScene* pTitleScene = new ZTitleScene();
	//pTitleScene->init();

	//ZMainScene* pMainScene = new ZMainScene();
	//pTitleScene->init();

	//pTitleScene->runByDirector(pDirector);
    
	ZSceneMgr* mgr = new ZSceneMgr(pDirector);
	mgr->runTitleScene();

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
