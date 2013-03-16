#include "ZGameMenuContainer.h"
#include "scene\ZSceneMgr.h"
ZGameMenuContainer::ZGameMenuContainer(ZSceneMgr* sceneMgr)
{
	this->m_sceneMgr = sceneMgr;
	init();
}

ScriptLayer* ZGameMenuContainer::getScriptLayer()
{
	return m_sceneMgr->getScriptLayer();
}

ScriptPlayer* ZGameMenuContainer::getCurrentScriptPayer()
{
	ScriptPlayer* player = m_sceneMgr->getScriptLayer()->getCurrentScriptPlayer();
	assert(player != NULL);	
	return player;
}

char* ZGameMenuContainer::getCurrentScriptId()
{
	ScriptPlayer* player = getCurrentScriptPayer();
	return player->getId();
	
}

void ZGameMenuContainer::init()
{
	assert(m_sceneMgr != NULL);
	/**
		0 - Main Menu
		1 - Load Menu
	*/
	m_optionMap.insert(make_pair(0 ,new ZMainMenu(NULL, false)));
	m_optionMap.insert(make_pair(1 ,new ZLoadMenu(NULL, false)));
}

ZGameMenuContainer::~ZGameMenuContainer(void)
{
}
