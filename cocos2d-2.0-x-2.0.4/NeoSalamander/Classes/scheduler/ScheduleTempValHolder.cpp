#include "ScheduleTempValHolder.h"

const char* ScheduleTempValHolder::NONE = "NONE";

ScheduleTempValHolder::ScheduleTempValHolder(void)
{
	tempSpriteFileName = (char*)NONE;
	tempDirection = NeoConstants::MOVE_DOWN;
	tempSpawnBulkCount = 3;
	tempSpawnInterval = 2.0f;
	tempVelocity = 100.0F;
	tempZOrder = 0;
}

void ScheduleTempValHolder::resetTempValueForSingleSprite(char* fileName, int dir, float velocity, int zOrder)
{
	tempSpriteFileName = fileName;
	tempDirection = dir;
	tempVelocity = velocity;
	tempZOrder = zOrder;

}

void ScheduleTempValHolder::resetTempValueForBulkSprite(char* fileName, int dir, int bulkCount, float spawnInterval, float velocity, int zOrder)
{
	tempSpriteFileName = fileName;
	tempDirection = dir;
	tempSpawnBulkCount = bulkCount;
	tempSpawnInterval = spawnInterval;
	tempVelocity = velocity;
	tempZOrder = zOrder;
}

ScheduleTempValHolder::~ScheduleTempValHolder(void)
{
}
