#include "ZLoadMenu.h"


ZLoadMenu::ZLoadMenu( CCNode* parentNode, bool visible) : ZGameMenu(parentNode, visible)
{
}

void ZLoadMenu::init()
{

	TiXmlElement* pElem = Utility::getRootElementFromFile(NeoConstants::SAVE_FILE_LOC);

	TiXmlElement* saveElem = pElem->FirstChildElement();

	CCMenu* menu = this->addBackMenu();

	//populate menu items and options 
	for( ; saveElem != NULL; saveElem=saveElem->NextSiblingElement())
	{
		//id		

		const char* idStr = saveElem->Attribute(NeoConstants::SCRIPT_ATTR_ID);

		//text
		char* text = (char*)saveElem->GetText();

		//sound
		const char* sound = saveElem->Attribute(NeoConstants::SCRIPT_ATTR_SOUND);

		//use virtual function to create menu item
		CCMenuItemFont* menuItem = createMenuItemWithString(text, this);

		if(menu == NULL)
		{
			menu = CCMenu::menuWithItem(menuItem);
			menu->setUserObject(this);
		}
		else
		{
			menu->addChild(menuItem);
		}

		//create ZOption
		ZOption* option = NULL;
		

		option = new ZOption(0, idStr, sound, menu, menuItem);
		
		menuItem->setUserObject(option);

		//this->m_optionMap.insert(make_pair(id ,option));
	}

	//set position to center
	CCPoint centerPt = Utility::getCenterPt();
	menu->setPosition(centerPt);
	menu->alignItemsVertically();

	this->m_menu = menu;

	this->m_parentLayer->addChild(this->m_menu, 11);
	this->m_menu->setVisible(this->m_visible);
}

CCMenuItemFont* ZLoadMenu::createMenuItemWithString(char* text, CCObject* target)
{
	CCMenuItemFont* menuItem = CCMenuItemFont::itemWithString(text, this, menu_selector(ZLoadMenu::optionCallback)); 
	return menuItem;
}

CCMenu* ZLoadMenu::addBackMenu()
{
	CCMenu* menu;
	CCMenuItemFont* menuItem = CCMenuItemFont::itemWithString("Back", this, menu_selector(ZLoadMenu::optionBackCallback)); 
	
	menu = CCMenu::menuWithItem(menuItem);
	menu->setUserObject(this);
	
	return menu;
}

void ZLoadMenu::optionCallback(CCObject* sender)
{
	CCMenuItemFont* item = (CCMenuItemFont*)sender;
	ZOption* option = (ZOption*)item->getUserObject();
	int id = option->getId();
	
	
	//Hide main menu and show the sub menu
	CCMenu* menu = option->getParentMenu();
	ZGameMenu* zMenu = (ZGameMenu*)menu->getUserObject();
	zMenu->hide();


	//play the sound
	Utility::playSound(option->getSound());
}

void ZLoadMenu::optionBackCallback(CCObject* sender)
{
	CCMenuItemFont* item = (CCMenuItemFont*)sender;
	ZOption* option = (ZOption*)item->getUserObject();
	int id = option->getId();
	
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
