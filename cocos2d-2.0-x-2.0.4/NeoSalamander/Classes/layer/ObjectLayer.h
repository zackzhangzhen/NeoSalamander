#pragma once
#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

#include "sprite/ZSprite.h"

#include "NeoConstants.h"

#include "scheduler/ScheduleTempValHolder.h"
#include "scheduler/LayerScheduler.h"

class ObjectLayer: public cocos2d::CCLayer
{
public:
	ObjectLayer(void);
	void randomSpawn(float dt);
	virtual void scheduleObjects();
	void scheduleRandomSpawn(float dt, const char* spriteFileName,int direction, float velocity, int zOrder = 0);
	void scheduleRandomSpawnInBulk(float dt, const char* spriteFileName,int direction,int spawnBulkCount, float spawnInterval, float velocity,int zOrder = 0);
	void randomSpawnInBulk(float dt);
	~ObjectLayer(void);
	static ObjectLayer* createObjectLayer(void);

private:
	static const char* STEWIE;
	static const char* BLACK_OPS;
	static const char* LAND_ROVER;
	static const char* RAVEN;	
};

