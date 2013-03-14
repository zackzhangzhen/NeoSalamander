#pragma once
#include "ZGameMenu.h"
#include "cocos2d.h"
#include "script\ZLabelTTF.h"
#include <vector>
#include "menu\tinyxml.h"
class ZLoadMenu : public ZGameMenu
{
public:
	ZLoadMenu(CCNode* parentNode, bool visible);
	CCMenu* addBackMenu();
	virtual void init();
	virtual CCMenuItemFont* createMenuItemWithString(char* text, CCObject* target);
	void optionCallback(CCObject* sender);
	void optionBackCallback(CCObject* sender);
	~ZLoadMenu(void);
};

