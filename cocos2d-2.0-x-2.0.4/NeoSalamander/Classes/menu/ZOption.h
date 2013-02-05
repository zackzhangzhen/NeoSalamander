#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class ZOption : public CCObject
{
public:
	ZOption(int, int, CCMenu*, CCMenuItemFont* );
	~ZOption(void);

	int getId();
	int getScore();
	CCMenu* getParentMenu();
	CCMenuItemFont* getMenuItem();

private:
	int m_id;
	int m_score;
	CCMenu* m_parentMenu;
	CCMenuItemFont* m_menuItem;
};

