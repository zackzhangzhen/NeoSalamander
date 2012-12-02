#include "BgLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;

const char* BgLayer::BG_01 = "pic\\bg\\bg01.png";
const char* BgLayer::BG_02 = "pic\\bg\\bg02.png";
const CCTexture2D* BgLayer::bgTex01 = NULL;
const CCTexture2D* BgLayer::bgTex02 = NULL;

float BgLayer::scrollFrequency = 0.01;
float BgLayer::scrollVelocity = 1;

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


