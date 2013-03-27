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
	void initBg();
	void setAnimationPlayingDone(CCNode* sender);
	void switchCueOn(CCNode* sender);
	void switchCueOff(CCNode* sender);
	void fadeIn(bool delay);
	void bgFadeOut(bool delay, bool switchCueOn = true);
	void jumpToLine(char* lineId);
	bool play(bool delay = false);
	void refresh();
	void refreshChildrenDlg();
	void fadeOut(bool switchCueOn = true);
	char* getId();
	char* getTitle();
	char* getNextScriptPlayerId();
	void setNextScriptPlayerId(char* id);
	void resetNextScriptId();
	char* getOriginNextScriptPlayerId();
	void autoRelease(CCNode* sender);

private:
	vector<ZDlg*> m_vec;
	vector<ZDlg*>::const_iterator m_iter;
	char* m_id;
	char* m_title;
	char* m_nextScriptPlayerId;
	char* m_originNextScriptPlayerId;
	ZSprite* m_bg;
	ScriptLayer* m_parentScriptLayer;
	bool fadedIn;
	char* m_bgPic;
};


