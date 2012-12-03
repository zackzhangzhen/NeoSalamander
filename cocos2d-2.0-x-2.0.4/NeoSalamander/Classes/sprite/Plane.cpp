#include "Plane.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;


Plane::Plane(void)
{
}

Plane::Plane(char* sprite)
{
	if(!sprite)
		m_Sprite = NULL;

	m_Sprite = CCSprite::create(sprite);
}

CCSprite* Plane::GetSprite()
{
    return m_Sprite;
}

void Plane::SetPostion(int x,int y)
{
	m_Sprite->setPosition(ccp(x,y));
}

void Plane::AddToLayer(CCLayer* layer)
{
	assert(layer!=NULL);
	layer->addChild(m_Sprite);
}

Plane::~Plane(void)
{
}
