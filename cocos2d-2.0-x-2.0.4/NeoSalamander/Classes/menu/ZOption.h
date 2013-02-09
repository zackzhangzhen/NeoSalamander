#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class ZOption : public CCObject
{
public:
	ZOption(int, int,const char* toScript, bool isJump, CCMenu*, CCMenuItemFont* );
	~ZOption(void);

	int getId();
	int getScore();
	bool isJump();
	const char* getToScript();
	CCMenu* getParentMenu();
	CCMenuItemFont* getMenuItem();
	

private:
	int m_id;
	int m_score;
	bool m_isJump;
	const char* m_toScript;
	CCMenu* m_parentMenu;
	CCMenuItemFont* m_menuItem;
};

