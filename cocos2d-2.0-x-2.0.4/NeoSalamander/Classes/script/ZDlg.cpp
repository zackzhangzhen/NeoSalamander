#include "ZDlg.h"
#include "layer\ScriptLayer.h"
#include "menu\ZOption.h"
#include "menu\ZMenu.h"

int ZDlg::POS_LEFT = 0;
int ZDlg::POS_RIGHT = 1;
int ZDlg::POS_FULL = 2;

int ZDlg::FRAME_MARGIN = 6;
int ZDlg::SCRIPT_MARGIN = 20;
int ZDlg::FIGURE_MARGIN = 10;
char* ZDlg::FRAME_L_NAME = "pic\\script\\frame_lr.png";
char* ZDlg::FRAME_R_NAME = "pic\\script\\frame_lr.png";
char* ZDlg::FRAME_F_NAME = "pic\\script\\frame_f.png";

CCSize ZDlg::FRAME_L_SIZE = CCSizeMake(0,0);
CCSize ZDlg::FRAME_R_SIZE = CCSizeMake(0,0);
CCSize ZDlg::FRAME_F_SIZE = CCSizeMake(0,0);

ZSprite* ZDlg::FRAME_L = NULL;
ZSprite* ZDlg::FRAME_R = NULL;
ZSprite* ZDlg::FRAME_F = NULL;

ZDlg::ZDlg(void)
{
}

ZDlg::ZDlg(TiXmlElement* dlgElem, CCNode* parentNode)
{
	//set the parent layer to the script layer
	m_parentScriptLayer = (ScriptLayer*)parentNode;

	TiXmlElement* lineElem = dlgElem->FirstChildElement();
	assert(lineElem != NULL);

	//vector<char*>* lines = new vector<char*>();
	vector<ScriptElement*> lines;
	int pos = ZDlg::POS_LEFT;
	dlgElem->Attribute(NeoConstants::SCRIPT_ATTR_POS, &pos);

	int size = ZLabelTTF::FONT_DEFAULT_SIZE;
	dlgElem->Attribute(NeoConstants::SCRIPT_ATTR_SIZE, &size);

	int colorCode = ZLabelTTF::FONT_COLOR_DEFAULT;
	dlgElem->Attribute(NeoConstants::SCRIPT_ATTR_COLOR, &colorCode);

	int figure_vertical_offset = NeoConstants::FIGURE_VERTICAL_OFFSET;
	dlgElem->Attribute(NeoConstants::SCRIPT_ATTR_FIGURE_VERTICAL_OFFSET, &figure_vertical_offset);

	char* font = (char*)dlgElem->Attribute(NeoConstants::SCRIPT_ATTR_FONT);
	char* imageFile = (char*)dlgElem->Attribute(NeoConstants::SCRIPT_ATTR_IMAGE);
	char* musicName = (char*)dlgElem->Attribute(NeoConstants::SCRIPT_ATTR_MUSIC);

	char* stopMusic = (char*)dlgElem->Attribute(NeoConstants::SCRIPT_ATTR_STOP_MUSIC);
	bool isStopMusic = stopMusic == NULL?false:true;

	for( ; lineElem != NULL; lineElem=lineElem->NextSiblingElement())
	{
		const char* tagName = lineElem->Value();
		if(strcmp(tagName, NeoConstants::SCRIPT_TAG_LINE) == 0)
		{
			char* line = (char*)lineElem->GetText();
			char* lineId = (char*)lineElem->Attribute(NeoConstants::SCRIPT_ATTR_ID);
			lines.push_back(new ValueWrapper(lineId, line));
		}
		else if(strcmp(tagName, NeoConstants::SCRIPT_TAG_OPTIONS) == 0)
		{
			ZMenu* menu = new ZMenu(lineElem, this->m_parentScriptLayer);
			lines.push_back(menu);
		}
		
	}

	zDlgInit(pos, lines, imageFile, musicName, isStopMusic, parentNode, colorCode, font, size, figure_vertical_offset);
}

