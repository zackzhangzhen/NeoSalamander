#pragma once
#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

#include "sprite/ZSprite.h"

#include "NeoConstants.h"

#include "scheduler/ScheduleTempValHolder.h"
#include "scheduler/LayerScheduler.h"

#include "collision/CollisionDetector.h"

enum TARGET_ARRAY_NO
{
	NOTHING,
	HERO,
	ENEMY,
	FRIENDLY_FIRE,
	HOSTILE_FIRE
};


class OLCollisionHandler:public CollisionHandler
{
public:
	OLCollisionHandler(CCNode* parent);
	virtual void HandleCollison(CCNode* layer,CollidableObject* obj1, CollidableObject* obj2);
};

class ObjectLayer: public cocos2d::CCLayer
{
public:
	ObjectLayer(void);
	void Initialize(void);
	void randomSpawn(float dt);
	virtual void scheduleUpdate();
	virtual void scheduleObjects();
	//void scheduleRandomSpawn(float dt, const char* spriteFileName,int direction, float velocity, bool bHostile, int zOrder = 0);
	void scheduleRandomSpawn(float dt, const char* spriteFileName,int direction, float velocity, int targetrArray,int zOrder = 0);
	void scheduleRandomSpawnInBulk(float dt, const char* spriteFileName,int direction,int spawnBulkCount, float spawnInterval, float velocity,int zOrder = 0);
	void randomSpawnInBulk(float dt);
	CollObjArray* getHeroArray();
	CollObjArray* getEnemyArray();
	CollObjArray* getFreindlyFireArray();
	CollObjArray* getHostileFireArray();
	~ObjectLayer(void);
	static ObjectLayer* createObjectLayer(void);
	void ccTouchesEnded(CCSet* touches, CCEvent* event);

	CollisionDetector* cd;
	//needtofix
	int m_curTargetArrayNo;

private:
	static const char* STEWIE;
	static const char* BLACK_OPS;
	static const char* LAND_ROVER;
	static const char* RAVEN;	

	CollObjArray* m_HeroArr;
	CollObjArray* m_EnemyArr;
	CollObjArray* m_FriendlyFireArr;
	CollObjArray* m_HostileFireArr;
};

