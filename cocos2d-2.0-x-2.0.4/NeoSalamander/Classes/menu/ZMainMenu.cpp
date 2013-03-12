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

			char* saveString = Utility::getSaveString(title);

			char* scriptId = scriptPlayer->getId();


			TiXmlElement* pElem = Utility::getRootElementFromFile(NeoConstants::SAVE_FILE_LOC);
			TiXmlElement * element = new TiXmlElement( NeoConstants::SAVE_NODE_TAG );
			element->SetAttribute(NeoConstants::SCRIPT_ATTR_ID, scriptId);
			TiXmlText * text = new TiXmlText( saveString );
			element->LinkEndChild(text);
			pElem->LinkEndChild(element);

			TiXmlDocument* doc = element->GetDocument();
			doc->SaveFile();

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
