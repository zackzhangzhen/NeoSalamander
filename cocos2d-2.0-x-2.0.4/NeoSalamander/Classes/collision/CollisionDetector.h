#pragma once
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <string>
using namespace cocos2d;

class ColObjArray
{
public:
	ColObjArray(void);
	~ColObjArray(void);

	string m_Tag;
	CCArray* m_objArr;
};

class CollisionDetector
{
public:
	CollisionDetector(void);
	~CollisionDetector(void);
};

