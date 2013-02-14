#ifndef __UTILITY_H__
#define __UTILITY_H__
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>
#include "cocos2d.h"
#include "NeoConstants.h"
#include "action/CCMoveToWrapper.h"
#include "SimpleAudioEngine.h" 
using namespace cocos2d;
class Utility
{
public:
	
	~Utility(void);
	static char* zstrcat(char* origin, char* extention);
	static float calcLength(CCPoint startPoint, CCPoint endPoint);
	static char* appendIntToString(char*, char* extention, int i);
	static char* convertStringToChar(std::string str);
	static CCActionInterval* getAnimationAction(char* filePrefix, char* extension, int suffixCount, bool startFromIndex0, bool repeat);
	static CCPoint getRandomPointTop();
	static CCPoint getRandomPointOnRandomSide();
	static CCPoint getRandomPointOnOneSide(bool left);
	static CCPoint* getRandomPointOnBothSides();
	static void playSound(const char* soundName, bool repeat = false);
	static void playMusic(const char* musicName, bool repeat = true);
	static void stopMusic();
	static bool getRandomBoolean();
	static CCMoveToWrapper generateLinearMoveToDownAction(float velocity, bool moveLeft, CCSize size, CCPoint pos);
	static CCMoveToWrapper generateLinearMoveToHorizontalAction(float velocity, bool moveLeft, CCSize size, CCPoint pos);
	static CCPoint getCenterPt();

private:
	Utility(void);
};
#endif

