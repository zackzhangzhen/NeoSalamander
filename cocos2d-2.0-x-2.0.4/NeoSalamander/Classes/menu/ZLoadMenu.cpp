#include "ZLoadMenu.h"


ZLoadMenu::ZLoadMenu(TiXmlElement* optionsElem, CCNode* parentNode, bool visible) : ZGameMenu(optionsElem, parentNode, visible)
{
}

CCMenuItemFont* ZLoadMenu::createMenuItemWithString(char* text, CCObject* target)
{
	CCMenuItemFont* menuItem = CCMenuItemFont::itemWithString(text, this, menu_selector(ZLoadMenu::optionCallback)); 
	return menuItem;
}

void ZLoadMenu::optionCallback(CCObject* sender)
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

ZLoadMenu::~ZLoadMenu(void)
{
}
