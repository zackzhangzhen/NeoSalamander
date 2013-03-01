#include "ZOption.h"


ZOption::ZOption(int id, const char* idStr, int score, const char* toLineOrScript, const char* sound, bool isJumpL, bool isJumpS, CCMenu* menu, CCMenuItemFont* item )
{
	this->m_id = id;
	this->m_idStr = idStr;
	this->m_score = score;
	this->m_parentMenu = menu;
	this->m_menuItem = item;
	
	this->m_sound = sound;
	this->m_isJumpS = isJumpS;
	this->m_isJumpL = isJumpL;

	this->m_toScript = toLineOrScript;	
	this->m_toLine = toLineOrScript;
}


int ZOption::getId()
{
	return m_id;
}

const char* ZOption::getIdStr()
{
	return m_idStr;
}

const char* ZOption::getToLine()
{
	return m_toLine;
}

int ZOption::getScore()
{
	return m_score;
}

bool ZOption::isJumpS()
{
	return m_isJumpS;
}

bool ZOption::isJumpL()
{
	return m_isJumpL;
}

const char* ZOption::getToScript()
{
	return m_toScript;
}

const char* ZOption::getSound()
{
	return m_sound;
}

CCMenu* ZOption::getParentMenu()
{
	return m_parentMenu;
}

CCMenuItemFont* ZOption::getMenuItem()
{
	return m_menuItem;
}

ZOption::~ZOption(void)
{
}
