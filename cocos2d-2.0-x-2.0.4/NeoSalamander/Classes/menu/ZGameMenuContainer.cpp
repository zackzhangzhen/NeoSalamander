#include "ZGameMenuContainer.h"
#include "scene\ZSceneMgr.h"
#include "layer\ObjectLayer.h"
#include "menu\ZMainMenu.h"
#include "menu\ZLoadMenu.h"
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

	CCNode* objLayer = this->m_sceneMgr->getObjectLayer();

	m_optionMap.insert(make_pair(NeoConstants::MAIN_MENU_ID ,new ZMainMenu(objLayer, false)));
	m_optionMap.insert(make_pair(NeoConstants::LOAD_MENU_ID ,new ZLoadMenu(objLayer, false)));
}

ZLoadMenu* ZGameMenuContainer::getLoadMenu()
{
	map<int, ZGameMenu*>::const_iterator iter = m_optionMap.find(NeoConstants::LOAD_MENU_ID);
	return (ZLoadMenu*)iter->second;
}

ZMainMenu* ZGameMenuContainer::getMainMenu()
{
	map<int, ZGameMenu*>::const_iterator iter = m_optionMap.find(NeoConstants::MAIN_MENU_ID);
	return (ZMainMenu*)iter->second;
}

ZGameMenuContainer::~ZGameMenuContainer(void)
{
}
