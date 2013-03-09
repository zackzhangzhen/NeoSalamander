#pragma once
#include "ZGameMenu.h"
#include "cocos2d.h"
#include "script\ZLabelTTF.h"
#include <vector>
#include "menu\tinyxml.h"
class ZLoadMenu : public ZGameMenu
{
public:
	ZLoadMenu(TiXmlElement* optionsElem, CCNode* parentNode, bool visible);
	virtual CCMenuItemFont* createMenuItemWithString(char* text, CCObject* target);
	void optionCallback(CCObject* sender);
	~ZLoadMenu(void);
};

