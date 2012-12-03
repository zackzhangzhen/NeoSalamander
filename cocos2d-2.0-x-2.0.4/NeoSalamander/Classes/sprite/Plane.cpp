#include "Plane.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;


Plane::Plane(void)
{
	m_curAnim = NULL;
	m_Sprite = NULL;
	m_curLayer = NULL;
}

Plane::Plane(char* sprite)
{
	if(!sprite)
		m_Sprite = NULL;

	m_Sprite = CCSprite::create(sprite);

	m_Sprite->setPosition(ccp(0,0));
	m_curAnim = NULL;
	m_curLayer = NULL;
}

CCSprite* Plane::GetSprite()
{
    return m_Sprite;
}

void Plane::SetPosition(int x,int y)
{
	m_Sprite->setPosition(ccp(x,y));
}

CCPoint Plane::GetPostion()
{
	return m_Sprite->getPosition();
}

void Plane::AddToLayer(CCLayer* layer)
{
	assert(layer!=NULL);
	layer->addChild(m_Sprite);
	m_curLayer = layer;
}

void Plane::AddAnimation(string animName,CCRepeatForever* anim)
{
	m_AnimMap.insert(map<string,CCRepeatForever*>::value_type(animName,anim));
}

void Plane::PlayAnimation(string animName)
{
	if(m_curLayer == NULL)
	{
		printf("This target has not been added to any layer yet");
		return;
	}

	map<string,CCRepeatForever*>::iterator it = m_AnimMap.find(animName);
	assert(it != m_AnimMap.end());

	if(m_curAnim != NULL)
		m_Sprite->stopAction(m_curAnim);
	m_curAnim = it->second;
	m_Sprite->runAction(it->second);

}

Plane::~Plane(void)
{
}
