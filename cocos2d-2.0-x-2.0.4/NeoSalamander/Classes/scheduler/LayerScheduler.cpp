#include "LayerScheduler.h"
#include "../../Classes/layer/ObjectLayer.h"

int enemy = 0;
int hero = 0;
LayerScheduler::LayerScheduler(void)
{
}

LayerScheduler::LayerScheduler(CCNode* _parentNode)
{
	parentNode = _parentNode;
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

void LayerScheduler::scheduleRandomSpawn(float dt,int targetArray)
{
	switch (targetArray)
	{
	case TARGET_ARRAY_NO::HERO:
		this->schedule(schedule_selector(LayerScheduler::randomSpawnHero), dt);	
		break;
	case TARGET_ARRAY_NO::ENEMY:
		this->schedule(schedule_selector(LayerScheduler::randomSpawnEnemy), dt);
		break;
	case TARGET_ARRAY_NO::FRIENDLY_FIRE:
		this->schedule(schedule_selector(LayerScheduler::randomSpawnFriendlyFire), dt);
		break;
	case TARGET_ARRAY_NO::HOSTILE_FIRE:
		this->schedule(schedule_selector(LayerScheduler::randomSpawnHostileFire), dt);
		break;
	default:
		;
	}
}

void LayerScheduler::randomSpawnHero(float dt)
{
	//needtofix
	if(enemy>=1)
		return;

	ZSprite* sprite = new ZSprite(tempValHolder.tempSpriteFileName, tempValHolder.tempDirection, tempValHolder.tempVelocity);
	sprite->addToCCNode(parentNode, tempValHolder.tempZOrder);

	((ObjectLayer*)(this->parentNode))->getHeroArray()->m_objArr->push_back(sprite);

	enemy++;
}



void LayerScheduler::randomSpawnEnemy(float dt)
{
		
	if(hero>=1)
		return;

	ZSprite* sprite = new ZSprite(tempValHolder.tempSpriteFileName, tempValHolder.tempDirection, tempValHolder.tempVelocity);
	sprite->addToCCNode(parentNode, tempValHolder.tempZOrder);

	((ObjectLayer*)(this->parentNode))->getEnemyArray()->m_objArr->push_back(sprite);

	hero++;
}

void LayerScheduler::randomSpawnFriendlyFire(float dt)
{

	if(enemy>=1)
		return;

	ZSprite* sprite = new ZSprite(tempValHolder.tempSpriteFileName, tempValHolder.tempDirection, tempValHolder.tempVelocity);
	sprite->addToCCNode(parentNode, tempValHolder.tempZOrder);

	((ObjectLayer*)(this->parentNode))->getFreindlyFireArray()->m_objArr->push_back(sprite);

	enemy++;
}

void LayerScheduler::randomSpawnHostileFire(float dt)
{

	if(enemy>=1)
		return;

	ZSprite* sprite = new ZSprite(tempValHolder.tempSpriteFileName, tempValHolder.tempDirection, tempValHolder.tempVelocity);
	sprite->addToCCNode(parentNode, tempValHolder.tempZOrder);

	((ObjectLayer*)(this->parentNode))->getHostileFireArray()->m_objArr->push_back(sprite);

	enemy++;
}



void LayerScheduler::update(CCTime dt)
{
	ObjectLayer* temp = (ObjectLayer*)this->parentNode;
	temp->cd->Detect();
	//int kkk = 0;
}

LayerScheduler::~LayerScheduler(void)
{
}
