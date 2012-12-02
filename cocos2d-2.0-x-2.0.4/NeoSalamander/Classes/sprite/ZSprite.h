#ifndef __Z_SPRITE_H__
#define __Z_SPRITE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"
using namespace cocos2d;
class ZSprite
{
public:
	ZSprite(void);
	ZSprite::ZSprite(char* fileName, CCSize originalSize);

	~ZSprite(void);


private:
	CCSize m_originSize;
	CCSprite* m_sprite;
};
#endif

