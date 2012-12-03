#ifndef __UTILITY_H__
#define __UTILITY_H__
#include <string>
#include <sstream>
#include <iostream>
#include "cocos2d.h"
#include "NeoConstants.h"
using namespace cocos2d;
class Utility
{
public:
	
	~Utility(void);

	static char* appendIntToString(char*, char* extention, int i);
	static char* convertStringToChar(std::string str);
	static CCRepeatForever* getAnimationAction(char* filePrefix, char* extension, int suffixCount, bool startFromIndex0);
	static CCPoint getRandomPoint();
	static bool getRandomBoolean();
	static CCMoveTo* generateLinearMoveToAction(float velocity, bool moveLeft, CCSize size, CCPoint pos);
private:
	Utility(void);
};
#endif

