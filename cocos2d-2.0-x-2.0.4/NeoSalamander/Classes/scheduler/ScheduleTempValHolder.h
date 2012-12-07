#pragma once
#include "NeoConstants.h"
class ScheduleTempValHolder
{
public:
	ScheduleTempValHolder(void);
	ScheduleTempValHolder(char*, int, int, float, float, int);
	~ScheduleTempValHolder(void);

	char* tempSpriteFileName;
	int tempDirection;
	int tempSpawnBulkCount;
	float tempSpawnInterval;
	float tempVelocity;
	int tempZOrder;

	void resetTempValueForSingleSprite(char* fileName, int dir, float velocity, int zOrder);
	void resetTempValueForBulkSprite(char* fileName, int dir, int bulkCount,float spawnInterval, float velocity, int zOrder);

	static const char* NONE;
};

