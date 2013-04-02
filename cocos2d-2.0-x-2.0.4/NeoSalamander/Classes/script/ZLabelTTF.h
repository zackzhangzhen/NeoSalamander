#pragma once
#include "cocos2d.h"
#include "NeoConstants.h"
#include "sprite\ZSprite.h"
#include <vector>
#include "ScriptElement.h"
#include "ValueWrapper.h"
#include "menu\ZMenu.h"
class ZLabelTTF
{
public:
	ZLabelTTF(void);
	~ZLabelTTF(void);
	void init(vector<ScriptElement*>& scripts, CCSize scriptSize, int colorCode, char* font, int size);

	static char* FONT_COMIC;
	static char* YAHEI;
	static int FONT_DEFAULT_SIZE;
	static int MENU_FONT_DEFAULT_SIZE;
	static int FONT_COLOR_DEFAULT;
	static int FONT_COLOR_BLUE;

	ZLabelTTF(vector<ScriptElement*>& scripts, CCSize scriptSize, int colorCode, char* font = FONT_COMIC, int size = FONT_DEFAULT_SIZE);

	void setPosition(CCPoint pos);
	void setPositionX(int x);
	void setPositionY(int y);
	int getPositionX();
	int getPositionY();
	CCPoint getPosition();
	bool rollScript();
	void jumpToLine(char* lineId);
	CCLabelTTF* getLabel();
	void addToCCNode(CCNode* node, int zOrder);
	CCAction * runAction(CCAction* action);
	void setOpacity(int opacity);
	void setColor(int colorCode);

private:
	CCLabelTTF* m_label;
	vector<ScriptElement*> m_scripts;
	vector<ScriptElement*>::iterator m_iter;
	CCNode* m_parentNode;
};

