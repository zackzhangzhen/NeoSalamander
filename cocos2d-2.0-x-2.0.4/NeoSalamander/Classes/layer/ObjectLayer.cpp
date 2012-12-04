#include "ObjectLayer.h"

const char* ObjectLayer::STEWIE = "pic\\object\\stewie.png";

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

void ObjectLayer::scheduleRandomSpawn(float dt)
{
	this->schedule( schedule_selector(ObjectLayer::randomSpawn),dt);
}

void ObjectLayer::randomSpawn(float dt)
{
	ZSprite* sprite = new ZSprite((char*)STEWIE, true, NeoConstants::MOVE_DOWN, 100.0F);
	sprite->addToCCNode(this, 0);
}

ObjectLayer::~ObjectLayer(void)
{
}
