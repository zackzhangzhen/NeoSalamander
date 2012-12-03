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
		this->m_sprite->setPosition(Utility::getRandomPoint());
	}	
}

ZSprite::ZSprite(char* fileName, bool randomSpawn, bool linearMove)
{
	this->m_sprite = CCSprite::create(fileName);
	this->m_originSize = this->m_sprite->getContentSize();
	if(randomSpawn)
	{
		this->m_sprite->setPosition(Utility::getRandomPoint());
	}

	if(linearMove)
	{

	}
}

void ZSprite::linearMoveWithRandomDirection(float velocity)
{
	// Determine where we wish to shoot the projectile to
	CCMoveTo* move = Utility::generateLinearMoveToAction(velocity, Utility::getRandomBoolean(),this->m_sprite->getContentSize(), this->m_sprite->getPosition());

	this->m_sprite->runAction( CCSequence::actions(move));
}

void ZSprite::linearMove(float velocity, bool moveLeft)
{
	// Determine where we wish to shoot the projectile to
	CCMoveTo* move = Utility::generateLinearMoveToAction(velocity, Utility::getRandomBoolean(),this->m_sprite->getContentSize(), this->m_sprite->getPosition());

	this->m_sprite->runAction( CCSequence::actions(move));
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
