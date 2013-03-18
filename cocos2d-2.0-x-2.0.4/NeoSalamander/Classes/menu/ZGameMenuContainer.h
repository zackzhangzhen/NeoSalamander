#pragma once
#include <iostream>
#include "ZGameMenu.h"
using namespace std;
class ZSceneMgr;
class ObjectLayer;
class ZLoadMenu;
class ZMainMenu;
class ZGameMenuContainer
{
public:
	
	ZGameMenuContainer(ZSceneMgr* parentSceneMgr);
	static ZGameMenuContainer* getInstance();
	ZLoadMenu* getLoadMenu();
	ZMainMenu* getMainMenu();
	ScriptLayer* getScriptLayer();
	ScriptPlayer* getCurrentScriptPayer();
	char* getCurrentScriptId();
	
	~ZGameMenuContainer(void);

	

private:
	
	void init();

	ZSceneMgr* m_sceneMgr;
	map<int, ZGameMenu*> m_optionMap;
};

