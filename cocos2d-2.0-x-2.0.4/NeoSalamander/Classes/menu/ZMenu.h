#pragma once


//#include "layer\ScriptLayer.h"
#include "cocos2d.h"
#include "script\ZLabelTTF.h"
#include <vector>
#include "menu\tinyxml.h"
#include <map>
#include "script\ScriptElement.h"
#include "menu\ZOption.h"
#include "SimpleAudioEngine.h" 
#include "mail\Courier.h"

class ScriptLayer;
class ZMenu: public ScriptElement
{
public:
	ZMenu(TiXmlElement* dlgElem, CCNode* parentNode, bool visible = false);
	void optionCallback(CCObject* sender);
	void show();
	void hide();
	ScriptLayer* getParentScriptLayer();
	~ZMenu(void);

private:
	CCMenu* m_menu;
	ScriptLayer* m_parentScriptLayer;
	//std::map<int, ZOption*> m_optionMap;
};

