#pragma once
#include "cocos2d.h"
#include "script\ScriptElement.h"
using namespace cocos2d;
class ZOption : public ScriptElement
{
public:
	ZOption(int, int, CCMenu*, CCMenuItemFont* );
	~ZOption(void);

	int getId();
	int getScore();
	CCMenu* getParentMenu();
	CCMenuItemFont* getMenuItem();
	char* getText();

private:
	int m_id;
	int m_score;
	CCMenu* m_parentMenu;
	CCMenuItemFont* m_menuItem;
};

