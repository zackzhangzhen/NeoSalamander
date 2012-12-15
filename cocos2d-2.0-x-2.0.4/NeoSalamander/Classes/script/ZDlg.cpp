#include "ZDlg.h"

int ZDlg::POS_LEFT = 0;
int ZDlg::POS_RIGHT = 1;
int ZDlg::POS_FULL = 2;

int ZDlg::FRAME_MARGIN = 6;
int ZDlg::SCRIPT_MARGIN = 6;
int ZDlg::FIGURE_MARGIN = 10;

char* ZDlg::FONT_ARIAL = "Arial";
int ZDlg::FONT_DEFAULT_SIZE = 24;

char* ZDlg::FRAME_L_NAME = "pic\\script\\frame_l.png";
char* ZDlg::FRAME_R_NAME = "pic\\script\\frame_r.png";
char* ZDlg::FRAME_F_NAME = "pic\\script\\frame_f.png";

CCSize ZDlg::FRAME_L_SIZE = CCSizeMake(0,0);
CCSize ZDlg::FRAME_R_SIZE = CCSizeMake(0,0);
CCSize ZDlg::FRAME_F_SIZE = CCSizeMake(0,0);

ZSprite* ZDlg::FRAME_L = new ZSprite(FRAME_L_NAME);
ZSprite* ZDlg::FRAME_R = new ZSprite(FRAME_R_NAME);
ZSprite* ZDlg::FRAME_F = new ZSprite(FRAME_F_NAME);

ZDlg::ZDlg(void)
{
}

ZDlg::ZDlg(int pos, char* script, char* figureFileName, char* font, int size)
{
	this->m_pos = pos;
	this->m_script = script;
	//this->m_scriptLabel = CCLabelTTF::create(script, font, size, CCSizeMake(/*68*/NeoConstants::WIN_WIDTH/2, 480),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
	this->m_scriptLabel = CCLabelTTF::create(script, font, size,this->getScriptSize(),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
	this->m_figure = new ZSprite(figureFileName);

	init();

}

void ZDlg::init(void)
{
	calcFrameSizes();
	calcPos();
	calcInitPos();
}

void ZDlg::calcInitPos(void)
{
	switch(this->m_pos)
	{
		case (/*ZDlg::POS_LEFT*/0):
		{			
			int x = m_framePos.x - m_frame->getWidth() - FRAME_MARGIN*2;
			int distance = m_framePos.x - x;

			m_frame->setPositionX(x);
			m_scriptLabel->setPositionX(m_scriptPos.x - distance);
			m_figure->setPositionX(m_figurePos.x - distance);
			
			break;
		}

		case (/*ZDlg::POS_RIGHT*/1):
		{			
			int x = m_framePos.x + m_frame->getWidth() + FRAME_MARGIN*2;
			int distance = x - m_framePos.x;

			m_frame->setPositionX(x);
			m_scriptLabel->setPositionX(m_scriptPos.x + distance);
			m_figure->setPositionX(m_figurePos.x + distance);
			
			break;
		}

		case (/*ZDlg::POS_FULL*/2):
		{			
			int y = m_framePos.y - m_frame->getHeight() - FRAME_MARGIN*2;
			int distance = m_framePos.y - y;

			m_frame->setPositionY(y);
			m_scriptLabel->setPositionY(m_scriptPos.y - distance);
			m_figure->setPositionY(m_figurePos.y - distance);
			
			break;
		}
	}
}

void ZDlg::calcFrame()
{
	switch(this->m_pos)
	{
		case (/*ZDlg::POS_LEFT*/0):
		{			
			m_frame = FRAME_L;
			break;
		}
		case (/*ZDlg::POS_RIGHT*/1):
		{			
			m_frame = FRAME_R;
			break;
		}		
		case (/*ZDlg::POS_FULL*/2):
		{			
			m_frame = FRAME_F;
			break;
		}
	}
}

CCSize ZDlg::getScriptSize()
{	
	CCSize frameSize = m_frame->getSize();
	return CCSizeMake(frameSize.width - SCRIPT_MARGIN, frameSize.height - SCRIPT_MARGIN);
}

void ZDlg::calcFrameSizes(void)
{
	this->FRAME_L_SIZE = FRAME_L->getSize();
	this->FRAME_R_SIZE = FRAME_R->getSize();
	this->FRAME_F_SIZE = FRAME_F->getSize();
}

void ZDlg::calcPos(void)
{
	calcFramePos();
	calcFigurePos();
	calcScriptPos();
}

void ZDlg::calcFramePos(void)
{
	switch(this->m_pos)
	{
		case (/*ZDlg::POS_LEFT*/0):
		{	
			this->m_framePos.y = FRAME_L->getHeight()/2 + FRAME_MARGIN;	
			this->m_framePos.x = FRAME_L->getWidth()/2 + FRAME_MARGIN;
			break;
		}

		case (/*ZDlg::POS_RIGHT*/1):
		{		
			this->m_framePos.y = FRAME_R->getHeight()/2 + FRAME_MARGIN;
			this->m_framePos.x = NeoConstants::WIN_WIDTH - FRAME_R->getWidth()/2 - FRAME_MARGIN;
			break;
		}

		case (/*ZDlg::POS_FULL*/2):
		{		
			this->m_framePos.y = FRAME_F->getHeight()/2 + FRAME_MARGIN;
			this->m_framePos.x = NeoConstants::WIN_WIDTH/2;
			break;
		}
	}
}

void ZDlg::calcFigurePos(void)
{
	CCPoint figurePos;
	switch(this->m_pos)
	{
		figurePos.y = m_framePos.y;
		case (/*ZDlg::POS_LEFT*/0):
		{			
			figurePos.x = m_framePos.x - FRAME_L->getWidth()/2 + FIGURE_MARGIN + m_figure->getWidth()/2;
			break;
		}

		case (/*ZDlg::POS_RIGHT*/1):
		{			
			figurePos.x = NeoConstants::WIN_WIDTH - m_figure->getWidth()/2 - FIGURE_MARGIN;
			break;
		}

		case (/*ZDlg::POS_FULL*/2):
		{			
			figurePos.x = m_framePos.x;
			break;
		}
	}

	m_figurePos = figurePos;
}

void ZDlg::calcScriptPos(void)
{
	m_scriptPos = this->m_framePos;
}

ZDlg::~ZDlg(void)
{
}
