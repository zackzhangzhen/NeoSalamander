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

float Utility::calcLength(CCPoint startPoint, CCPoint endPoint)
{
	int xLen = endPoint.x - startPoint.x;
	int yLen = endPoint.y - startPoint.y;
	float length = sqrtf((xLen * xLen) 
                                        + (yLen*yLen));
	return length;
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

 CCActionInterval* Utility::getAnimationAction(char* filePrefix, char* extension, int suffixCount, bool startFromIndex0, bool repeat)
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

	if(!repeat)
	{
		return theAnim;
	}
	else
	{
		CCRepeatForever * actionRepeat = CCRepeatForever::create(theAnim);
		actionRepeat->retain();

		return actionRepeat;
	}
}

 CCPoint Utility::getRandomPointTop()
 {
	 CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int minX = 0 - NeoConstants::WIDTH_TOLERANCE;
	int maxX = winSize.width + NeoConstants::WIDTH_TOLERANCE;
	int rangeX = maxX - minX;
	// srand( TimGetTicks() );
	int random = rand();
	int actualX = ( random % rangeX ) + minX;
	int actualY = winSize.height + NeoConstants::HEIGHT_TOLERANCE;
	
	return ccp(actualX, actualY);
 }

 CCPoint Utility::getRandomPointOnOneSide(bool left)
 {
	 CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int minY= 0 - NeoConstants::HEIGHT_TOLERANCE;
	int maxY = winSize.height + NeoConstants::HEIGHT_TOLERANCE;
	int rangeY = maxY - minY;
	// srand( TimGetTicks() );
	int random = rand();
	int actualY = ( random % rangeY ) + minY;

	int actualX;
	if(left)
	{
		actualX = 0 - NeoConstants::WIDTH_TOLERANCE;
	}

	else
	{
		actualX = winSize.width + NeoConstants::WIDTH_TOLERANCE;
	}
	
	return ccp(actualX, actualY);
 }

 CCPoint Utility::getRandomPointOnRandomSide()
 {
	 bool left = Utility::getRandomBoolean();
	 CCPoint pt = getRandomPointOnOneSide(left);

	 return pt;
 }

 CCPoint* Utility::getRandomPointOnBothSides()
 {
	 CCPoint pt1 = getRandomPointOnOneSide(true);
	 int y = pt1.y;

	 CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	 int x = winSize.width + NeoConstants::WIDTH_TOLERANCE;
	 CCPoint pt2 = ccp(x,y);

	 CCPoint* ptPair = new CCPoint[2];
	 ptPair[0] = pt1;
	 ptPair[1] = pt2;
	 return ptPair;
 }

 bool Utility::getRandomBoolean()
 {
	 int random = rand();
	 int i = random%2;
	 return i == 0;
 }

 CCMoveToWrapper Utility::generateLinearMoveToDownAction(float velocity, bool moveLeft, CCSize size, CCPoint pos)
{
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

	CCMoveTo* moveTo = CCMoveTo::actionWithDuration(realMoveDuration, realDest);
	return CCMoveToWrapper(realMoveDuration, realDest);
}

CCMoveToWrapper Utility::generateLinearMoveToHorizontalAction(float velocity, bool moveLeft, CCSize size, CCPoint pos)
{
	int realX ;
	if(moveLeft)
	{
		realX = 0 - size.width;//don't use size.width/2, let it move further
	}
	else
	{
		realX = NeoConstants::WIN_WIDTH + size.width;//don't use size.width/2 let it move further
	}
	
    CCPoint realDest = ccp(realX, pos.y);

	float length = abs(realX - pos.x);
    float realMoveDuration = length/velocity;

	CCMoveTo* moveTo = CCMoveTo::actionWithDuration(realMoveDuration, realDest);
	return CCMoveToWrapper(realMoveDuration, realDest);
}

Utility::~Utility(void)
{
}
