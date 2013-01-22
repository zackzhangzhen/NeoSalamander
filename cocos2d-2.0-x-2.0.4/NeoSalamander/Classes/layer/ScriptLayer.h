#pragma once
#include "cocos2d.h"
#include <vector>
#include <map>
#include "tinyxml.h"
#include "utility\CompareCString.h"

class ScriptPlayer;

class ScriptLayer : public cocos2d::CCLayer
{
public:
	ScriptLayer(void);
	~ScriptLayer(void);

	void initScripts();
	void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	bool isAnimationPlaying();
	void setAnimationPlaying(bool playing);
	void loadScript(const char* fileName);
private:
	ScriptPlayer* findScriptPlayerByKey(char* key);
	bool m_isAnimationPlaying;
	//need to specify a comparator here since the default one compares the address of the char* pointer...
	std::map<char*, ScriptPlayer*, CompareCString> m_map;

	ScriptPlayer* m_player;
};
