#include "Plane.h"
#include "SimpleAudioEngine.h"
#include "../layer/ObjectLayer.h"
using namespace cocos2d;


extern map<void*,void*> g_AddressMap;

Plane::Plane(void)
{
}

Plane::Plane(char* fileName, int direction, float velocity):ZSprite(fileName,direction,velocity)
{

}

Plane::Plane(char* sprite):ZSprite(sprite)
{
}


void Plane::EquipBullet(char* sprite)
{
    strcpy(m_SpriteFileBullet,sprite);
}

void Plane::MoveDoneExtra(CCNode* sender)
{
	EnterCriticalSection(&GlobalFlag::m_csObject);

	CCSprite* sprite = (CCSprite*)sender;
	map<void*,void*>::iterator it = g_AddressMap.find((void*)sender);
	if(it == g_AddressMap.end())
		return;
	Plane* plane = (Plane*)it->second;

	ObjectLayer* ol = (ObjectLayer*)this->m_parentNode;
	ol->cd->removeObjectByPointer((CollidableObject*)plane);
	sprite->autorelease();
	g_AddressMap.erase((void*)sender);
	LeaveCriticalSection(&GlobalFlag::m_csObject);
}


void Plane::FireDone(CCNode* sender)
{

	EnterCriticalSection(&GlobalFlag::m_csObject);

	CCSprite* sprite = (CCSprite*)sender;
	map<void*,void*>::iterator it = g_AddressMap.find((void*)sender);
	if(it == g_AddressMap.end())
		return;
	ZSprite* bullet = (ZSprite*)it->second;
	this->m_parentNode->removeChild(bullet,true);
	ObjectLayer* ol = (ObjectLayer*)this->m_parentNode;
	ol->cd->removeObjectByPointer((CollidableObject*)bullet);
	bullet->autorelease();
	g_AddressMap.erase((void*)sender);
	//bullet->release();
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
	//The target should be bullet!!!!
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(bullet,callfuncN_selector(Plane::FireDone));
	//bullet->getSprite()->runAction(CCSequence::actions(actionMove,actionMoveDone,NULL));

	//Include the mapping of the sprite to its host ZSprite
	g_AddressMap.insert(map<void*,void*>::value_type((void*)bullet->getSprite(),(void*)bullet));
	bullet->getSprite()->runAction(CCSequence::actions(actionMove,actionMoveDone,NULL));
	
}

Plane::~Plane(void)
{
}