void ZDlg::zDlgInit(int pos, vector<ScriptElement*>& scripts, char* figureFileName, char* musicName, bool isStopMusic, CCNode* parentNode,int colorCode, char* font, int size, int figure_vertical_offset)
{
	m_scriptState = ScriptState::NOT_FADED_IN;
	m_parentScriptLayer = NULL;
	m_figureFileName = figureFileName;
	m_musicName = musicName;
	m_stopMusic = isStopMusic;
	m_figureVerticalOffset = figure_vertical_offset;
	m_scripts = scripts;
	m_colorCode = colorCode;
	m_font = font;
	m_size = size;
	this->m_frame = NULL;
	

	 this->m_pos = pos;

	 if(parentNode != NULL)
	{
		this->m_parentScriptLayer = (ScriptLayer*)parentNode;
		//move to ZDlgLazyInit()
		//this->addToCCNode(parentNode, 10);
	}

	 this->m_scriptState = ScriptState::NOT_FADED_IN;

	//this->m_scriptLabel = CCLabelTTF::create(script, font, size, CCSizeMake(/*68*/NeoConstants::WIN_WIDTH/2, 480),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
	
		
	//move to ZDlgLazyInit()
	//this->m_figure = new ZSprite(figureFileName);

}

void ZDlg::zDlgLazyInit()
{		
	initFramePrototype(m_parentScriptLayer, 10+1);
	initFrame();
	this->m_scriptLabel = new ZLabelTTF(m_scripts, this->getScriptSize(), m_colorCode, m_font == NULL? ZLabelTTF::YAHEI : m_font,  m_size);
	this->m_figure = new ZSprite(m_figureFileName);
	

	init(m_figureVerticalOffset);
	this->addToCCNode(m_parentScriptLayer, 10);
}

void ZDlg::initFramePrototype(CCNode* parent, int zOrder)
{
	//In here, must add all the frames in to a parent, otherwise they will be destroyed soon.
	if(FRAME_L == NULL)
	{
		FRAME_L = new ZSprite(FRAME_L_NAME);
		FRAME_L->addToCCNode(parent, zOrder);
		FRAME_L->setOpacity(0);
	}
	if(FRAME_R == NULL)
	{
		FRAME_R = new ZSprite(FRAME_R_NAME);
		FRAME_R->addToCCNode(parent, zOrder);
		FRAME_R->setOpacity(0);
	}
	if(FRAME_F == NULL)
	{
		FRAME_F = new ZSprite(FRAME_F_NAME);
		FRAME_F->addToCCNode(parent, zOrder);
		FRAME_F->setOpacity(0);
	}
}

void ZDlg::initFrame()
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


void ZDlg::addToCCNode(CCNode* node, int baseOrder)
{
	assert(node != NULL);

	m_figure->addToCCNode(node, baseOrder);
	m_frame->addToCCNode(node, baseOrder + 1);
	m_scriptLabel->addToCCNode(node, baseOrder + 2);
}


void ZDlg::setAnimationPlayingDone(CCNode* sender)
{
	this->m_parentScriptLayer->setAnimationPlaying(false);
}

void ZDlg::playMusic()
{
	if(m_musicName != NULL)
	{
		Utility::playMusic(m_musicName);
	}	
}

