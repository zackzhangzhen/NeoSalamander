#pragma once

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"
#include "NeoConstants.h"
#include "utility/Utility.h";
#include "action\CCMoveToWrapper.h"
#include "synchronization\GlobalFlag.h"
#include <map>
#include <string>
using namespace cocos2d;
class ZSprite:public CCObject
{
public:
	ZSprite(void);
	ZSprite(char* fileName);	
	ZSprite(char* fileName, CCNode* parentNode, int zOrder = 0);
	ZSprite(char* fileName, float duration, CCPoint startPt, CCPoint endPt);
	ZSprite(char* fileName, bool randomSpawn);
	ZSprite(char* fileName, int direction, float velocity = 1);
	ZSprite(ZSprite& rhs, float spawnInterval);
	bool isInScreen();
	void addToCCNode(CCNode* node, int zOrder);
	void MoveDone(CCNode* sender);

	void linearMoveDownWithRandomDirection(float velocity);
	void linearMoveLeft(float velocity);
	void linearMoveRight(float velocity);
	void linearMoveDown(float velocity, bool moveLeft);

	CCSprite* getSprite();
	CCPoint getPostion();
	int getPostionX();
	int getPostionY();
	CCSize getSize();
	int getWidth();
	int getHeight();
	void setOpacity(int opacity);
	void setPosition(int x,int y);
	void setPosition(CCPoint pt);
	void setPositionX(int x);
	void setPositionY(int y);
	void addAnimation(string animName, CCActionInterval* anim);//Add an animation to the sprite's anim map
	void playAnimation(string animName);//Play an animation of the sprite,designated by the animName
	void playAnimationAndStop(string animName);
	~ZSprite(void);


protected:
	CCSize m_originSize;	
	CCSprite* m_sprite;
	//used for the copy constructor - start
	char* m_spriteFileName;
	CCPoint m_startPoint;
	CCMoveToWrapper m_moveToWrapper;	

	CCActionInterval* m_curAnim;
    CCNode* m_parentNode;
	map<string,CCActionInterval*> m_AnimMap;
};

