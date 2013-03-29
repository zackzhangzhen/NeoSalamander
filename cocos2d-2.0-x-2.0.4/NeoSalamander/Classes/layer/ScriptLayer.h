#pragma once
#include "cocos2d.h"
#include <vector>
#include <map>
#include "menu\tinyxml.h"
#include "utility\CompareCString.h"
#include "sprite\ZSprite.h"

class ScriptPlayer;
class ZMenu;
class ZMainScene;
class ZBackMenu;
class ScriptLayer : public cocos2d::CCLayer
{
public:
	ScriptLayer(ZMainScene* parentScene);
	~ScriptLayer(void);

	//void initScripts();
	ZMainScene* getParentMainScene();
	void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	void fadeOutCurrentScript();
	void fadeOutCurrentScriptInstantly();
	bool isAnimationPlaying();	
	void jumpToLine(char* lineId);
	void setAnimationPlaying(bool playing);
	bool isInOption();
	void setInOption(bool inOption);
	void loadScript(const char* fileName);
	void initCueSprite();
	void switchCue(bool on);
	void play();
	void menuCallback(CCObject* sender);
	void refresh(char* strId);
	void resetCurrentScriptPlayer(char* strId);
	void setCurrentScriptPlayer(ScriptPlayer* player);
	void setNextScriptPlayerAsync(char* id);
	void setNextScriptPlayerSync(char* id);
	void switchBackMenu(bool on);
	ScriptPlayer* getCurrentScriptPlayer();
	ScriptPlayer* findScriptPlayerByKey(char* key);
private:
	
	bool m_isAnimationPlaying;
	bool m_isInOption;
	//need to specify a comparator here since the default one compares the address of the char* pointer...
	std::map<char*, ScriptPlayer*, CompareCString> m_map;

	ZSprite* m_cue;

	ScriptPlayer* m_player;
	ZMainScene* m_parentScene;
	ZBackMenu* m_backMenu;
};
