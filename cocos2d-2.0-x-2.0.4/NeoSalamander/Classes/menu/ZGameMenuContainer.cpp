#include "ZGameMenuContainer.h"
#include "scene\ZSceneMgr.h"
#include "layer\ObjectLayer.h"
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

	m_optionMap.insert(make_pair(0 ,new ZMainMenu(objLayer, false)));
	m_optionMap.insert(make_pair(1 ,new ZLoadMenu(objLayer, false)));
}

ZGameMenuContainer::~ZGameMenuContainer(void)
{
}
