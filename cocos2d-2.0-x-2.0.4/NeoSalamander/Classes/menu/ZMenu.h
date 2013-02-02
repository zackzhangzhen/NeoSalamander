#pragma once


//#include "layer\ScriptLayer.h"
#include "cocos2d.h"
#include "script\ZLabelTTF.h"
#include <vector>
#include "tinyxml.h"
#include <map>
#include "ZOption.h"

class ScriptLayer;
class ZMenu: public CCObject
{
public:
	ZMenu(void);
	ZMenu(TiXmlElement* dlgElem, CCNode* parentNode);
	void optionCallback(CCObject* sender);
	~ZMenu(void);

private:
	CCMenu* m_menu;
	ScriptLayer* m_parentScriptLayer;
	std::map<int, ZOption*> m_optionMap;
};

