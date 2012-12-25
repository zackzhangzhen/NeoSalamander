#pragma once
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <string>
#include <map>
#include <vector>
using namespace cocos2d;

class CollidableObject:public CCNode
{
public:
	virtual bool IsCollidingWith(CollidableObject* obj);
};


class CollObjArray
{
public:
	CollObjArray(void);
	CollObjArray(string tag);
	~CollObjArray(void);

	//tofillin
	void addElement(CollidableObject* obj);
	int getSize();
	CollidableObject* getAt(int i);
	void removeByPointer(CollidableObject* obj);
	string m_Tag;
	//CCArray* m_objArr;
	vector<CollidableObject*>* m_objArr;
};


class CollisionHandler:public CCNode
{
public:
	CollisionHandler(void);
	CollisionHandler(CCNode* parent);
	virtual void HandleCollison(CCNode* layer,CollidableObject* obj1, CollidableObject* obj2); 
	CCNode* m_Parent;
};



class CollisionDetector
{
public:
	CollisionDetector(void);
	~CollisionDetector(void);
	void AddToCollArray(CollObjArray* _collObjArray);
	void AddToTargetMap(string& tag, vector<string>& vec);
	void Detect();

	//tofillin
	void removeObjectByPointer(CollidableObject* obj);
	//void (__thiscall *test_handler)(CCNode*,CCNode*);

protected:
	CollObjArray* FindArrayByTag(string tag);
	void CollideTwoArrays(CollObjArray* arrLeft,CollObjArray* arrRight);

	//map<string,void (CCNode*,CCNode*)> collHandlerMap;
	vector<CollObjArray*> m_AllCollObj;
	map<string,vector<string>> m_tgtMap;
};


 //map<string,CollisionHandler*> collHandlers;