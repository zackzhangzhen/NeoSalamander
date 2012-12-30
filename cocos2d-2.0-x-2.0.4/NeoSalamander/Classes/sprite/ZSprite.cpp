#include "ZSprite.h"
using namespace cocos2d;
//The base class for the sprites
ZSprite::ZSprite(void)
{
	this->m_curAnim = NULL;
	this->m_parentNode = NULL;
	this->m_sprite = NULL;
	this->m_spriteFileName = NULL;
}

ZSprite::ZSprite(char* fileName)
{
	this->ZSprite::ZSprite();

	this->m_sprite = CCSprite::create(fileName);
	m_sprite->setPosition(ccp(0,0));

	this->m_spriteFileName = fileName;

	this->m_originSize = this->m_sprite->getContentSize();
}

ZSprite::ZSprite(char* fileName, float duration, CCPoint startPt, CCPoint endPt)
{

	this->ZSprite::ZSprite();

	this->m_sprite = CCSprite::create(fileName);
	m_sprite->setPosition(startPt);

	CCMoveTo* moveTo = CCMoveTo::create(duration, endPt);

	this->m_spriteFileName = fileName;

	this->m_originSize = this->m_sprite->getContentSize();

	this->m_moveToWrapper = CCMoveToWrapper(duration, endPt);

	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(this,callfuncN_selector(ZSprite::MoveDone));
	this->m_sprite->runAction(CCSequence::actions(moveTo, actionMoveDone, NULL));
}

ZSprite::ZSprite(char* fileName, bool randomSpawn)
{
	this->ZSprite::ZSprite(fileName);
	/*this->m_sprite = CCSprite::create(fileName);
	this->m_originSize = this->m_sprite->getContentSize();*/
	if(randomSpawn)
	{
		CCPoint pt = Utility::getRandomPointTop();
		this->m_sprite->setPosition(pt);
		this->m_startPoint = pt;
	}	
}

ZSprite::ZSprite(ZSprite& rhs, float spawnInterval)
{
	this->ZSprite::ZSprite(rhs.m_spriteFileName);
	//this->m_sprite = CCSprite::create(rhs.m_spriteFileName);
	this->m_sprite->setPosition(rhs.m_startPoint);

	this->m_startPoint = rhs.m_startPoint;
	this->m_spriteFileName = rhs.m_spriteFileName;

	this->m_originSize = this->m_sprite->getContentSize();

	this->m_moveToWrapper = CCMoveToWrapper(rhs.m_moveToWrapper.getDuration(), rhs.m_moveToWrapper.getEndPoint());
		
	if(spawnInterval != 0.0f)
	{
		CCDelayTime *delayAction = CCDelayTime::actionWithDuration(spawnInterval);
		CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(this,callfuncN_selector(ZSprite::MoveDone));
		this->m_sprite->runAction( CCSequence::actions(delayAction, m_moveToWrapper.getMoveTo(), actionMoveDone, NULL));
	}
	else
	{
		CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(this,callfuncN_selector(ZSprite::MoveDone));
		this->m_sprite->runAction(CCSequence::actions(m_moveToWrapper.getMoveTo(), actionMoveDone, NULL));		
	}
}

ZSprite::ZSprite(char* fileName, int direction, float velocity)
{
	/*this->m_sprite = CCSprite::create(fileName);
	this->m_spriteFileName = fileName;
	this->m_originSize = this->m_sprite->getContentSize();*/

	this->ZSprite::ZSprite(fileName);

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
			 //needtofix
			 pt.x = 320;
			 pt.y = 100;
			 this->m_sprite->setPosition(pt);
			 this->m_startPoint = pt;
			 linearMoveLeft(velocity);
			 break;
		}

	case (2/*NeoConstants::MOVE_RIGHT*/):
		{
			pt = Utility::getRandomPointOnOneSide(true);
			//needtofix
			pt.x = 0;
			pt.y = 300;
			this->m_sprite->setPosition(pt);
			this->m_startPoint = pt;
			linearMoveRight(velocity);
			break;
		}
	}
}

void ZSprite::addToCCNode(CCNode* node, int zOrder)
{
	assert(node!=NULL);

	if(this->m_sprite->getParent() != NULL)
	{
		return;
	}

	node->addChild(this->m_sprite, zOrder);
	m_parentNode = node;
}

void ZSprite::MoveDone(CCNode* sender)
{
	EnterCriticalSection(&GlobalFlag::m_csObject);
	
	CCSprite* sprite = (CCSprite*)sender;
	this->m_parentNode->removeChild(sprite,true);	
	sprite->autorelease();

	LeaveCriticalSection(&GlobalFlag::m_csObject);
}

void ZSprite::linearMoveDownWithRandomDirection(float velocity)
{
	this->m_moveToWrapper = Utility::generateLinearMoveToDownAction(velocity, Utility::getRandomBoolean(),this->m_sprite->getContentSize(), this->m_sprite->getPosition());

	//this->m_sprite->runAction( m_moveToWrapper.getMoveTo());
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(this,callfuncN_selector(ZSprite::MoveDone));
	this->m_sprite->runAction(CCSequence::actions(m_moveToWrapper.getMoveTo(), actionMoveDone, NULL));
}

void ZSprite::linearMoveLeft(float velocity)
{
	this->m_moveToWrapper = Utility::generateLinearMoveToHorizontalAction(velocity, true ,this->m_sprite->getContentSize(), this->m_sprite->getPosition());
	this->m_sprite->runAction( m_moveToWrapper.getMoveTo());

	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(this,callfuncN_selector(ZSprite::MoveDone));
	this->m_sprite->runAction(CCSequence::actions(m_moveToWrapper.getMoveTo(), actionMoveDone, NULL));
}

