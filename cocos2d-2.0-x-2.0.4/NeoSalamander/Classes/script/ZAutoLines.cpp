#include "ZAutoLines.h"
#include "layer\ScriptLayer.h"
#include "script\ZLabelTTF.h"
#include "script\ScriptPlayer.h"
ZAutoLines::ZAutoLines(TiXmlElement* autolinesElem, CCNode* parentNode, ScriptPlayer* parentPlayer, bool visibl) : ScriptElement(ScriptElementType::AUTO_LINES)
{
	assert(parentNode != NULL);

	this->m_parentScriptPlayer = parentPlayer;

	TiXmlElement* autoScriptElem = autolinesElem->FirstChildElement();
	assert(autoScriptElem != NULL);

	//populate menu items and options 
	for( ; autoScriptElem != NULL; autoScriptElem=autoScriptElem->NextSiblingElement())
	{

		int size = ZLabelTTF::FONT_DEFAULT_SIZE;
		autoScriptElem->Attribute(NeoConstants::SCRIPT_ATTR_SIZE, &size);

		int colorCode = ZLabelTTF::FONT_COLOR_DEFAULT;
		autoScriptElem->Attribute(NeoConstants::SCRIPT_ATTR_COLOR, &colorCode);

		int preBlank = NeoConstants::PRE_BLANK_DEFAULT;
		autoScriptElem->Attribute(NeoConstants::PRE_BLANK, &preBlank);

		int fadeInTime = NeoConstants::FADE_IN_TIME_DEFAULT;
		autoScriptElem->Attribute(NeoConstants::FADE_IN_TIME, &fadeInTime);

		int presentTime = NeoConstants::PRESENT_TIME_DEFAULT;
		autoScriptElem->Attribute(NeoConstants::PRESENT_TIME, &presentTime);

		int fadeOutTime = NeoConstants::FADE_OUT_TIME_DEFAULT;
		autoScriptElem->Attribute(NeoConstants::FADE_OUT_TIME, &fadeOutTime);

		int postBlank = NeoConstants::POST_BLANK_DEFAULT;
		autoScriptElem->Attribute(NeoConstants::POST_BLANK, &postBlank);

		char* font = (char*)autoScriptElem->Attribute(NeoConstants::SCRIPT_ATTR_FONT);
		if(font == NULL)
		{
			font = ZLabelTTF::YAHEI;
		}

		//text
		char* text = (char*)autoScriptElem->GetText();

		this->m_parentScriptLayer = (ScriptLayer*)parentNode;

		CCLabelTTF* label = this->createLabel(text, font, colorCode, size);

		label->setUserData(new AutoScriptAttrHolder(preBlank, fadeInTime, presentTime, fadeOutTime, postBlank));
		
		this->m_labels.push_back(label);
	}	
}

CCLabelTTF* ZAutoLines::createLabel(char* text, char* font, int color, int size)
{
	CCLabelTTF* label = CCLabelTTF::create(text, font, size, Utility::getDefaultScriptSize(), kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);

	Utility::setColor(color, label);
	label->setOpacity(0);
	label->setVisible(true);

	//set position to center
	CCPoint centerPt = Utility::getCenterPt();
	label->setPosition(centerPt);
	this->m_parentScriptLayer->addChild(label, 11);

	return label;
}

void ZAutoLines::play()
{
	vector<CCLabelTTF*>::iterator iter = m_labels.begin();
	int size = m_labels.size();
	int i = 0;
	int base = 0;
	while(iter != m_labels.end())
	{
		CCLabelTTF* label = *iter;

		AutoScriptAttrHolder* attrHolder = (AutoScriptAttrHolder*)label->getUserData();

		int preBlank = attrHolder->getPreBlank();
		int fadeInTime = attrHolder->getFadeInTime();
		int presentTime = attrHolder->getPresentTime();
		int fadeOutTime = attrHolder->getFadeOutTime();
		int postBlank = attrHolder->getPostBlank();

		CCDelayTime *preBlankAction = CCDelayTime::actionWithDuration(base + preBlank);
		CCFadeIn* fadeInAction= CCFadeIn::actionWithDuration(fadeInTime);
		CCDelayTime *presentAction = CCDelayTime::actionWithDuration(presentTime);
		CCFadeOut* fadeOutAction= CCFadeOut::actionWithDuration(fadeOutTime);
		CCDelayTime *postBlankAction = CCDelayTime::actionWithDuration(postBlank);

		if(i == size - 1)
		{
			//The end --- :)
			if(fadeOutTime == 0)
			{
				label->runAction(CCSequence::actions(preBlankAction, fadeInAction, presentAction, NULL));
			}
			else
			{
				CCFiniteTimeAction* animationDone = CCCallFuncN::actionWithTarget(this,callfuncN_selector(ZAutoLines::setAnimationPlayingDone));
				label->runAction(CCSequence::actions(preBlankAction, fadeInAction, presentAction, fadeOutAction, postBlankAction, animationDone, NULL));
			}			
		}
		else
		{
			label->runAction(CCSequence::actions(preBlankAction, fadeInAction, presentAction, fadeOutAction, postBlankAction, NULL));
		}
		
		i++;
		base+= preBlank+fadeInTime+presentTime+fadeOutTime+postBlank;
		iter++;
	}
}

void ZAutoLines::setAnimationPlayingDone(CCNode* sender)
{
	//calling this will eventually set the current script id to the next
	this->m_parentScriptPlayer->play();

	//calling this will fade out the background of the current dlg
	this->m_parentScriptPlayer->bgFadeOut(false);


	{
		char* nextScriptId = m_parentScriptPlayer->getNextScriptPlayerId();
		if(nextScriptId != NULL)
		{
			ScriptPlayer* player = m_parentScriptLayer->findScriptPlayerByKey(nextScriptId);
			m_parentScriptLayer->setCurrentScriptPlayer(player);
		}		
	}

	//this->m_parentScriptLayer->ccTouchesEnded(NULL,NULL);
}

ZAutoLines::~ZAutoLines(void)
{
}
