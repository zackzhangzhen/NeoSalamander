#pragma once
#include <vector>
#include "cocos2d.h"
#include "menu\tinyxml.h"
#include "script\AutoScriptAttrHolder.h"
#include "script\ScriptElement.h"

using namespace std;
using namespace cocos2d;
class ScriptPlayer;
class ScriptLayer;
class ZAutoLines: public ScriptElement
{
public:
	ZAutoLines(TiXmlElement* dlgElem, CCNode* parentNode, ScriptPlayer* parentPlayer, bool visible = false);
	void play();
	void setAnimationPlayingDone(CCNode* sender);
	CCLabelTTF* createLabel(char* text, char* font,int color, int size);
	~ZAutoLines(void);


private:
	ScriptLayer* m_parentScriptLayer;
	vector<CCLabelTTF*> m_labels;
	ScriptPlayer* m_parentScriptPlayer;
};

