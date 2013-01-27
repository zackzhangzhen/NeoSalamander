#include "ZDlg.h"
#include "layer\ScriptLayer.h"

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
	TiXmlElement* lineElem = dlgElem->FirstChildElement();
	assert(lineElem != NULL);

	//vector<char*>* lines = new vector<char*>();
	vector<char*> lines;
	int pos = ZDlg::POS_LEFT;
	dlgElem->Attribute("pos", &pos);

	int size = ZLabelTTF::FONT_DEFAULT_SIZE;
	dlgElem->Attribute("size", &size);

	int figure_vertical_offset = NeoConstants::FIGURE_VERTICAL_OFFSET;
	dlgElem->Attribute(NeoConstants::SCRIPT_ATTR_FIGURE_VERTICAL_OFFSET, &figure_vertical_offset);

	char* font = (char*)dlgElem->Attribute("font");
	char* imageFile = (char*)dlgElem->Attribute("image");
	for( ; lineElem != NULL; lineElem=lineElem->NextSiblingElement())
	{
		char* line = (char*)lineElem->GetText();
		lines.push_back(line);
	}

	ZDlgInit(pos, lines, imageFile, parentNode, font, size, figure_vertical_offset);
}

void ZDlg::ZDlgInit(int pos, vector<char*>& scripts, char* figureFileName, CCNode* parentNode, char* font, int size, int figure_vertical_offset)
{
	m_scriptState = ScriptState::NOT_FADED_IN;
	m_parentScriptLayer = NULL;

	this->m_frame = NULL;
	 initFramePrototype();

	 this->m_pos = pos;
	 initFrame();

	//this->m_scriptLabel = CCLabelTTF::create(script, font, size, CCSizeMake(/*68*/NeoConstants::WIN_WIDTH/2, 480),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
	this->m_scriptLabel = new ZLabelTTF(scripts, this->getScriptSize(), font, size);
	this->m_figure = new ZSprite(figureFileName);

	init(figure_vertical_offset);

	if(parentNode != NULL)
	{
		this->m_parentScriptLayer = (ScriptLayer*)parentNode;
		this->addToCCNode(parentNode, 10);
	}
}

ZDlg::ZDlg(int pos, vector<char*>& scripts, char* figureFileName, CCNode* parentNode, char* font, int size)
{
	ZDlgInit(pos, scripts, figureFileName, parentNode, font, size);
}

ZDlg::ZDlg(int pos, char* script, char* figureFileName, CCNode* parentNode, char* font, int size)
{
	m_scriptState = ScriptState::NOT_FADED_IN;
	m_parentScriptLayer = NULL;

	this->m_frame = NULL;
	 initFramePrototype();

	 this->m_pos = pos;
	 initFrame();

	//this->m_scriptLabel = CCLabelTTF::create(script, font, size, CCSizeMake(/*68*/NeoConstants::WIN_WIDTH/2, 480),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
	this->m_scriptLabel = new ZLabelTTF(script, this->getScriptSize(), font);
	this->m_scriptLabel->setOpacity(0);
	this->m_figure = new ZSprite(figureFileName);

	init();

	if(parentNode != NULL)
	{
		this->m_parentScriptLayer = (ScriptLayer*)parentNode;
		this->addToCCNode(parentNode, 10);
	}
}

void ZDlg::initFramePrototype()
{
	if(FRAME_L == NULL)
	{
		FRAME_L = new ZSprite(FRAME_L_NAME);
	}
	if(FRAME_R == NULL)
	{
		FRAME_R = new ZSprite(FRAME_R_NAME);
	}
	if(FRAME_F == NULL)
	{
		FRAME_F = new ZSprite(FRAME_F_NAME);
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

void ZDlg::fadeIn(bool delay)
{
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

void ZDlg::fadeOut()
{
	m_parentScriptLayer->setAnimationPlaying(true);

	CCFiniteTimeAction* animationDone = CCCallFuncN::actionWithTarget(this,callfuncN_selector(ZDlg::setAnimationPlayingDone));
	CCFiniteTimeAction* autoReleaseAction = CCCallFuncN::actionWithTarget(this,callfuncN_selector(ZDlg::autoRelease));

	switch(this->m_pos)
	{
		case (/*ZDlg::POS_FULL*/2):
		{	
			CCFadeOut* pCCFadeOut1= CCFadeOut::actionWithDuration(1);
			CCFadeOut* pCCFadeOut2= CCFadeOut::actionWithDuration(1.5);
			CCFadeOut* pCCFadeOut3= CCFadeOut::actionWithDuration(1);

			CCDelayTime *delayAction1 = CCDelayTime::actionWithDuration(1);
			CCDelayTime *delayAction2 = CCDelayTime::actionWithDuration(1);

			//don't auto-release frames, they will be reused throught all the dlgs
			m_frame->getSprite()->runAction(CCSequence::actions(delayAction1, pCCFadeOut1, NULL));
			m_figure->getSprite()->runAction(CCSequence::actions(delayAction2, pCCFadeOut2/*, animationDone*/,autoReleaseAction, NULL));
			m_scriptLabel->runAction(CCSequence::actions(pCCFadeOut3,autoReleaseAction, NULL));
			break;
		}
		default:
			{
				CCMoveTo* frameMoveTo = CCMoveTo::actionWithDuration(1.5, m_frameInitPos);
				CCMoveTo* figureMoveTo = CCMoveTo::actionWithDuration(0.8, m_figureInitPos);
				CCMoveTo* scriptMoveTo = CCMoveTo::actionWithDuration(1.5, m_scriptInitPos);

				CCFadeOut* pCCFadeOut= CCFadeOut::actionWithDuration(1);
				CCDelayTime *delayAction1 = CCDelayTime::actionWithDuration(1);
				CCDelayTime *delayAction2 = CCDelayTime::actionWithDuration(1);

				//don't auto-release frames, they will be reused throught all the dlgs
				m_frame->getSprite()->runAction(CCSequence::actions(delayAction1, frameMoveTo, NULL));
				m_figure->getSprite()->runAction(CCSequence::actions(delayAction2, figureMoveTo/*, animationDone*/, autoReleaseAction, NULL));
				m_scriptLabel->runAction(CCSequence::actions(pCCFadeOut,scriptMoveTo,autoReleaseAction, NULL));

			}
	}
}

bool ZDlg::play(bool delay)
{
	//when the background fades in, the cue is turned on, will need to turn it off when the scripts start to play.
	this->m_parentScriptLayer->switchCue(false);

	switch(m_scriptState)
	{
		case(ScriptState::NOT_FADED_IN):
		{
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

ZDlg::~ZDlg(void)
{
}
