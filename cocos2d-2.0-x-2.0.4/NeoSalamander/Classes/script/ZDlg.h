#pragma once
#include "sprite\ZSprite.h"
#include "cocos2d.h"
#include "NeoConstants.h"
class ZDlg
{
public:
	ZDlg(void);
	ZDlg(int pos, char* script, char* figureFileName, CCNode* parentNode = NULL, char* font = FONT_COMIC, int size = FONT_DEFAULT_SIZE);
	
	~ZDlg(void);

	void calcFrameSizes(void);
	void calcPos(void);
	void initFramePrototype();
	void initFrame();
	void init(void);
	void calcInitPos(void);
	void calcInitOpacity(void);

	void addToCCNode(CCNode* node, int baseOrder);

	void fadeIn(bool delay);
	void fadeOut();
	bool play(bool delay);

	static int POS_LEFT;
	static int POS_RIGHT;
	static int POS_FULL;

	static int FRAME_MARGIN;
	static int SCRIPT_MARGIN;
	static int FIGURE_MARGIN;
	static int FIGURE_OFFSET;

	static char* FONT_COMIC;
	static int FONT_DEFAULT_SIZE;

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
	void calcFigurePos(void);
	void calcScriptPos(void);
	CCSize getScriptSize();

	int m_pos;

	bool fadingIn;

	CCPoint m_frameInitPos;
	CCPoint m_figureInitPos;
	CCPoint m_scriptInitPos;

	CCPoint m_framePos;
	CCPoint m_figurePos;
	CCPoint m_scriptPos;

	char* m_script;
	CCLabelTTF* m_scriptLabel;
	ZSprite * m_figure;
	ZSprite  * m_frame;
};

