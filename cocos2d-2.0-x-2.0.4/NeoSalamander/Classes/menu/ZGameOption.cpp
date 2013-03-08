#include "ZGameOption.h"


ZGameOption::ZGameOption(int id, const char* idStr, int score, const char* toLine, const char* toScript, const char* sound, bool isJumpL, bool isJumpS, CCMenu* menu, CCMenuItemFont* item )
{
	this->m_id = id;
	this->m_idStr = idStr;
	this->m_score = score;
	this->m_parentMenu = menu;
	this->m_menuItem = item;
	
	this->m_sound = sound;
	this->m_isJumpS = isJumpS;
	this->m_isJumpL = isJumpL;

	this->m_toLine = toLine;
	this->m_toScript = toScript;		
}


int ZGameOption::getId()
{
	return m_id;
}

const char* ZGameOption::getIdStr()
{
	return m_idStr;
}

const char* ZGameOption::getSound()
{
	return m_sound;
}

CCMenu* ZGameOption::getParentMenu()
{
	return m_parentMenu;
}

CCMenuItemFont* ZGameOption::getMenuItem()
{
	return m_menuItem;
}

ZGameOption::~ZGameOption(void)
{
}
