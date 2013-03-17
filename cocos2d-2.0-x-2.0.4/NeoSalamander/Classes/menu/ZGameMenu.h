#pragma once


#include "layer\ScriptLayer.h"
#include "cocos2d.h"
#include "script\ZLabelTTF.h"
#include <vector>
#include "menu\tinyxml.h"
#include <map>
#include "script\ScriptElement.h"
#include "menu\ZOption.h"
#include "SimpleAudioEngine.h" 
#include "mail\Courier.h"
#include "script\ScriptPlayer.h"
#include "cocos2d.h"
#include "script\ZLabelTTF.h"
#include <vector>
#include "menu\tinyxml.h"

class ZGameMenu: public ScriptElement
{
public:
	ZGameMenu(CCNode* parentNode, bool visible = false);
	virtual void init() = 0;
	virtual CCMenuItemFont* createMenuItemWithString(char* text, CCObject* target) = 0;
	virtual void optionCallback(CCObject* sender) = 0;
	void show();
	void hide();
	CCLayer* getParentLayer();
	~ZGameMenu(void);

protected:

	TiXmlElement* m_optionsElem;
	bool m_visible;

	CCMenu* m_menu;
	CCLayer* m_parentLayer;
};