void ZDlg::fadeIn(bool delay)
{
	playMusic();

	m_scriptState = ScriptState::SCRIPT_ROLLING;
	m_parentScriptLayer->setAnimationPlaying(true);
	CCFiniteTimeAction* animationDone = CCCallFuncN::actionWithTarget(this,callfuncN_selector(ZDlg::setAnimationPlayingDone));
	switch(this->m_pos)
	{
		case (/*ZDlg::POS_FULL*/2):
		{	
			CCFadeIn* pCCFadeIn1= CCFadeIn::actionWithDuration(1);
			CCFadeIn* pCCFadeIn2= CCFadeIn::actionWithDuration(1.5);
			CCFadeIn* pCCFadeIn3= CCFadeIn::actionWithDuration(1);

			CCDelayTime *delayAction = CCDelayTime::actionWithDuration(1);

			if(delay)
			{

				CCDelayTime *allDelayAction1 = CCDelayTime::actionWithDuration(2);
				CCDelayTime *allDelayAction2 = CCDelayTime::actionWithDuration(2);
				CCDelayTime *allDelayAction3 = CCDelayTime::actionWithDuration(2);

				m_frame->getSprite()->runAction(CCSequence::actions(allDelayAction1,pCCFadeIn1, NULL));
				m_figure->getSprite()->runAction(CCSequence::actions(allDelayAction2,pCCFadeIn2, NULL));
				m_scriptLabel->runAction(CCSequence::actions(allDelayAction3, delayAction, pCCFadeIn3,animationDone, NULL));

				return ;
			}

			m_frame->getSprite()->runAction(pCCFadeIn1);
			m_figure->getSprite()->runAction(pCCFadeIn2);			
			m_scriptLabel->runAction(CCSequence::actions(delayAction, pCCFadeIn3,animationDone, NULL));

			break;
		}
		default:
			{
				//m_frame->setPosition(m_frameInitPos);
				//m_figure->setPosition(m_figureInitPos);
				CCMoveTo* frameMoveTo = CCMoveTo::actionWithDuration(0.5, m_framePos);
				CCMoveTo* figureMoveTo = CCMoveTo::actionWithDuration(1, m_figurePos);
				CCMoveTo* scriptMoveTo = CCMoveTo::actionWithDuration(0.5, m_scriptPos);

				CCFadeIn* pCCFadeIn= CCFadeIn::actionWithDuration(1);
				CCDelayTime *delayAction = CCDelayTime::actionWithDuration(0.5);


				if(delay)
				{

					m_parentScriptLayer->setAnimationPlaying(true);

					CCDelayTime *allDelayAction1 = CCDelayTime::actionWithDuration(2);
					CCDelayTime *allDelayAction2 = CCDelayTime::actionWithDuration(2);
					CCDelayTime *allDelayAction3 = CCDelayTime::actionWithDuration(2);

					m_frame->getSprite()->runAction(CCSequence::actions(allDelayAction1,frameMoveTo, NULL));
					m_figure->getSprite()->runAction(CCSequence::actions(allDelayAction2,figureMoveTo, NULL));
					m_scriptLabel->runAction(CCSequence::actions(allDelayAction3, scriptMoveTo, delayAction, pCCFadeIn,animationDone, NULL));

					return ;
				}

				m_frame->getSprite()->runAction(frameMoveTo);
				m_figure->getSprite()->runAction(figureMoveTo);
				m_scriptLabel->runAction(CCSequence::actions(scriptMoveTo, delayAction, pCCFadeIn,animationDone, NULL));

			}
	}
}

void ZDlg::autoRelease(CCNode* sender)
{
	CCSprite* sprite = (CCSprite*)sender;
	this->m_parentScriptLayer->removeChild(sprite,true);
	sprite->autorelease();

	/*EnterCriticalSection(&GlobalFlag::m_csObject);
	
	CCSprite* sprite = (CCSprite*)sender;
	this->m_parentScriptLayer->removeChild(this->m_figure->getSprite(),true);
	this->m_parentScriptLayer->removeChild(this->m_frame->getSprite(),true);
	this->m_parentScriptLayer->removeChild(this->m_scriptLabel->getLabel(),true);

	this->m_figure->getSprite()->autorelease();
	this->m_frame->getSprite()->autorelease();
	this->m_scriptLabel->getLabel()->autorelease();

	LeaveCriticalSection(&GlobalFlag::m_csObject);*/
}


