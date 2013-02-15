#pragma once

#include "sprite\ZSprite.h"
//#include "layer\ScriptLayer.h"
#include "cocos2d.h"
#include "NeoConstants.h"
#include "script\ZLabelTTF.h"
#include <vector>
#include "tinyxml.h"
#include "ValueWrapper.h"
#include "ScriptElement.h"
#include "menu\ZOption.h"
#include "menu\ZMenu.h"
//#include "layer\ScriptLayer.h"


class ScriptLayer;

enum ScriptState{
	NOT_FADED_IN,
	SCRIPT_ROLLING,
	SCRIPT_DONE
};

class ZDlg : public CCObject
{
public:
	ZDlg(void);
	ZDlg(TiXmlElement* dlgElem, CCNode* parentNode);
	//ZDlg(int pos, vector<ScriptElement*>& scripts, char* figureFileName, CCNode* parentNode, char* font = ZLabelTTF::FONT_COMIC, int size = ZLabelTTF::FONT_DEFAULT_SIZE);	
	
	~ZDlg(void);

	void ZDlgInit(int pos, vector<ScriptElement*>& scripts, char* figureFileName, char* musicName, bool isStopMusic, CCNode* parentNode, int colorCode, char* font, int size = ZLabelTTF::FONT_DEFAULT_SIZE, int figure_vertical_offset = NeoConstants::FIGURE_VERTICAL_OFFSET);
	void calcFrameSizes(void);
	void calcPos(int figure_vertical_offset = NeoConstants::FIGURE_VERTICAL_OFFSET);
	void initFramePrototype();
	void initFrame();
	void init(int figure_vertical_offset = NeoConstants::FIGURE_VERTICAL_OFFSET);
	void calcInitPos(void);
	void calcInitOpacity(void);

	void addToCCNode(CCNode* node, int baseOrder);

	void fadeIn(bool delay);
	void playMusic();
	void fadeOut();
	bool play(bool delay);
	ScriptLayer* getParentScriptLayer();
	void setAnimationPlayingDone(CCNode* sender);
	void autoRelease(CCNode* sender);
	char* getMusicName();
	bool isStopMusic();

	static int POS_LEFT;
	static int POS_RIGHT;
	static int POS_FULL;

	static int FRAME_MARGIN;
	static int SCRIPT_MARGIN;
	static int FIGURE_MARGIN;

	static ZSprite* FRAME_L;
	static ZSprite* FRAME_R;
	static ZSprite* FRAME_F;

	static char* FRAME_L_NAME;
	static char* FRAME_R_NAME;
	static char* FRAME_F_NAME;


	static CCSize FRAME_L_SIZE;
	static CCSize FRAME_R_SIZE;
	static CCSize FRAME_F_SIZE;
	


private:

	void calcFrame();
	void calcFramePos(void);
	void calcFigurePos(int figure_vertical_offset = NeoConstants::FIGURE_VERTICAL_OFFSET);
	void calcScriptPos(void);
	CCSize getScriptSize();

	int m_pos;

	CCPoint m_frameInitPos;
	CCPoint m_figureInitPos;
	CCPoint m_scriptInitPos;

	CCPoint m_framePos;
	CCPoint m_figurePos;
	CCPoint m_scriptPos;
	ZSprite* m_figure;
	ZSprite* m_frame;
	ZLabelTTF* m_scriptLabel;
	ScriptLayer* m_parentScriptLayer;
	ScriptState m_scriptState;
	char* m_musicName;
	bool m_stopMusic;
};



