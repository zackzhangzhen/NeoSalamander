#include "ZMenu.h"
#include "layer\ScriptLayer.h"


ZMenu::ZMenu(TiXmlElement* optionsElem, CCNode* parentNode, bool visible) : ScriptElement(ScriptElementType::OPTIONS)
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

		const char* idStr = optionElem->Attribute("id");

		//score
		int score = 0;
		optionElem->Attribute("score", &score);

		//toScript
		const char* toScript = optionElem->Attribute("toScript");

		//sound
		const char* sound = optionElem->Attribute("sound");

		//isJump
		const char* jump = optionElem->Attribute("jump");
		bool isJump = jump == NULL? false:true;

		//text
		char* text = (char*)optionElem->GetText();

		//create menu item
		CCMenuItemFont* menuItem = CCMenuItemFont::itemWithString(text, this, menu_selector(ZMenu::optionCallback));  
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
		ZOption* option = new ZOption(id, idStr, score,toScript, sound, isJump, menu, menuItem);

		menuItem->setUserObject(option);

		//this->m_optionMap.insert(make_pair(id ,option));
	}

	//set position to center
	CCPoint centerPt = Utility::getCenterPt();
	menu->setPosition(centerPt);
	menu->alignItemsVertically();

	this->m_menu = menu;

	this->m_parentScriptLayer = (ScriptLayer*)parentNode;
	this->m_parentScriptLayer->addChild(this->m_menu, 11);
	this->m_menu->setVisible(false);

}

ScriptLayer* ZMenu::getParentScriptLayer()
{
	return m_parentScriptLayer;
}

void ZMenu::show()
{
	this->m_menu->setVisible(true);
	this->m_parentScriptLayer->setInOption(true);
}

void ZMenu::hide()
{
	this->m_menu->setVisible(false);
	this->m_parentScriptLayer->setInOption(false);
}

void ZMenu::optionCallback(CCObject* sender)
{
	CCMenuItemFont* item = (CCMenuItemFont*)sender;
	ZOption* option = (ZOption*)item->getUserObject();
	/*int id = item->getTag();
	map<int, ZOption*>::const_iterator iter = m_optionMap.find(id);
	assert(iter != m_optionMap.end());
	ZOption* option = iter->second;*/

	CCMenu* menu = option->getParentMenu();
	ZMenu* zMenu = (ZMenu*)menu->getUserObject();
	zMenu->hide();

	ScriptLayer* parLayer = zMenu->getParentScriptLayer();

	bool jump = option->isJump();
	char* nextScriptId = (char*)option->getToScript();
	if(jump)
	{		
		parLayer->setNextScriptPlayerSync(nextScriptId);
	}
	else
	{
		parLayer->setNextScriptPlayerAsync(nextScriptId);
	}

	//play the sound
	Utility::playSound(option->getSound());

	Courier::sendMail(option->getIdStr());
}

ZMenu::~ZMenu(void)
{
}