void ZDlg::fadeOut(float interval0,float interval1,float interval2,float interval3,float interval4,float interval5,float interval6,float interval7,float interval8,float interval9,float interval10)
{
	//stop 
	if(this->isStopMusic())
	{
		Utility::stopMusic();
	}

	m_scriptState = ScriptState::SCRIPT_DONE;
	m_parentScriptLayer->setAnimationPlaying(true);

	CCFiniteTimeAction* animationDone = CCCallFuncN::actionWithTarget(this,callfuncN_selector(ZDlg::setAnimationPlayingDone));
	CCFiniteTimeAction* autoReleaseAction = CCCallFuncN::actionWithTarget(this,callfuncN_selector(ZDlg::autoRelease));

	switch(this->m_pos)
	{
		case (/*ZDlg::POS_FULL*/2):
		{	
			CCFadeOut* pCCFadeOut1= CCFadeOut::actionWithDuration(interval0);
			CCFadeOut* pCCFadeOut2= CCFadeOut::actionWithDuration(interval1);
			CCFadeOut* pCCFadeOut3= CCFadeOut::actionWithDuration(interval2);

			CCDelayTime *delayAction1 = CCDelayTime::actionWithDuration(interval3);
			CCDelayTime *delayAction2 = CCDelayTime::actionWithDuration(interval4);

			//don't auto-release frames, they will be reused throught all the dlgs
			m_frame->getSprite()->runAction(CCSequence::actions(delayAction1, pCCFadeOut1, NULL));
			m_figure->getSprite()->runAction(CCSequence::actions(delayAction2, pCCFadeOut2/*, animationDone*/,autoReleaseAction, NULL));
			m_scriptLabel->runAction(CCSequence::actions(pCCFadeOut3,autoReleaseAction, NULL));
			break;
		}
		default:
			{
				CCMoveTo* frameMoveTo = CCMoveTo::actionWithDuration(interval5, m_frameInitPos);
				CCMoveTo* figureMoveTo = CCMoveTo::actionWithDuration(interval6, m_figureInitPos);
				CCMoveTo* scriptMoveTo = CCMoveTo::actionWithDuration(interval7, m_scriptInitPos);

				CCFadeOut* pCCFadeOut= CCFadeOut::actionWithDuration(interval8);
				CCDelayTime *delayAction1 = CCDelayTime::actionWithDuration(interval9);
				CCDelayTime *delayAction2 = CCDelayTime::actionWithDuration(interval10);

				//don't auto-release frames, they will be reused throught all the dlgs
				m_frame->getSprite()->runAction(CCSequence::actions(delayAction1, frameMoveTo, NULL));
				m_figure->getSprite()->runAction(CCSequence::actions(delayAction2, figureMoveTo/*, animationDone*/, autoReleaseAction, NULL));
				m_scriptLabel->runAction(CCSequence::actions(pCCFadeOut,scriptMoveTo,autoReleaseAction, NULL));

			}
	}
}

void ZDlg::fadeOut()
{
	fadeOut(1, 1.5, 1, 1, 1,1.5,0.8,1.5,1,1,1);
}

bool ZDlg::fadeOutInstantly()
{
	if(m_scriptState != ScriptState::NOT_FADED_IN && m_scriptState != ScriptState::SCRIPT_DONE)
	{
		fadeOut(0.1, 0.1, 0.1, 0.1, 0.1,0.1,0.1,0.1,0.1,0.1,0.1);
		return true;
	}

	return false;
	
}

void ZDlg::jumpToLine(char* lineId)
{
	this->m_scriptLabel->jumpToLine(lineId);
}

void ZDlg::refresh()
{
	m_scriptState = ScriptState::NOT_FADED_IN;
	this->zDlgLazyInit();
}

