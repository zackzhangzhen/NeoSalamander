#pragma once
#include "cocos2d.h"
#include "menu\tinyxml.h"
#include <vector>
#include "script\ScriptElement.h"


using namespace cocos2d;

class ScriptLayer;
class ZLabelTTF;
class ZAutoLines: public ScriptElement
{
public:
	ZAutoLines(TiXmlElement* dlgElem, CCNode* parentNode, bool visible = false);
	~ZAutoLines(void);

private:
	ScriptLayer* m_parentScriptLayer;
	ZLabelTTF* m_scriptLabel;
	CCLabelTTF* m_label;
};

