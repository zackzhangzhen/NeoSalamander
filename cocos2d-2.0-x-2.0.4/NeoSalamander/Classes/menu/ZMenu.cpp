#include "ZMenu.h"
#include "layer\ScriptLayer.h"

ZMenu::ZMenu(void)
{
	this->m_menu = NULL;
}

ZMenu::ZMenu(TiXmlElement* optionsElem, CCNode* parentNode)
{
	assert(parentNode != NULL);

	TiXmlElement* optionElem = optionsElem->FirstChildElement();
	assert(optionElem != NULL);

	CCMenu* menu = NULL;

	//populate menu items and options 
	for( ; optionElem != NULL; optionElem=optionElem->NextSiblingElement())
	{
		//id
		int id = 0;
		optionElem->Attribute("id", &id);

		//score
		int score = 0;
		optionElem->Attribute("score", &score);

		//text
		char* text = (char*)optionElem->GetText();

		//create menu item
		CCMenuItemFont* menuItem = CCMenuItemFont::itemWithString(text, this, menu_selector(ZMenu::optionCallback));  
		menuItem->setTag(id);

		if(menu == NULL)
		{
			menu = CCMenu::menuWithItem(menuItem);
		}
		else
		{
			menu->addChild(menuItem);
		}

		//create ZOption
		ZOption* option = new ZOption(id, score, menu, menuItem);
		this->m_optionMap.insert(make_pair(id ,option));
	}

	//set position to center
	CCPoint centerPt = Utility::getCenterPt();
	menu->setPosition(centerPt);

	this->m_menu = menu;

	this->m_parentScriptLayer = (ScriptLayer*)parentNode;
	this->m_parentScriptLayer->addChild(this->m_menu, 11);

}

void ZMenu::optionCallback(CCObject* sender)
{

}

ZMenu::~ZMenu(void)
{
}
