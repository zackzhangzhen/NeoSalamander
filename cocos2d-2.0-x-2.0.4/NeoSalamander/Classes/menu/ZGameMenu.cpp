#include "ZGameMenu.h"
#include "layer\ScriptLayer.h"


ZGameMenu::ZGameMenu(TiXmlElement* optionsElem, CCNode* parentNode, bool visible) : ScriptElement(ScriptElementType::OPTIONS)
{
	assert(parentNode != NULL);

	this->m_optionsElem = optionsElem;
	this->m_parentScriptLayer = (ScriptLayer*)parentNode;
	this->m_visible = visible;
}

//use this method instead of doing it in constructor because we want to use polymorphism in here
void ZGameMenu::init()
{
	

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
		CCMenuItemFont* menuItem = createMenuItemWithString(text, this);
		 
		menuItem->setTag(id);

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
		

		option = new ZOption(id, idStr, sound, menu, menuItem);
		
		menuItem->setUserObject(option);

		//this->m_optionMap.insert(make_pair(id ,option));
	}

	//set position to center
	CCPoint centerPt = Utility::getCenterPt();
	menu->setPosition(centerPt);
	menu->alignItemsVertically();

	this->m_menu = menu;

	this->m_parentScriptLayer->addChild(this->m_menu, 11);
	this->m_menu->setVisible(false);
}


ScriptLayer* ZGameMenu::getParentScriptLayer()
{
	return m_parentScriptLayer;
}

void ZGameMenu::show()
{
	this->m_menu->setVisible(true);
	this->m_parentScriptLayer->setInOption(true);
}

void ZGameMenu::hide()
{
	this->m_menu->setVisible(false);
	this->m_parentScriptLayer->setInOption(false);
}


ZGameMenu::~ZGameMenu(void)
{
}
