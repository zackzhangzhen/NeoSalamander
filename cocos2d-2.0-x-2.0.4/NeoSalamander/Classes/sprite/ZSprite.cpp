#include "ZSprite.h"
using namespace cocos2d;
//The base class for the sprites
ZSprite::ZSprite(void)
{

}

ZSprite::ZSprite(char* fileName)
{
	this->m_sprite = CCSprite::create(fileName);
	this->m_spriteFileName = fileName;

	this->m_originSize = this->m_sprite->getContentSize();
}

ZSprite::ZSprite(char* fileName, bool randomSpawn)
{
	this->m_sprite = CCSprite::create(fileName);
	this->m_originSize = this->m_sprite->getContentSize();
	if(randomSpawn)
	{
		CCPoint pt = Utility::getRandomPointTop();
		this->m_sprite->setPosition(pt);
		this->m_startPoint = pt;
	}	
}

ZSprite::ZSprite(ZSprite& rhs, float spawnInterval)
{
	this->m_sprite = CCSprite::create(rhs.m_spriteFileName);
	this->m_sprite->setPosition(rhs.m_startPoint);

	this->m_startPoint = rhs.m_startPoint;
	this->m_spriteFileName = rhs.m_spriteFileName;

	this->m_originSize = this->m_sprite->getContentSize();

	this->m_moveToWrapper = CCMoveToWrapper(rhs.m_moveToWrapper.getDuration(), rhs.m_moveToWrapper.getEndPoint());
		
	if(spawnInterval != 0.0f)
	{
		CCDelayTime *delayAction = CCDelayTime::actionWithDuration(spawnInterval);
		this->m_sprite->runAction( CCSequence::actions(delayAction, m_moveToWrapper.getMoveTo(), NULL));
	}
	else
	{
		this->m_sprite->runAction(m_moveToWrapper.getMoveTo());
	}
}

ZSprite::ZSprite(char* fileName, int direction, float velocity)
{
	this->m_sprite = CCSprite::create(fileName);
	this->m_spriteFileName = fileName;
	this->m_originSize = this->m_sprite->getContentSize();

	CCPoint pt;

	switch(direction)
	{
	case (0/*NeoConstants::MOVE_DOWN*/): 
		{
			 pt = Utility::getRandomPointTop();
			 this->m_sprite->setPosition(pt);
			 this->m_startPoint = pt;
			 linearMoveDownWithRandomDirection(velocity);
			 break;
		 }

	case (1/*NeoConstants::MOVE_LEFT*/):
		{
			 pt = Utility::getRandomPointOnOneSide(false);
			 this->m_sprite->setPosition(pt);
			 this->m_startPoint = pt;
			 linearMoveLeft(velocity);
			 break;
		}

	case (2/*NeoConstants::MOVE_RIGHT*/):
		{
			pt = Utility::getRandomPointOnOneSide(true);
			this->m_sprite->setPosition(pt);
			this->m_startPoint = pt;
			linearMoveRight(velocity);
			break;
		}
	}
}

void ZSprite::addToCCNode(CCNode* node, int zOrder)
{
	node->addChild(this->m_sprite, zOrder);
}

void ZSprite::linearMoveDownWithRandomDirection(float velocity)
{
	this->m_moveToWrapper = Utility::generateLinearMoveToDownAction(velocity, Utility::getRandomBoolean(),this->m_sprite->getContentSize(), this->m_sprite->getPosition());
	//this->m_sprite->runAction( CCSequence::actions(move));
	this->m_sprite->runAction( m_moveToWrapper.getMoveTo());
}

void ZSprite::linearMoveLeft(float velocity)
{
	this->m_moveToWrapper = Utility::generateLinearMoveToHorizontalAction(velocity, true ,this->m_sprite->getContentSize(), this->m_sprite->getPosition());
	this->m_sprite->runAction( m_moveToWrapper.getMoveTo());
}

void ZSprite::linearMoveRight(float velocity)
{
	this->m_moveToWrapper = Utility::generateLinearMoveToHorizontalAction(velocity, false ,this->m_sprite->getContentSize(), this->m_sprite->getPosition());
	this->m_sprite->runAction( m_moveToWrapper.getMoveTo());
}

void ZSprite::linearMoveDown(float velocity, bool moveLeft)
{
	// Determine where we wish to shoot the projectile to
	this->m_moveToWrapper = Utility::generateLinearMoveToDownAction(velocity, Utility::getRandomBoolean(),this->m_sprite->getContentSize(), this->m_sprite->getPosition());
	this->m_sprite->runAction( m_moveToWrapper.getMoveTo());
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
