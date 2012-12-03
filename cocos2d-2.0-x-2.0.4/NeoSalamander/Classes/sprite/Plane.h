#ifndef __PLANE_H__
#define __PLANE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "ZSprite.h"
using namespace cocos2d;

class Plane
{
public:
	Plane(void);
	Plane(char* sprite);//Pass the sprite file name to this constructor 
	CCSprite* GetSprite();//Get the pointer to the plane sprite
	void SetPostion(int x,int y);//Set the postion of the sprite in the layer
	void AddToLayer(CCLayer* layer);//The plane add itself to a layer
	~Plane(void);

protected:
	CCSprite* m_Sprite;
};

#endif