bool ZDlg::play(bool delay)
{
	//when the background fades in, the cue is turned on, will need to turn it off when the scripts start to play.
	this->m_parentScriptLayer->switchCue(false);

	switch(m_scriptState)
	{
		case(ScriptState::NOT_FADED_IN):
		{
			this->zDlgLazyInit();
			this->fadeIn(delay);
			return false;
		}

		case( ScriptState::SCRIPT_ROLLING):
		{
			if(this->m_scriptLabel->rollScript())
			{
				m_scriptState = ScriptState::SCRIPT_DONE;
				this->fadeOut();
				return true;
			}
		}

		default:

			return false;
	}
}

void ZDlg::init(int figure_vertical_offset)
{
	calcInitOpacity();
	calcFrameSizes();
	calcPos(figure_vertical_offset);
	calcInitPos();
}

void ZDlg::calcInitOpacity(void)
{
	m_scriptLabel->setOpacity(0);

	switch(this->m_pos)
	{
		case (/*ZDlg::POS_FULL*/2):
		{	
			m_frame->setOpacity(0);
			m_figure->setOpacity(0);

			break;
		}
		default:
			m_frame->setOpacity(255);
	}
}

void ZDlg::calcInitPos(void)
{
	switch(this->m_pos)
	{
		case (/*ZDlg::POS_LEFT*/0):
		{			
			int x = m_framePos.x - m_frame->getWidth() - FRAME_MARGIN*2;
			int distance = m_framePos.x - x;

			m_frameInitPos = ccp(x,m_framePos.y);
			m_scriptInitPos = ccp(m_scriptPos.x - distance, m_scriptPos.y);
			m_figureInitPos = ccp(m_figurePos.x - distance, m_figurePos.y);

			m_frame->setPosition(m_frameInitPos);
			m_scriptLabel->setPosition(m_scriptInitPos);
			m_figure->setPosition(m_figureInitPos);
			
			break;
		}

		case (/*ZDlg::POS_RIGHT*/1):
		{			
			int x = m_framePos.x + m_frame->getWidth() + FRAME_MARGIN*2;
			int distance = x - m_framePos.x;

			m_frameInitPos = ccp(x,m_framePos.y);
			m_scriptInitPos = ccp(m_scriptPos.x + distance, m_scriptPos.y);
			m_figureInitPos = ccp(m_figurePos.x + distance, m_figurePos.y);

			m_frame->setPositionX(x);
			m_scriptLabel->setPositionX(m_scriptInitPos.x);
			m_figure->setPositionX(m_figureInitPos.x);
			
			break;
		}

		case (/*ZDlg::POS_FULL*/2):
		{	
			//In this case, don't slide in,make it fade in, so don't move them out of the screen.
			/*int y = m_framePos.y - m_frame->getHeight() - FRAME_MARGIN*2;
			int distance = m_framePos.y - y;

			m_frame->setPositionY(y);
			m_scriptLabel->setPositionY(m_scriptPos.y - distance);
			m_figure->setPositionY(m_figurePos.y - distance);*/
			
			m_frame->setPosition(m_framePos);
			m_scriptLabel->setPosition(m_scriptPos);
			m_figure->setPosition(m_figurePos);
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

void ZDlg::calcPos(int figure_vertical_offset)
{
	calcFramePos();
	calcFigurePos(figure_vertical_offset);
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
	this->m_frame->setPosition(m_framePos);
}

void ZDlg::calcFigurePos(int figure_vertical_offset)
{
	CCPoint figurePos;
	switch(this->m_pos)
	{
		
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
	m_figurePos.y = m_figurePos.y + figure_vertical_offset;
	this->m_figure->setPosition(m_figurePos);
}

void ZDlg::calcScriptPos(void)
{
	//m_scriptPos = ccp(this->m_framePos.x + SCRIPT_MARGIN,this->m_framePos.y - SCRIPT_MARGIN) ;
	m_scriptPos = this->m_framePos;

	this->m_scriptLabel->setPosition(m_scriptPos);
}


char* ZDlg::getMusicName()
{
	return m_musicName;
}

bool ZDlg::isStopMusic()
{
	return m_stopMusic;
}

ZDlg::~ZDlg(void)
{
}
