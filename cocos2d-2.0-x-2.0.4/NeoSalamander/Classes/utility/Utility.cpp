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

char* Utility::zstrcat(char* origin, char* extention)
{
	std::stringstream ss;
	ss << origin << extention;
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

		return actionRepeat;
	}
}

 int Utility::getRangedNumber(float min, float max)
 {
	int range = max - min;
	int random = rand();

	int actual = random % range;
	
	return actual + min;
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

CCPoint Utility::getCenterPt()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
    return ccp(size.width/2, size.height - 150);
}
CCPoint Utility::getTopRightPt()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
    return ccp(size.width, size.height);
}

void Utility::playSound(const char* soundName, bool repeat)
{
	if(soundName == NULL)
	{
		return;
	}

	//concatenate the sound file name including the .wav extension
	char* seg = zstrcat("sound\\",(char*)soundName);
	char* finalStr = zstrcat(seg,".wav");



	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(finalStr);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound\\my_song.mp3", repeat);
}

void Utility::playMusic(const char* musicName, bool repeat)
{
	if(musicName == NULL)
	{
		return;
	}

	//concatenate the sound file name including the .mp3 extension
	char* seg = zstrcat("music\\",(char*)musicName);
	char* finalStr = zstrcat(seg,".mp3");

	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(finalStr);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(finalStr, repeat);
}

/*void Utility::playMusic(const char* musicName, bool repeat)
{
	if(musicName == NULL)
	{
		return;
	}

	//concatenate the sound file name including the .mp3 extension
	char* seg = zstrcat("music\\",(char*)musicName);
	char* finalStr = zstrcat(seg,".wav");

	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(finalStr);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(finalStr, repeat);
}*/

void Utility::stopMusic()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
}

TiXmlElement* Utility::getRootElementFromFile(const char* fileName)
{
	//need to new the TiXmlDocument here otherwise the doc strucure will be lost after exiting the callee
	TiXmlDocument* doc = new TiXmlDocument(fileName);
	assert(doc->LoadFile());
	TiXmlHandle hDoc(doc);
	TiXmlElement* pElem;
	pElem=hDoc.FirstChildElement().Element();
	assert(pElem != NULL);
	return pElem;
}

char* Utility::getCurrentTime()
{
	try
	{
		time_t now = time(0);

		// Convert now to tm struct for local timezone
		tm* localtm = localtime(&now);

		char* output = new char[30];
		strftime(output, 30, "%Y-%m-%d-%H:%M:%S %a", localtm);

		return output;

		//return asctime(localtm);
	}
	catch(...)
	{
		return "Save Point";
	}
}

char* Utility::getSaveString(char* title)
{
	char* timeString = Utility::getCurrentTime();
	if(title == NULL && timeString == NULL)
	{
		return "Place Holder";
	}

	if(title == NULL)
	{
		return timeString;
	}

	if(timeString == NULL)
	{
		return title;
	}


	char* temp = Utility::zstrcat(title, " - ");
	return Utility::zstrcat(temp, timeString);
}
void Utility::replaceTitleWithMainScene(ZSceneMgr* mgr)
{
	ZScene* titleScene = mgr->getTitleScene();
	ZScene* mainScene = mgr->getMainScene();

	replaceScene(titleScene, mainScene);
}

void Utility::replaceMainWithTitleScene(ZSceneMgr* mgr)
{
	ZScene* titleScene = mgr->getTitleScene();
	ZScene* mainScene = mgr->getMainScene();

	replaceScene(mainScene, titleScene);
}

void Utility::replaceScene(ZScene* originScene, ZScene* targetScene)
{

	//CCDirector::sharedDirector()->popScene();
	//CCDirector::sharedDirector()->pushScene(originScene->getScene());
	CCDirector::sharedDirector()->setDepthTest(true);
	//CCTransitionScene *transition = CCTransitionPageTurn::create(3.0f, mainScene->getScene(), true);
	
	CCTransitionScene *transition = CCTransitionRotoZoom::create(3.0f, targetScene->getScene()); 
	
	
	CCDirector::sharedDirector()->replaceScene(transition); 
	//CCDirector::sharedDirector()->startAnimation();
	//targetScene->getScene()->resumeSchedulerAndActions();
	
}

vector<ScriptElement*> Utility::createLines(TiXmlElement* lineElem, CCNode* parentLayer)
{
	assert(lineElem != NULL);
	vector<ScriptElement*> lines;
	for( ; lineElem != NULL; lineElem=lineElem->NextSiblingElement())
	{
		const char* tagName = lineElem->Value();
		if(strcmp(tagName, NeoConstants::SCRIPT_TAG_LINE) == 0)
		{
			char* line = (char*)lineElem->GetText();
			char* lineId = (char*)lineElem->Attribute(NeoConstants::SCRIPT_ATTR_ID);
			lines.push_back(new ValueWrapper(lineId, line));
		}
		else if(strcmp(tagName, NeoConstants::SCRIPT_TAG_OPTIONS) == 0)
		{
			ZMenu* menu = new ZMenu(lineElem, parentLayer);
			lines.push_back(menu);
		}
		else if(strcmp(tagName, NeoConstants::SCRIPT_TAG_AUTO_LINES) == 0)
		{
			ZAutoLines* autolines = new ZAutoLines(lineElem, parentLayer);
			lines.push_back(autolines);
		}

	}

	return lines;
}

void Utility::setColor(int colorCode, CCLabelTTF* label)
{
	//0 : WHITE
	//1 : BLUE
	//2 : YELLOW 
	//3 : MAGENTA
	//4 : ORANGE
	//5 : GREEN
	//6 : RED
	//7 : BLACK
	//8 : GRAY
	//default(0) : WHITE
	switch(colorCode)
	{
	case 1:
		{
			label->setColor(ccBLUE  );
			break;
		}
	case 2:
		{
			label->setColor(ccYELLOW  );
			break;
		}
	case 3:
		{
			label->setColor(ccMAGENTA  );
			break;
		}
	case 4:
		{
			label->setColor(ccORANGE  );
			break;
		}
	case 5:
		{
			label->setColor(ccGREEN  );
			break;
		}
	case 6:
		{
			label->setColor(ccRED  );
			break;
		}
	case 7:
		{
			label->setColor(ccBLACK  );
			break;
		}
	case 8:
		{
			label->setColor(ccGRAY  );
			break;
		}
	default:
		{
			return;
		}
	}
}

CCSize Utility::getDefaultScriptSize()
{
	return  CCSizeMake(NeoConstants::WIN_WIDTH, NeoConstants::WIN_HEIGHT);
}

Utility::~Utility(void)
{
}
