#pragma once
#include "cocos2d.h"
#include "NeoConstants.h"
#include "sprite\ZSprite.h"
#include <vector>
class ZLabelTTF
{
public:
	ZLabelTTF(void);
	~ZLabelTTF(void);
	void init(vector<char*> scripts, CCSize scriptSize, char* font, int size);

	static char* FONT_COMIC;
	static char* YAHEI;
	static int FONT_DEFAULT_SIZE;

	ZLabelTTF(vector<char*>& scripts, CCSize scriptSize, char* font = FONT_COMIC, int size = FONT_DEFAULT_SIZE);
	ZLabelTTF(char* script, CCSize scriptSize, char* font = FONT_COMIC, int size = FONT_DEFAULT_SIZE);

	void setPosition(CCPoint pos);
	void setPositionX(int x);
	void setPositionY(int y);
	int getPositionX();
	int getPositionY();
	CCPoint getPosition();
	bool rollScript();
	CCLabelTTF* getLabel();
	void addToCCNode(CCNode* node, int zOrder);
	CCAction * runAction(CCAction* action);
	void setOpacity(int opacity);
private:
	CCLabelTTF* m_label;
	vector<char*> m_scripts;
	vector<char*>::iterator m_iter;
	CCNode* m_parentNode;
};

