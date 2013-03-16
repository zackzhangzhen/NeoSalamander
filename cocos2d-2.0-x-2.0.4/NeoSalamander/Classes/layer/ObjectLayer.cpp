#include "layer\ObjectLayer.h"
#include "scene\ZTitleScene.h"

const char* ObjectLayer::STEWIE = "pic\\object\\stewie.png";
const char* ObjectLayer::BLACK_OPS = "pic\\enemy\\blackops.png";
const char* ObjectLayer::LAND_ROVER = "pic\\enemy\\landrover.png";
const char* ObjectLayer::RAVEN = "pic\\enemy\\raven.png";

ObjectLayer::ObjectLayer(ZTitleScene* parentScene)
{
	this->m_parentScene = parentScene;
}

ObjectLayer * ObjectLayer::createObjectLayer(ZTitleScene* parentScene)
{
	ObjectLayer *pRet = new ObjectLayer(parentScene);
	
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

void ObjectLayer::scheduleObjects()
{
	/*this->scheduleRandomSpawnInBulk(10.0F, STEWIE, NeoConstants::MOVE_DOWN,5,0.5f, 90.0F, 0);
	this->scheduleRandomSpawnInBulk(15.0F, LAND_ROVER, NeoConstants::MOVE_DOWN,3,0.8F,70.0f);
	this->scheduleRandomSpawnInBulk(6.0F, BLACK_OPS, NeoConstants::MOVE_DOWN,1,0.5f, 90.0F, 0);
	this->scheduleRandomSpawn(30.0F, RAVEN, NeoConstants::MOVE_LEFT, 10.0F, 0);*/

	this->scheduleRandomSpawnInBulk(Utility::getRangedNumber(8,11), STEWIE, Utility::getRangedNumber(0,3),Utility::getRangedNumber(1,4),1.0f, Utility::getRangedNumber(1,91), 0);
	this->scheduleRandomSpawnInBulk(Utility::getRangedNumber(8,11), LAND_ROVER, Utility::getRangedNumber(0,3),Utility::getRangedNumber(1,4),1.0f, Utility::getRangedNumber(1,91), 0);
	this->scheduleRandomSpawnInBulk(Utility::getRangedNumber(8,11), BLACK_OPS, Utility::getRangedNumber(0,3),Utility::getRangedNumber(1,4),1.0f, Utility::getRangedNumber(1,91), 0);
	this->scheduleRandomSpawnInBulk(Utility::getRangedNumber(8,11), RAVEN, Utility::getRangedNumber(0,3),Utility::getRangedNumber(1,4),1.0f, Utility::getRangedNumber(1,91), 0);
}

void ObjectLayer::addGameMenu()
{
	ZMainMenu* mainMenu = new ZMainMenu(this,true);
	mainMenu->init();
	//ZLoadMenu* loadMenu = new ZLoadMenu(this,true);

}

void ObjectLayer::scheduleRandomSpawn(float dt, const char* spriteFileName,int direction, float velocity, int zOrder)
{
	LayerScheduler* scheduler = new LayerScheduler((char*)spriteFileName, direction, 0, 0.0F, velocity, zOrder, this);
	this->addChild(scheduler, 0);
	scheduler->scheduleRandomSpawn(dt);	
}

void ObjectLayer::scheduleRandomSpawnInBulk(float dt, const char* spriteFileName,int direction,int spawnBulkCount,float spawnInterval, float velocity,int zOrder)
{
	LayerScheduler* scheduler = new LayerScheduler((char*)spriteFileName, direction, spawnBulkCount, spawnInterval, velocity, zOrder, this);
	this->addChild(scheduler, 0);
	scheduler->scheduleRandomSpawnInBulk(dt);	
}

ZTitleScene* ObjectLayer::getParentTitleScene()
{
	return this->m_parentScene;
}

ObjectLayer::~ObjectLayer(void)
{
}
