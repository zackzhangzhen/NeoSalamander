#pragma once
#include "script\ZDlg.h"
#include <vector>
#include "menu\tinyxml.h"
class ScriptLayer;

class ScriptPlayer: public CCObject
{
public:
	ScriptPlayer(char* id, vector<ZDlg*>& vec);
	ScriptPlayer(char* id, TiXmlElement* scriptElem, CCNode* parentNode);
	~ScriptPlayer(void);
	void initBg(TiXmlElement* scriptElem, CCNode* parentNode);
	void setAnimationPlayingDone(CCNode* sender);
	void switchCueOn(CCNode* sender);
	void switchCueOff(CCNode* sender);
	void fadeIn(bool delay);
	void fadeOut(bool delay);
	bool play();
	void fadeOut();
	char* getId();
	char* getNextScriptPlayerId();
	void setNextScriptPlayerId(char* id);
	void autoRelease(CCNode* sender);

private:
	vector<ZDlg*> m_vec;
	vector<ZDlg*>::const_iterator m_iter;
	char* m_id;
	char* m_nextScriptPlayerId;
	ZSprite* m_bg;
	ScriptLayer* m_parentScriptLayer;
	bool fadedIn;
};


