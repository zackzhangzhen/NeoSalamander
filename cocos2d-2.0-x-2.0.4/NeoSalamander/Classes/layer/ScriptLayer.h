#pragma once
#include "cocos2d.h"
#include "script\ScriptPlayer.h"
#include "script\ZDlg.h"
#include <vector>
#include <map>

class ScriptLayer : public cocos2d::CCLayer
{
public:
	ScriptLayer(void);
	~ScriptLayer(void);

	void initScripts();
	void ccTouchesEnded(CCSet* touches, CCEvent* event);

private:
	ScriptPlayer* findScriptPlayerByKey(char* key);


	map<char*, ScriptPlayer*> m_map;

	ScriptPlayer* m_player;
};

