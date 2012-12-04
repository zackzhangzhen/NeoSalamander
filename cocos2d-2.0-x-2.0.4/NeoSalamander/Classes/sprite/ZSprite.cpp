#include "ZSprite.h"
using namespace cocos2d;
//The base class for the sprites
ZSprite::ZSprite(void)
{

}


ZSprite::ZSprite(char* fileName)
{
	this->m_sprite = CCSprite::create(fileName);
	this->m_originSize = this->m_sprite->getContentSize();
}

ZSprite::ZSprite(char* fileName, bool randomSpawn)
{
	this->m_sprite = CCSprite::create(fileName);
	this->m_originSize = this->m_sprite->getContentSize();
	if(randomSpawn)
	{
		this->m_sprite->setPosition(Utility::getRandomPointTop());
	}	
}

ZSprite::ZSprite(char* fileName, bool randomSpawn, int direction, float velocity)
{
	this->m_sprite = CCSprite::create(fileName);
	this->m_originSize = this->m_sprite->getContentSize();
	if(randomSpawn)
	{
		CCPoint pt = Utility::getRandomPointTop();
		this->m_sprite->setPosition(pt);
	}

	switch(direction)
	{
	case (0/*NeoConstants::MOVE_DOWN*/): 
		{
			 linearMoveDownWithRandomDirection(velocity);
			 break;
		 }

	case (1/*NeoConstants::MOVE_LEFT*/):
		{

		}

	case (2/*NeoConstants::MOVE_RIGHT*/):
		{

		}

	}
}

void ZSprite::addToCCNode(CCNode* node, int zOrder)
{
	node->addChild(this->m_sprite, zOrder);
}

void ZSprite::linearMoveDownWithRandomDirection(float velocity)
{
	// Determine where we wish to shoot the projectile to
	CCMoveTo* move = Utility::generateLinearMoveToDownAction(velocity, Utility::getRandomBoolean(),this->m_sprite->getContentSize(), this->m_sprite->getPosition());

	//this->m_sprite->runAction( CCSequence::actions(move));
	this->m_sprite->runAction( move);
}

void ZSprite::linearMoveDown(float velocity, bool moveLeft)
{
	// Determine where we wish to shoot the projectile to
	CCMoveTo* move = Utility::generateLinearMoveToDownAction(velocity, Utility::getRandomBoolean(),this->m_sprite->getContentSize(), this->m_sprite->getPosition());

	this->m_sprite->runAction( move);
}

bool ZSprite::isInScreen()
{
	float x =this->m_sprite->getPositionX();
	float y =this->m_sprite->getPositionY();

	float left_edge = - x/2;
	float right_edge = NeoConstants::WIN_WIDTH + x/2;
	float top_edge = NeoConstants::WIN_HEIGHT + y/2;
	float bottom_edge = -y/2;

	return (x > left_edge) && (x < right_edge) && (y > bottom_edge) && (y < top_edge);
}

ZSprite::~ZSprite(void)
{
}
