#include "ZMainMenu.h"
#include "layer\ObjectLayer.h"
#include "menu\ZGameMenuContainer.h"
ZMainMenu::ZMainMenu(CCNode* parentNode, bool visible) : ZGameMenu(parentNode, visible)
{
	init();
}

CCMenuItemFont* ZMainMenu::createMenuItemWithString(const char* strId, char* text, CCObject* target)
{
	CCMenuItemFont* menuItem = CCMenuItemFont::itemWithString(text, this, menu_selector(ZMainMenu::optionCallback)); 
	return menuItem;
}



void ZMainMenu::init()
{
	TiXmlElement* pElem = Utility::getRootElementFromFile(NeoConstants::MAIN_MENU_FILE_LOC);
	this->m_optionsElem = pElem->FirstChildElement();

	TiXmlElement* optionElem = m_optionsElem->FirstChildElement();
	assert(optionElem != NULL);

	CCMenu* menu = NULL;

	//populate menu items and options 
	for( ; optionElem != NULL; optionElem=optionElem->NextSiblingElement())
	{
		//id
		int id = 0;
		optionElem->Attribute("id", &id);

		const char* idStr = optionElem->Attribute("id");

		//text
		char* text = (char*)optionElem->GetText();

		//sound
		const char* sound = optionElem->Attribute("sound");

		//use virtual function to create menu item
		CCMenuItemFont* menuItem = createMenuItemWithString(NULL,text, this);
		 
		menuItem->setTag(id);
		menuItem->setFontName("SimHei");
		Utility::setColor(NeoConstants::GAME_MENU_DEFAULT_COLOR,menuItem);

		if(menu == NULL)
		{
			menu = CCMenu::menuWithItem(menuItem);
			
		}
		else
		{
			menu->addChild(menuItem);
		}
		menu->setUserObject(this);
		//create ZOption
		ZOption* option = NULL;
		

		option = new ZOption(id, idStr, sound, menu, menuItem);
		
		menuItem->setUserObject(option);

		//this->m_optionMap.insert(make_pair(id ,option));
	}

	//set position to center
	CCPoint centerPt = Utility::getMenuCenterPt();
	menu->setPosition(centerPt);
	menu->alignItemsVertically();

	this->m_menu = menu;

	this->m_parentLayer->addChild(this->m_menu, 11);
	this->m_menu->setVisible(this->m_visible);
}


void ZMainMenu::optionCallback(CCObject* sender)
{
	CCMenuItemFont* item = (CCMenuItemFont*)sender;
	ZOption* option = (ZOption*)item->getUserObject();
	int id = option->getId();

	const char* sound = option->getSound();
	Utility::playSound(sound);

	switch(id)
	{
	case 1:
		{
			//new game
			CCLayer* layer = this->m_parentLayer;
			ZScene* titleScene = ((ObjectLayer*)layer)->getParentTitleScene();
			ZSceneMgr* sceneMgr = titleScene->getSceneMgr();
			//reset the script to play the first one
			sceneMgr->refreshMainScene((char*)NeoConstants::STARTING_SCRIPT_ID);
			Utility::replaceTitleWithMainScene(sceneMgr);
			break;
		}

	case 2:
		{
			//load game
			CCLayer* layer = this->m_parentLayer;
			ZTitleScene* titleScene = ((ObjectLayer*)layer)->getParentTitleScene();
			titleScene->switchMainLoadMenu(false);

			break;
		}

	case 3:
		{
			//save game
			CCLayer* layer = this->m_parentLayer;
			ZTitleScene* titleScene = ((ObjectLayer*)layer)->getParentTitleScene();
			ZSceneMgr* sceneMgr = titleScene->getSceneMgr();
			ScriptLayer* scriptLayer = sceneMgr->getScriptLayer();
			ScriptPlayer* scriptPlayer = scriptLayer->getCurrentScriptPlayer();
			char* title = scriptPlayer->getTitle();

			char* saveString = Utility::getSaveString(title);

			char* scriptId = scriptPlayer->getId();


			TiXmlElement* pElem = Utility::getRootElementFromFile(NeoConstants::SAVE_FILE_LOC);
			TiXmlElement * element = new TiXmlElement( NeoConstants::SAVE_NODE_TAG );
			element->SetAttribute(NeoConstants::SCRIPT_ATTR_ID, scriptId);
			element->SetAttribute(NeoConstants::SCRIPT_ATTR_SOUND, NeoConstants::SCRIPT_ATTR_SOUND_OPTION_CORRECT);
			TiXmlText * text = new TiXmlText( saveString );
			element->LinkEndChild(text);
			pElem->LinkEndChild(element);

			TiXmlDocument* doc = element->GetDocument();
			doc->SaveFile();

			ZGameMenuContainer* menuContainer = titleScene->getMenuContainer();
			menuContainer->reloadLoadMenu();

			((ZTitleScene*)titleScene)->switchMainLoadMenu(true);

			break;
		}
	}

	//play the sound
	Utility::playSound(option->getSound());
}

ZMainMenu::~ZMainMenu(void)
{
}
