#pragma once
#include "ZGameMenu.h"
class ZMainMenu : public ZGameMenu
{
public:
	ZMainMenu(CCNode* parentNode, bool visible);
	virtual CCMenuItemFont* createMenuItemWithString(char* text, CCObject* target);
	virtual void init();
	void optionCallback(CCObject* sender);
	~ZMainMenu(void);
};

