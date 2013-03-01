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
		const char* toScript = optionElem->Attribute(NeoConstants::SCRIPT_ATTR_TO_SCRIPT);

		//toLine
		const char* toLine = optionElem->Attribute("toLine");

		//sound
		const char* sound = optionElem->Attribute("sound");

		//isJumpL
		const char* jumpL = optionElem->Attribute("jumpL");
		bool isJumpL = jumpL == NULL? false:true;

		//isJumpS
		const char* jumpS = optionElem->Attribute("jumpS");
		bool isJumpS = jumpS == NULL? false:true;

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
		ZOption* option = NULL;
		
		if(isJumpL)
		{
			option = new ZOption(id, idStr, score,toLine, sound, isJumpL, isJumpS, menu, menuItem);
		}
		else
		{
			option = new ZOption(id, idStr, score,toScript, sound, isJumpL, isJumpS, menu, menuItem);
		}
		
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

	bool jumpL = option->isJumpL();
	bool jumpS = option->isJumpS();

	char* nextScriptId = (char*)option->getToScript();
	if(jumpS)
	{
		parLayer->setNextScriptPlayerSync(nextScriptId);
	}
	else if(jumpL)
	{
		char* nextLineId = (char*)option->getToLine();
		parLayer->jumpToLine(nextLineId);
	}
	else if(nextScriptId != NULL)
	{
		parLayer->setNextScriptPlayerAsync(nextScriptId);
	}

	//play the sound
	Utility::playSound(option->getSound());

	//Courier::sendMail(option->getIdStr());
}

ZMenu::~ZMenu(void)
{
}
