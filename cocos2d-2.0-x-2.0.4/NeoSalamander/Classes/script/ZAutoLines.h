#pragma once
#include <vector>
#include "cocos2d.h"
#include "menu\tinyxml.h"

#include "script\ScriptElement.h"

using namespace std;
using namespace cocos2d;

class ScriptLayer;
class ZAutoLines: public ScriptElement
{
public:
	ZAutoLines(TiXmlElement* dlgElem, CCNode* parentNode, bool visible = false);
	void play();
	CCLabelTTF* createLabel(char* text, char* font, int size);
	~ZAutoLines(void);


private:
	ScriptLayer* m_parentScriptLayer;
	vector<CCLabelTTF*> m_labels;
};

