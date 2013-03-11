#include "ZMainMenu.h"


ZMainMenu::ZMainMenu(TiXmlElement* optionsElem, CCNode* parentNode, bool visible) : ZGameMenu(optionsElem, parentNode, visible)
{
}

CCMenuItemFont* ZMainMenu::createMenuItemWithString(char* text, CCObject* target)
{
	CCMenuItemFont* menuItem = CCMenuItemFont::itemWithString(text, this, menu_selector(ZMainMenu::optionCallback)); 
	return menuItem;
}

void ZMainMenu::optionCallback(CCObject* sender)
{
	CCMenuItemFont* item = (CCMenuItemFont*)sender;
	ZOption* option = (ZOption*)item->getUserObject();
	int id = option->getId();
	switch(id)
	{
	case 0:
		{
			//new game
			break;
		}

	case 1:
		{
			//load game
			break;
		}

	case 2:
		{
			//save game
			ZMenu* menu = option->getParentZMenu();
			ScriptLayer* scriptLayer = menu->getParentScriptLayer();
			ScriptPlayer* scriptPlayer = scriptLayer->getCurrentScriptPlayer();
			char* title = scriptPlayer->getTitle();

			break;
		}
	}
	
	//Hide main menu and show the sub menu
	CCMenu* menu = option->getParentMenu();
	ZGameMenu* zMenu = (ZGameMenu*)menu->getUserObject();
	zMenu->hide();


	//play the sound
	Utility::playSound(option->getSound());
}

ZMainMenu::~ZMainMenu(void)
{
}
