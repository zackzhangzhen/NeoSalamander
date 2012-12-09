#ifndef __UTILITY_H__
#define __UTILITY_H__
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>
#include "cocos2d.h"
#include "NeoConstants.h"
#include "action/CCMoveToWrapper.h"
using namespace cocos2d;
class Utility
{
public:
	
	~Utility(void);
	static float calcLength(CCPoint startPoint, CCPoint endPoint);
	static char* appendIntToString(char*, char* extention, int i);
	static char* convertStringToChar(std::string str);
	static CCActionInterval* getAnimationAction(char* filePrefix, char* extension, int suffixCount, bool startFromIndex0, bool repeat);
	static CCPoint getRandomPointTop();
	static CCPoint getRandomPointOnRandomSide();
	static CCPoint getRandomPointOnOneSide(bool left);
	static CCPoint* getRandomPointOnBothSides();
	static bool getRandomBoolean();
	static CCMoveToWrapper generateLinearMoveToDownAction(float velocity, bool moveLeft, CCSize size, CCPoint pos);
	static CCMoveToWrapper generateLinearMoveToHorizontalAction(float velocity, bool moveLeft, CCSize size, CCPoint pos);

private:
	Utility(void);
};
#endif

