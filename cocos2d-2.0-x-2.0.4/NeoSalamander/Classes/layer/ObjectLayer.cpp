#include "ObjectLayer.h"

extern map<string,CollisionHandler*> collHandlers;
const char* ObjectLayer::STEWIE = "pic\\object\\stewie.png";
const char* ObjectLayer::BLACK_OPS = "pic\\enemy\\blackops.png";
const char* ObjectLayer::LAND_ROVER = "pic\\enemy\\landrover.png";
const char* ObjectLayer::RAVEN = "pic\\enemy\\raven.png";


OLCollisionHandler::OLCollisionHandler(CCNode* parent)
{
	m_Parent = parent;
}

void OLCollisionHandler::HandleCollison(CCNode* layer,CollidableObject* obj1, CollidableObject* obj2)
{

}

ObjectLayer::ObjectLayer(void)
{
	m_HeroArr = NULL;
	m_EnemyArr = NULL;
	m_FriendlyFireArr = NULL;
	m_HostileFireArr = NULL;

	cd = NULL;
}

void ObjectLayer::Initialize(void)
{
	m_HeroArr = new CollObjArray("hero");
	m_EnemyArr = new CollObjArray("enemy");
	m_FriendlyFireArr = new CollObjArray("friendlyfire");
	m_HostileFireArr = new CollObjArray("hostilefire");

	cd = new CollisionDetector();
	vector<string> temp;
	temp.push_back("enemy");
	cd->AddToTargetMap(string("friendlyfire_enemy"),temp);
	OLCollisionHandler* ch = new OLCollisionHandler(this);
	collHandlers.insert(map<string,CollisionHandler*>::value_type(string("friendlyfire_enemy"),ch));

	//scheduleUpdate();

	
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





void ObjectLayer::scheduleUpdate()
{
	LayerScheduler* ls = new LayerScheduler(this);
	//ls->schedule(schedule_selector(LayerScheduler::update));
	this->addChild(ls,0);
	ls->scheduleUpdate();
}


void ObjectLayer::scheduleObjects()
{
	this->scheduleRandomSpawnInBulk(10.0F, STEWIE, NeoConstants::MOVE_DOWN,5,0.5f, 90.0F, 0);
	this->scheduleRandomSpawnInBulk(15.0F, LAND_ROVER, NeoConstants::MOVE_DOWN,3,0.8F,70.0f);
	this->scheduleRandomSpawnInBulk(6.0F, BLACK_OPS, NeoConstants::MOVE_DOWN,1,0.5f, 90.0F, 0);
	this->scheduleRandomSpawn(30.0F, RAVEN, NeoConstants::MOVE_LEFT, 10.0F, 0);
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

ObjectLayer::~ObjectLayer(void)
{
}
