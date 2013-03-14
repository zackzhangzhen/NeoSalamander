#include "ZGameMenuContainer.h"
#include "ZMainMenu.h"
#include "ZLoadMenu.h"

ZGameMenuContainer* ZGameMenuContainer::m_instance;

ZGameMenuContainer::ZGameMenuContainer()
{
}

ScriptLayer* ZGameMenuContainer::getScriptLayer()
{
	return m_scriptLayer;
}

ScriptPlayer* ZGameMenuContainer::getCurrentScriptPayer()
{
	ScriptPlayer* player = m_scriptLayer->getCurrentScriptPlayer();
	assert(player != NULL);	
	return player;
}

char* ZGameMenuContainer::getCurrentScriptId()
{
	ScriptPlayer* player = getCurrentScriptPayer();
	return player->getId();
	
}

ZGameMenuContainer* ZGameMenuContainer::getInstance()
{
	if(m_instance == 0)
	{
		m_instance  = new ZGameMenuContainer();
	}

	return m_instance;
}

void ZGameMenuContainer::init(ScriptLayer* scriptLayer)
{
	assert(scriptLayer != NULL);
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
