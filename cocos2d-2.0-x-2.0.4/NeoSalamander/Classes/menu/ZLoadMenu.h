#pragma once
#include "menu\ZGameMenu.h"
#include "cocos2d.h"
#include "script\ZLabelTTF.h"
#include <vector>
#include "menu\tinyxml.h"
#include "layer\ObjectLayer.h"
class ZLoadMenu : public ZGameMenu
{
public:
	ZLoadMenu(CCNode* parentNode, bool visible);
	CCMenu* addBackMenu();
	void init();
	void show();
	//virtual void hide();
	CCMenuItemFont* createMenuItemWithString(const char* idStr, char* text, CCObject* target);
	void optionCallback(CCObject* sender);
	void optionBackCallback(CCObject* sender);
	~ZLoadMenu(void);
};

