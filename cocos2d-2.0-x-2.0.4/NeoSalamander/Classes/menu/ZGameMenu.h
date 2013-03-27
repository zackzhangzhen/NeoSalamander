#pragma once



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

class ScriptLayer;
class ZGameMenu: public ScriptElement
{
public:
	ZGameMenu(CCNode* parentNode, bool visible = false);
	virtual void init() = 0;
	virtual CCMenuItemFont* createMenuItemWithString(const char* strId, char* text, CCObject* target);
	virtual void optionCallback(CCObject* sender) = 0;
	virtual void show();
	virtual void hide();
	CCLayer* getParentLayer();
	~ZGameMenu(void);

protected:

	TiXmlElement* m_optionsElem;
	bool m_visible;

	CCMenu* m_menu;
	CCLayer* m_parentLayer;
};

