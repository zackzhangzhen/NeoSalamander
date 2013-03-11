#pragma once
#include "cocos2d.h"
#include "layer\ScriptLayer.h"
#include "script\ScriptPlayer.h"
using namespace cocos2d;
class ZMenu;
class ZOption : public CCObject
{
public:
	ZOption(int id, const char* idStr, int score, const char* toLine, const char* toScript, const char* sound, bool isJumpL, bool isJumpS, CCMenu* menu, CCMenuItemFont* item );
	ZOption(int id, const char* idStr,const char* sound, CCMenu*  menu, CCMenuItemFont* menuItem);//for option in game menu

	~ZOption(void);

	int getId();
	const char* getIdStr();
	int getScore();
	bool isJumpS();
	bool isJumpL();
	const char* getSound();
	const char* getToScript();
	const char* getToLine();
	CCMenu* getParentMenu();
	ZMenu* getParentZMenu();
	CCMenuItemFont* getMenuItem();
	ScriptLayer* getParentScriptLayer();

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

