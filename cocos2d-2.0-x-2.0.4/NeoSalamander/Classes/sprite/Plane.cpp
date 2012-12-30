#include "Plane.h"
#include "SimpleAudioEngine.h"
#include "../layer/ObjectLayer.h"
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

	EnterCriticalSection(&GlobalFlag::m_csObject);

	CCSprite* bullet = (CCSprite*)sender;
	this->m_parentNode->removeChild(bullet,true);	
	bullet->autorelease();

	LeaveCriticalSection(&GlobalFlag::m_csObject);

	
}

void Plane::Fire(float velocity)
{
	

	CCPoint startPoint = ccp(m_sprite->getPositionX(),m_sprite->getPositionY()+ m_sprite->getContentSize().height/2);
	

	CCPoint endPoint = ccp(m_sprite->getPositionX(), NeoConstants::WIN_HEIGHT + m_sprite->getContentSize().height/2);

	float length = Utility::calcLength(startPoint, endPoint);
	float duration = length/velocity;

	//ZSprite* bullet = new ZSprite(m_SpriteFileBullet, duration, startPoint, endPoint);
	ZSprite* bullet = new ZSprite(m_SpriteFileBullet);

	
	bullet->setPosition(startPoint.x, startPoint.y);

	bullet->addToCCNode(m_parentNode, 0);
	ObjectLayer* layer = (ObjectLayer*)bullet->getParentNode();
	layer->getHeroArray()->addElement(bullet);


	CCFiniteTimeAction* actionMove = CCMoveTo::actionWithDuration(duration, endPoint);
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(this,callfuncN_selector(Plane::FireDone));
	//bullet->getSprite()->runAction(CCSequence::actions(actionMove,actionMoveDone,NULL));
	bullet->getSprite()->runAction(CCSequence::actions(actionMove,actionMoveDone,NULL));
}

Plane::~Plane(void)
{
}
