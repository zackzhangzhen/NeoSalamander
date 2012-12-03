#ifndef __Z_SPRITE_H__
#define __Z_SPRITE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"
#include "NeoConstants.h"
#include "utility/Utility.h";
using namespace cocos2d;
class ZSprite
{
public:
	ZSprite(void);
	ZSprite(char* fileName);
	ZSprite(char* fileName, bool randomSpawn);
	ZSprite(char* fileName, bool randomSpawn, bool linearMove);
	bool isInScreen();

	void linearMoveWithRandomDirection(float velocity);
	void linearMove(float velocity, bool moveLeft);
	~ZSprite(void);


private:
	CCSize m_originSize;
	CCSprite* m_sprite;
};
#endif

