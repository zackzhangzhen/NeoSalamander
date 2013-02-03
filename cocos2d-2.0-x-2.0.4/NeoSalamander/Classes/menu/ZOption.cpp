#include "ZOption.h"


ZOption::ZOption(int id, int score, CCMenu* menu, CCMenuItemFont* item ) : ScriptElement(ScriptElementType::OPTIONS)
{
	this->m_id = id;
	this->m_score = score;
	this->m_parentMenu = menu;
	this->m_menuItem = item;
}

int ZOption::getId()
{
	return m_id;
}

char* ZOption::getText()
{
	return "";
}

int ZOption::getScore()
{
	return m_score;
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
