#include "BgLayer.h"
#include "../sprite/Plane.h"
#include "../utility/Utility.h"
using namespace cocos2d;
using namespace CocosDenshion;

const char* BgLayer::BG_01 = "pic\\bg\\bg01.png";
const char* BgLayer::BG_02 = "pic\\bg\\bg02.png";
const CCTexture2D* BgLayer::bgTex01 = NULL;
const CCTexture2D* BgLayer::bgTex02 = NULL;

float BgLayer::scrollFrequency = 0.01;
float BgLayer::scrollVelocity = 1;
bool BgLayer::pause = false;
 Plane* pl = NULL;

BgLayer::BgLayer(void)
{
	this->bg01 = true;

	//init the background sprite
	this->m_bgSprite = CCSprite::create(this->BG_01);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	m_bgSprite->setPosition(ccp(size.width/2, 0));

	this->addChild(m_bgSprite);

	bgTex01 = CCTextureCache::sharedTextureCache()->addImage(BgLayer::BG_01);
	bgTex02 = CCTextureCache::sharedTextureCache()->addImage(BgLayer::BG_02);

	this->scheduleScroll(this->scrollFrequency);

	pl = new Plane("pic\\object\\plane.png");
	pl->setPosition(100,100);
	pl->addToCCNode(this, 0);
	pl->addAnimation("exp",Utility::getAnimationAction("pic\\explosion\\","png",26,false, false));
	//pl->PlayAnimation("exp");
	pl->EquipBullet("pic\\bullet\\bullet.png");

	this->setTouchEnabled(true);
	
}

void BgLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{

	CCTouch* touch = (CCTouch*)( touches->anyObject() );
	CCPoint location = touch->locationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	//pl->Fire(300.0f);
	
	//m_bgSprite->runAction(CCShaky3D::actionWithRange(5, true, ccg(15, 10), 1.5));

	

	/*if(!pause)
	{
		CCDirector::sharedDirector()->pause();
		pause = true;
	}
	else
	{
		CCDirector::sharedDirector()->resume();
		pause = false;
	}*/
	pl = new Plane("pic\\object\\plane.png");
	pl->setPosition(location.x,location.y);
	pl->addToCCNode(this, 0);
	pl->addAnimation("exp",Utility::getAnimationAction("pic\\explosion\\","png",26,false, false));
	pl->playAnimationAndStop("exp");
}

BgLayer::~BgLayer(void)
{
}

void BgLayer::scroll(float dt)
{
	float x = this->m_bgSprite->getPositionX();
	float y = this->m_bgSprite->getPositionY();

	if(y >= 576)
	{
		y = -0.5;
		if(bg01)
		{
			this->m_bgSprite->setTexture((CCTexture2D*)this->bgTex02);
			bg01 = false;
		}
		else
		{
			this->m_bgSprite->setTexture((CCTexture2D*)this->bgTex01);
			bg01 = true;
		}
	}
	this->m_bgSprite->setPosition(ccp(x,y+this->scrollVelocity));
}

void BgLayer::scheduleScroll(float dt)
{
	this->schedule( schedule_selector(BgLayer::scroll), dt );
}


