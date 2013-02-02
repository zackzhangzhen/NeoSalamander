#include "ZMenu.h"
#include "layer\ScriptLayer.h"

ZMenu::ZMenu(void)
{
	this->m_menu = NULL;
}

ZMenu::ZMenu(TiXmlElement* optionsElem, CCNode* parentNode)
{
	TiXmlElement* optionElem = optionsElem->FirstChildElement();
	assert(optionElem != NULL);

	CCMenu* menu = NULL;

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
}

void ZMenu::optionCallback(CCObject* sender)
{

}

ZMenu::~ZMenu(void)
{
}
