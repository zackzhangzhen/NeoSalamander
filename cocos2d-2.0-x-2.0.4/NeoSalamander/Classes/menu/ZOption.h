#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class ZOption : public CCObject
{
public:
	ZOption(int, const char* idStr, int,const char* toScript, const char* sound, bool isJump, CCMenu*, CCMenuItemFont* );
	~ZOption(void);

	int getId();
	const char* getIdStr();
	int getScore();
	bool isJump();
	const char* getSound();
	const char* getToScript();
	CCMenu* getParentMenu();
	CCMenuItemFont* getMenuItem();
	

private:
	int m_id;
	const char* m_idStr;
	int m_score;
	bool m_isJump;
	const char* m_toScript;
	const char* m_sound;
	CCMenu* m_parentMenu;
	CCMenuItemFont* m_menuItem;
};

