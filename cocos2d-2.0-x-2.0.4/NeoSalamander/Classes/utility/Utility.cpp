#include "Utility.h"
using namespace cocos2d;

Utility::Utility(void)
{

}

char* Utility::appendIntToString(char* origin, char* extention, int i)
{
	std::stringstream ss;
	ss << origin << i << "." << extention;

	std::string str = ss.str();
	char* finalStr =  convertStringToChar(str);
	return finalStr;
}

char* Utility::convertStringToChar(std::string str)
{
	int size = str.size();
	char * target = new char[size];
	for (int a=0;a<size;a++)
	{
		target[a]=str[a];
	}
	target[size] = '\0';
	return target;
}

 CCRepeatForever* Utility::getAnimationAction(char* filePrefix, char* extension, int suffixCount, bool startFromIndex0)
{
	CCAnimation * anim = CCAnimation::create();
	anim->setDelayPerUnit(0.03f);
	anim->retain();

	for(int i =  0; i < suffixCount; i++ )
	{
		int j = i;
		if(!startFromIndex0)
		{
			j++;
		}
		char* fileName = appendIntToString(filePrefix,extension, j);
		anim->addSpriteFrameWithFileName(fileName);
	}

	CCAnimate *theAnim = CCAnimate::create(anim);
	CCRepeatForever * actionRepeat = CCRepeatForever::create(theAnim);

	return actionRepeat;
}

 CCPoint Utility::getRandomPoint()
 {
	 CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int minX = 0 - NeoConstants::WIDTH_TOLERANCE;
	int maxX = winSize.width + NeoConstants::WIDTH_TOLERANCE;
	int rangeX = maxX - minX;
	// srand( TimGetTicks() );
	int actualX = ( rand() % rangeX ) + minX;
	int actualY = winSize.height + NeoConstants::HEIGHT_TOLERANCE;
	
	return ccp(actualX, actualY);
 }

 bool Utility::getRandomBoolean()
 {
	 int i = rand()%1;
	 return i == 0;
 }

 CCMoveTo* Utility::generateLinearMoveToAction(float velocity, bool moveLeft, CCSize size, CCPoint pos)
{
	// Determine where we wish to shoot the projectile to

	float ratioRange = 10 - 1;

	float randomRatio = ( rand() % 9 ) + 1;

	int realY = - size.height/2;
	int realYLen = pos.y - realY;
    int realXLen = realYLen/randomRatio;
	int realX;
	if(moveLeft)
	{
		realX = pos.x - realXLen;
	}
	else
	{
		realX = pos.x + realXLen;
	}
	
    CCPoint realDest = ccp(realX, realY);

    // Determine the length   
    float length = sqrtf((realXLen * realXLen) 
                                        + (realYLen*realYLen));
    
    float realMoveDuration = length/velocity;

	return CCMoveTo::actionWithDuration(realMoveDuration, realDest);
}

Utility::~Utility(void)
{
}
