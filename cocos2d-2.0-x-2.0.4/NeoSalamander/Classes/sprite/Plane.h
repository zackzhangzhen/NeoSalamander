#ifndef __PLANE_H__
#define __PLANE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
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
class Plane:public CCObject
{
public:
	Plane(void);
	Plane(char* sprite);//Pass the sprite file name to this constructor 
	CCSprite* GetSprite();//Get the pointer to the plane sprite
	void SetPosition(int x,int y);//Set the postion of the sprite in the layer
	CCPoint GetPostion();
	void AddToLayer(CCLayer* layer);//The plane add itself to a layer
	void AddAnimation(string animName,CCRepeatForever* anim);//Add an animation to the plane's anim map
	void PlayAnimation(string animName);//Play an animation of the plane,designated by the animName
	void Fire();

	void EquipBullet(char* sprite);
	void FireDone(CCNode* sender);
	~Plane(void);

protected:
	CCSprite* m_SpritePlane;
	CCSprite* m_SpriteBullet;
	    char  m_SpriteFileBullet[256];
	map<string,CCRepeatForever*> m_AnimMap;
	CCRepeatForever* m_curAnim;
    CCLayer* m_curLayer;
};

#endif
