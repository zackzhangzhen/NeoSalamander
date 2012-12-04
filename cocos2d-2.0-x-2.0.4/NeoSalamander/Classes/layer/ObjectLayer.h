#pragma once
#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

#include "sprite/ZSprite.h"

#include "NeoConstants.h"

class ObjectLayer: public cocos2d::CCLayer
{
public:
	ObjectLayer(void);
	void randomSpawn(float dt);
	void scheduleRandomSpawn(float dt);
	~ObjectLayer(void);
	static ObjectLayer* createObjectLayer(void);

private:
	static const char* STEWIE;
};

