#pragma once
#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

#include "sprite/ZSprite.h"

#include "NeoConstants.h"

#include "scheduler/ScheduleTempValHolder.h"
class LayerScheduler: public cocos2d::CCNode
{
public:
	LayerScheduler(void);
	LayerScheduler(CCNode* parentNode);
	LayerScheduler(char* fileName, int dir, int bulkCount, float spawnInterval, float velocity, int zOrder, CCNode* parentNode);
	ScheduleTempValHolder LayerScheduler::getTempValHolder();
	void randomSpawn(float dt);
	void randomSpawnInBulk(float dt);
	void scheduleRandomSpawnInBulk(float dt);
	void scheduleRandomSpawn(float dt);
	void update(CCTime dt);
	void scheduleUpdate();
	~LayerScheduler(void);

private:
	ScheduleTempValHolder tempValHolder;
	CCNode* parentNode;
};

