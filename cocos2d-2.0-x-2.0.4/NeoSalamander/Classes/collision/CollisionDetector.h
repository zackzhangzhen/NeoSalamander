#pragma once
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <string>
#include <map>
#include <vector>
using namespace cocos2d;

class CollidableObject
{
public:
	virtual bool IsCollidingWith(CollidableObject* obj);
};


class CollObjArray
{
public:
	CollObjArray(void);
	~CollObjArray(void);

	string m_Tag;
	//CCArray* m_objArr;
	vector<CollidableObject*>* m_objArr;
};


class CollisionHandler
{
public:
	CollisionHandler(void);
	virtual void HandleCollison(CCLayer* layer,CollidableObject* obj1, CollidableObject* obj2) = 0; 
	CCLayer* m_Layer;
};



class CollisionDetector
{
public:
	CollisionDetector(void);
	~CollisionDetector(void);
	void AddToCollArray(CollObjArray* _collObjArray);
	void AddToTargetMap(string& tag, vector<string>& vec);
	void Detect();

	//void (__thiscall *test_handler)(CCNode*,CCNode*);

protected:
	CollObjArray* FindArrayByTag(string tag);
	void CollideTwoArrays(CollObjArray* arrLeft,CollObjArray* arrRight);

	//map<string,void (CCNode*,CCNode*)> collHandlerMap;
	vector<CollObjArray*> m_AllCollObj;
	map<string,vector<string>> m_tgtMap;
};


 //map<string,CollisionHandler*> collHandlers;