#pragma once
#include "menu\ZGameMenu.h"
#include "scene\ZMainScene.h"
#include "scene\ZSceneMgr.h"

class ObjectLayer;
class ZGameMenuContainer;
class ZMainMenu : public ZGameMenu
{
public:
	ZMainMenu(CCNode* parentNode, bool visible);
	virtual CCMenuItemFont* createMenuItemWithString(const char* strId, char* text, CCObject* target);
	virtual void init();
	void optionCallback(CCObject* sender);
	~ZMainMenu(void);
};

