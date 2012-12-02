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

Utility::~Utility(void)
{
}
