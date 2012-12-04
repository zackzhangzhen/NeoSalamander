#include "Plane.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;


Plane::Plane(void)
{
	m_curAnim = NULL;
	m_SpritePlane = NULL;
	m_SpriteBullet = NULL;
	m_curLayer = NULL;
}

Plane::Plane(char* sprite)
{
	if(!sprite)
		m_SpritePlane = NULL;

	m_SpritePlane = CCSprite::create(sprite);

	m_SpritePlane->setPosition(ccp(0,0));
	m_curAnim = NULL;
	m_curLayer = NULL;
	m_SpriteBullet = NULL;
}

CCSprite* Plane::GetSprite()
{
    return m_SpritePlane;
}

void Plane::SetPosition(int x,int y)
{
	m_SpritePlane->setPosition(ccp(x,y));
}

CCPoint Plane::GetPostion()
{
	return m_SpritePlane->getPosition();
}

void Plane::AddToLayer(CCLayer* layer)
{
	assert(layer!=NULL);
	layer->addChild(m_SpritePlane);
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
		m_SpritePlane->stopAction(m_curAnim);
	m_curAnim = it->second;
	m_SpritePlane->runAction(it->second);

}

void Plane::EquipBullet(char* sprite)
{
    strcpy(m_SpriteFileBullet,sprite);
}

void Plane::FireDone(CCNode* sender)
{
	CCSprite* bullet = (CCSprite*)sender;
	this->m_curLayer->removeChild(bullet,true);	
}

void Plane::Fire()
{
	CCSprite* spriteBullet = CCSprite::create(m_SpriteFileBullet);
	spriteBullet->setPosition(ccp(m_SpritePlane->getPositionX(),m_SpritePlane->getPositionY()+m_SpritePlane->getContentSize().height/2));
	m_curLayer->addChild(spriteBullet);

	CCFiniteTimeAction* actionMove = CCMoveTo::actionWithDuration(2.0f,ccp(m_SpritePlane->getPositionX(),576+m_SpritePlane->getContentSize().height/2));
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(this,callfuncN_selector(Plane::FireDone));
	spriteBullet->runAction(CCSequence::actions(actionMove,actionMoveDone,NULL));
}

Plane::~Plane(void)
{
}
