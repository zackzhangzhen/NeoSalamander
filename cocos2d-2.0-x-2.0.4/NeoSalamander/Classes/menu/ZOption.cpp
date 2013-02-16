#include "ZOption.h"


ZOption::ZOption(int id, const char* idStr, int score, const char* toScript, const char* sound, bool isJump, CCMenu* menu, CCMenuItemFont* item )
{
	this->m_id = id;
	this->m_idStr = idStr;
	this->m_score = score;
	this->m_parentMenu = menu;
	this->m_menuItem = item;
	this->m_toScript = toScript;
	this->m_sound = sound;
	this->m_isJump = isJump;
}

int ZOption::getId()
{
	return m_id;
}

const char* ZOption::getIdStr()
{
	return m_idStr;
}

int ZOption::getScore()
{
	return m_score;
}

bool ZOption::isJump()
{
	return m_isJump;
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
