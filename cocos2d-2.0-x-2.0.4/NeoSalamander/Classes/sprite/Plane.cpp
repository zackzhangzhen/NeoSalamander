#include "Plane.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;


Plane::Plane(void)
{
}

Plane::Plane(char* sprite):ZSprite(sprite)
{
}


void Plane::EquipBullet(char* sprite)
{
    strcpy(m_SpriteFileBullet,sprite);
}

void Plane::FireDone(CCNode* sender)
{
	CCSprite* bullet = (CCSprite*)sender;
	this->m_parentNode->removeChild(bullet,true);	
	bullet->autorelease();
}

void Plane::Fire(float velocity)
{
	ZSprite* bullet = new ZSprite(m_SpriteFileBullet);

	CCPoint startPoint = ccp(m_sprite->getPositionX(),m_sprite->getPositionY()+ m_sprite->getContentSize().height/2);
	bullet->setPosition(startPoint.x, startPoint.y);

	CCPoint endPoint = ccp(m_sprite->getPositionX(), NeoConstants::WIN_HEIGHT + m_sprite->getContentSize().height/2);

	float length = Utility::calcLength(startPoint, endPoint);
	float duration = length/velocity;

	m_parentNode->addChild(bullet->getSprite());
	

	CCFiniteTimeAction* actionMove = CCMoveTo::actionWithDuration(duration, endPoint);
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(this,callfuncN_selector(Plane::FireDone));
	bullet->getSprite()->runAction(CCSequence::actions(actionMove,actionMoveDone,NULL));
}

Plane::~Plane(void)
{
}
