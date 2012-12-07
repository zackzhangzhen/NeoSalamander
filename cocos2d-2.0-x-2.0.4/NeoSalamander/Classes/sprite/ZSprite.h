#ifndef __Z_SPRITE_H__
#define __Z_SPRITE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"
#include "NeoConstants.h"
#include "utility/Utility.h";
#include "action\CCMoveToWrapper.h"
using namespace cocos2d;
class ZSprite
{
public:
	ZSprite(void);
	ZSprite(char* fileName);
	ZSprite(char* fileName, bool randomSpawn);
	ZSprite(char* fileName, bool randomSpawn, int direction, float velocity = 1);
	ZSprite(ZSprite& rhs, float spawnInterval);
	bool isInScreen();
	void addToCCNode(CCNode* node, int zOrder);

	void linearMoveDownWithRandomDirection(float velocity);
	void linearMoveLeft(float velocity);
	void linearMoveRight(float velocity);
	void linearMoveDown(float velocity, bool moveLeft);
	~ZSprite(void);


private:
	CCSize m_originSize;	
	CCSprite* m_sprite;
	//used for the copy constructor - start
	char* m_spriteFileName;
	CCPoint m_startPoint;
	CCMoveToWrapper m_moveToWrapper;	
};
#endif

