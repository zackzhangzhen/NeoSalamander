#ifndef __Z_SPRITE_H__
#define __Z_SPRITE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"
#include "NeoConstants.h"
#include "utility/Utility.h";
#include "action\CCMoveToWrapper.h"
#include <map>
#include <string>
using namespace cocos2d;
class ZSprite:public CCObject
{
public:
	ZSprite(void);
	ZSprite(char* fileName);
	ZSprite(char* fileName, bool randomSpawn);
	ZSprite(char* fileName, int direction, float velocity = 1);
	ZSprite(ZSprite& rhs, float spawnInterval);
	bool isInScreen();
	void addToCCNode(CCNode* node, int zOrder);

	void linearMoveDownWithRandomDirection(float velocity);
	void linearMoveLeft(float velocity);
	void linearMoveRight(float velocity);
	void linearMoveDown(float velocity, bool moveLeft);

	CCSprite* getSprite();
	CCPoint getPostion();
	void setPosition(int x,int y);
	void addAnimation(string animName,CCRepeatForever* anim);//Add an animation to the sprite's anim map
	void playAnimation(string animName);//Play an animation of the sprite,designated by the animName

	~ZSprite(void);


protected:
	CCSize m_originSize;	
	CCSprite* m_sprite;
	//used for the copy constructor - start
	char* m_spriteFileName;
	CCPoint m_startPoint;
	CCMoveToWrapper m_moveToWrapper;	

	CCRepeatForever* m_curAnim;
    CCNode* m_parentNode;
	map<string,CCRepeatForever*> m_AnimMap;
};
#endif