bool ZSprite::IsCollidingWith(CollidableObject* obj)
{

	CCSprite* leftSide = this->getSprite();
	CCSprite *rightSide =((ZSprite*)obj)->getSprite();
	CCRect leftRect = CCRectMake(
       leftSide->getPosition().x - (leftSide->getContentSize().width/2),
        leftSide->getPosition().y - (leftSide->getContentSize().height/2),
       leftSide->getContentSize().width,
      leftSide->getContentSize().height);

	CCRect rightRect = CCRectMake(
       rightSide->getPosition().x - (rightSide->getContentSize().width/2),
        rightSide->getPosition().y - (rightSide->getContentSize().height/2),
       rightSide->getContentSize().width,
      rightSide->getContentSize().height);

     if (CCRect::CCRectIntersectsRect(leftRect, rightRect))
     {
       return true;
     }
	 else
	 {
	   return false;
	 }
}

void ZSprite::linearMoveRight(float velocity)
{
	this->m_moveToWrapper = Utility::generateLinearMoveToHorizontalAction(velocity, false ,this->m_sprite->getContentSize(), this->m_sprite->getPosition());
	this->m_sprite->runAction( m_moveToWrapper.getMoveTo());

	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(this,callfuncN_selector(ZSprite::MoveDone));
	this->m_sprite->runAction(CCSequence::actions(m_moveToWrapper.getMoveTo(), actionMoveDone, NULL));
}

void ZSprite::linearMoveDown(float velocity, bool moveLeft)
{
	// Determine where we wish to shoot the projectile to
	this->m_moveToWrapper = Utility::generateLinearMoveToDownAction(velocity, Utility::getRandomBoolean(),this->m_sprite->getContentSize(), this->m_sprite->getPosition());
	this->m_sprite->runAction( m_moveToWrapper.getMoveTo());

	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(this,callfuncN_selector(ZSprite::MoveDone));
	this->m_sprite->runAction(CCSequence::actions(m_moveToWrapper.getMoveTo(), actionMoveDone, NULL));
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

CCSprite* ZSprite::getSprite()
{
    return m_sprite;
}

void ZSprite::setPosition(CCPoint pt)
{
	m_sprite->setPosition(pt);
}

void ZSprite::setOpacity(int opacity)
{
	m_sprite->setOpacity(opacity);
}

void ZSprite::setPosition(int x,int y)
{
	m_sprite->setPosition(ccp(x,y));
}

void ZSprite::setPositionX(int x)
{
	m_sprite->setPositionX(x);
}

void ZSprite::setPositionY(int y)
{
	m_sprite->setPositionX(y);
}

CCPoint ZSprite::getPostion()
{
	return m_sprite->getPosition();
}

<<<<<<< HEAD
CCNode* ZSprite::getParentNode()
{
	return m_parentNode;
=======
int ZSprite::getPostionX()
{
	return m_sprite->getPosition().x;
}

int ZSprite::getPostionY()
{
	return m_sprite->getPosition().y;
>>>>>>> ScriptGenerator
}

void ZSprite::addAnimation(string animName,CCActionInterval* anim)
{
	m_AnimMap.insert(map<string,CCActionInterval*>::value_type(animName,anim));
}

void ZSprite::playAnimation(string animName)
{
	if(m_parentNode == NULL)
	{
		printf("This target has not been added to any layer yet");
		return;
	}

	map<string,CCActionInterval*>::iterator it = m_AnimMap.find(animName);
	assert(it != m_AnimMap.end());

	/*if(m_curAnim != NULL)
		m_sprite->stopAction(m_curAnim);*/
	m_curAnim = it->second;
	m_sprite->runAction(it->second);

}


void ZSprite::playAnimationWithNewSprite(string animName)
{
	//if(m_parentNode == NULL)
	//{
	//	printf("This target has not been added to any layer yet");
	//	return;
	//}

	//map<string,CCRepeatForever*>::iterator it = m_AnimMap.find(animName);
	//assert(it != m_AnimMap.end());

	///*if(m_curAnim != NULL)
	//	m_sprite->stopAction(m_curAnim);*/
	//m_curAnim = it->second;
	ZSprite* newSprite = new ZSprite("pic\\explosion\\0.png");
	newSprite->addAnimation("explode",Utility::getAnimationAction("pic\\explosion\\", "png",26, false));
	newSprite->setPosition(m_sprite->getPositionX(),m_sprite->getPositionY());
	newSprite->addToCCNode(m_parentNode,0);
	newSprite->playAnimation("explode");
	int kkk = 0;

void ZSprite::playAnimationAndStop(string animName)
{
	if(m_parentNode == NULL)
	{
		printf("This target has not been added to any layer yet");
		return;
	}

	map<string,CCActionInterval*>::iterator it = m_AnimMap.find(animName);
	assert(it != m_AnimMap.end());

	if(m_curAnim != NULL)
		m_sprite->stopAction(m_curAnim);
	m_curAnim = it->second;
	
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(this,callfuncN_selector(ZSprite::MoveDone));
	this->m_sprite->runAction(CCSequence::actions(it->second, actionMoveDone, NULL));
}

CCSize ZSprite::getSize()
{
	return this->getSprite()->getContentSize();
}

int ZSprite::getWidth()
{
	return this->getSprite()->getContentSize().width;
}

int ZSprite::getHeight()
{
	return this->getSprite()->getContentSize().height;

}

ZSprite::~ZSprite(void)
{
}
