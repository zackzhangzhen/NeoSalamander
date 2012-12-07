#include "ObjectLayer.h"

const char* ObjectLayer::STEWIE = "pic\\object\\stewie.png";
const char* ObjectLayer::BLACK_OPS = "pic\\enemy\\blackops.png";
const char* ObjectLayer::LAND_ROVER = "pic\\enemy\\landrover.png";
const char* ObjectLayer::RAVEN = "pic\\enemy\\raven.png";

ObjectLayer::ObjectLayer(void)
{

}

ObjectLayer * ObjectLayer::createObjectLayer(void)
{
	ObjectLayer *pRet = new ObjectLayer();
	
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

void ObjectLayer::scheduleEnemies()
{
	//this->scheduleRandomSpawn(1.0F, STEWIE, NeoConstants::MOVE_DOWN, 40.0F, 0);
	//this->scheduleRandomSpawnInBulk(3.0F, STEWIE, NeoConstants::MOVE_DOWN,5,0.5f, 90.0F, 0);
	this->scheduleRandomSpawn(5.0F, RAVEN, NeoConstants::MOVE_LEFT,120.0F,0);
}

void ObjectLayer::scheduleRandomSpawn(float dt, const char* spriteFileName,int direction, float velocity, int zOrder)
{
	this->tempValHolder.resetTempValueForSingleSprite((char*)spriteFileName, direction, velocity, zOrder); 
	this->schedule(schedule_selector(ObjectLayer::randomSpawn), dt);	
}

void ObjectLayer::scheduleRandomSpawnInBulk(float dt, const char* spriteFileName,int direction,int spawnBulkCount,float spawnInterval, float velocity,int zOrder)
{
	this->tempValHolder.resetTempValueForBulkSprite((char*)spriteFileName, direction,spawnBulkCount,spawnInterval, velocity, zOrder); 
	this->schedule(schedule_selector(ObjectLayer::randomSpawnInBulk), dt);
}

void ObjectLayer::randomSpawn(float dt)
{
	ZSprite* sprite = new ZSprite(tempValHolder.tempSpriteFileName, true, tempValHolder.tempDirection, tempValHolder.tempVelocity);
	sprite->addToCCNode(this, tempValHolder.tempZOrder);
}

void ObjectLayer::randomSpawnInBulk(float dt)
{
	bool firstOne = true;
	ZSprite* firstSprite = NULL;
	for(int i = 0; i < tempValHolder.tempSpawnBulkCount; i++)
	{
		if(firstOne)
		{
			firstOne = false;
			firstSprite = new ZSprite(tempValHolder.tempSpriteFileName, true, tempValHolder.tempDirection, tempValHolder.tempVelocity);
			firstSprite->addToCCNode(this, tempValHolder.tempZOrder);
			continue;
		}

		ZSprite* sprite = new ZSprite(*firstSprite, tempValHolder.tempSpawnInterval*(i));	
		sprite->addToCCNode(this, tempValHolder.tempZOrder);
	}
}

ObjectLayer::~ObjectLayer(void)
{
}
