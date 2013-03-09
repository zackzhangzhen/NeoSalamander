#pragma once
#include <iostream>
#include "ZGameMenu.h"
#include "layer\ScriptLayer.h"
#include "script\ScriptPlayer.h"
using namespace std;
class ZGameMenuContainer
{
public:
	

	static ZGameMenuContainer* getInstance();

	ScriptLayer* getScriptLayer();
	ScriptPlayer* getCurrentScriptPayer();
	char* getCurrentScriptId();

	~ZGameMenuContainer(void);

	

private:
	ZGameMenuContainer();
	void init(ScriptLayer* scriptLayer);

	ScriptLayer* m_scriptLayer;
	static ZGameMenuContainer* m_instance;
	map<int, ZGameMenu*> m_optionMap;
	bool m_initialized;
};

