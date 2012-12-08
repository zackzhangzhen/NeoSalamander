#ifndef __PLANE_H__
#define __PLANE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "NeoConstants.h"
#include "ZSprite.h"
#include <map>
#include <string>
using namespace cocos2d; 

/*
 Plane* pl = new Plane("picName");
 pl->SetPosition(100,100);
 pl->AddToLayer(layPtr);
 pl->AddAnimation("anim1",Utility::getAnimationAction("pre","ext",5,true));
 pl->PlayAnimation("anim1");
*/
class Plane:public ZSprite
{
public:
	Plane(void);
	Plane(char* sprite);//Pass the sprite file name to this constructor 
	void Fire(float velocity);

	void EquipBullet(char* sprite);
	void FireDone(CCNode* sender);
	~Plane(void);

protected:
	ZSprite* m_SpriteBullet;
	char  m_SpriteFileBullet[256];
	

};

#endif
