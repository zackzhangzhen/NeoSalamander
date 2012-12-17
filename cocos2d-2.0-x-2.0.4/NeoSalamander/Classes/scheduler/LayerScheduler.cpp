#include "LayerScheduler.h"
#include "../../Classes/layer/ObjectLayer.h"

LayerScheduler::LayerScheduler(void)
{
}

LayerScheduler::LayerScheduler(CCNode* parentNode)
{
}

ScheduleTempValHolder LayerScheduler::getTempValHolder()
{
	return tempValHolder;
}

void LayerScheduler::scheduleUpdate()
{
	this->schedule(schedule_selector(LayerScheduler::update));
}

LayerScheduler::LayerScheduler(char* fileName, int dir, int bulkCount, float spawnInterval, float velocity, int zOrder, CCNode* parentNode)
{
	this->tempValHolder = ScheduleTempValHolder(fileName, dir, bulkCount, spawnInterval, velocity, zOrder);
	this->parentNode = parentNode;
}

void LayerScheduler::scheduleRandomSpawnInBulk(float dt)
{
	this->schedule(schedule_selector(LayerScheduler::randomSpawnInBulk), dt);
}

void LayerScheduler::randomSpawnInBulk(float dt)
{
	bool firstOne = true;
	ZSprite* firstSprite = NULL;
	for(int i = 0; i < tempValHolder.tempSpawnBulkCount; i++)
	{
		if(firstOne)
		{
			firstOne = false;
			firstSprite = new ZSprite(tempValHolder.tempSpriteFileName, tempValHolder.tempDirection, tempValHolder.tempVelocity);
			firstSprite->addToCCNode(this, tempValHolder.tempZOrder);
			continue;
		}

		ZSprite* sprite = new ZSprite(*firstSprite, tempValHolder.tempSpawnInterval*(i));	
		sprite->addToCCNode(parentNode, tempValHolder.tempZOrder);
	}
}

void LayerScheduler::scheduleRandomSpawn(float dt)
{
	this->schedule(schedule_selector(LayerScheduler::randomSpawn), dt);	
}

void LayerScheduler::randomSpawn(float dt)
{
	ZSprite* sprite = new ZSprite(tempValHolder.tempSpriteFileName, tempValHolder.tempDirection, tempValHolder.tempVelocity);
	sprite->addToCCNode(parentNode, tempValHolder.tempZOrder);
}

void LayerScheduler::update(CCTime dt)
{
	//((ObjectLayer*)this->parentNode)->cd->Detect();
	int kkk = 0;
}

LayerScheduler::~LayerScheduler(void)
{
}
