#pragma once
#include <iostream>
#include "ZGameMenu.h"
#include "ZMainMenu.h"
#include "ZLoadMenu.h"
using namespace std;
class ZSceneMgr;
class ZGameMenuContainer
{
public:
	
	ZGameMenuContainer(ZSceneMgr* parentSceneMgr);
	static ZGameMenuContainer* getInstance();

	ScriptLayer* getScriptLayer();
	ScriptPlayer* getCurrentScriptPayer();
	char* getCurrentScriptId();

	~ZGameMenuContainer(void);

	

private:
	
	void init();

	ZSceneMgr* m_sceneMgr;
	map<int, ZGameMenu*> m_optionMap;
};

