#pragma once

#include "scene\ZMainScene.h"
#include "scene\ZSceneMgr.h"
#include "menu\ZGameMenu.h"
class ObjectLayer;
class ZGameMenuContainer;
class ZBackMenu : public ZGameMenu
{
public:
	ZBackMenu(CCNode* parentNode, bool visible);
	virtual void optionCallback(CCObject* sender);
	virtual void init();
	CCPoint getPos();
	~ZBackMenu(void);

private:
	bool m_visible;
	static const int BACK_MENU_WIDTH = 50;
	static const int BACK_MENU_HEIGHT = 50;
};


