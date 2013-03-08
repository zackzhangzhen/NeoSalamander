#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class ZGameOption : public CCObject
{
public:
	ZGameOption::ZGameOption(int id, const char* idStr, int score, const char* toLine, const char* toScript, const char* sound, bool isJumpL, bool isJumpS, CCMenu* menu, CCMenuItemFont* item );
	
	~ZGameOption(void);

	int getId();
	const char* getIdStr();
	const char* getSound();
	CCMenu* getParentMenu();
	CCMenuItemFont* getMenuItem();
	

private:
	int m_id;
	const char* m_idStr;
	int m_score;
	bool m_isJumpS;
	bool m_isJumpL;
	const char* m_toScript;
	const char* m_toLine;
	const char* m_sound;
	CCMenu* m_parentMenu;
	CCMenuItemFont* m_menuItem;
};

