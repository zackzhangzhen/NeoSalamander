

#include "ScriptPlayer.h"
#include "layer\ScriptLayer.h"

ScriptPlayer::ScriptPlayer(char* id, vector<ZDlg*>& vec)
{
	this->m_id = id;
	this->m_vec = vec;

	m_iter = m_vec.begin();
}

ScriptPlayer::ScriptPlayer(char* id, TiXmlElement* scriptElem, CCNode* parentNode)
{
	TiXmlElement* dlgElem = scriptElem->FirstChildElement();
	assert(dlgElem != NULL);

	//Initialize the background sprite, don't initialize here, will lazy-initialize it, so that it saves memory, and also when loading a game it will be re-initialized, this is necessary as it might have been manually GCed.
	//initBg(scriptElem, parentNode);
	m_bgPic = (char*)scriptElem->Attribute(NeoConstants::SCRIPT_ATTR_PIC);

	for( ; dlgElem != NULL; dlgElem=dlgElem->NextSiblingElement())
	{
		ZDlg* dlg = new ZDlg(dlgElem, parentNode);
		m_vec.push_back(dlg);
	}

	this->m_nextScriptPlayerId = (char*)scriptElem->Attribute(NeoConstants::SCRIPT_ATTR_TO_SCRIPT);
	this->m_originNextScriptPlayerId = (char*)scriptElem->Attribute(NeoConstants::SCRIPT_ATTR_TO_SCRIPT);


	this->m_id = id;
	this->m_title = (char*)scriptElem->Attribute(NeoConstants::SCRIPT_ATTR_TITLE);
	m_iter = m_vec.begin();
	this->m_parentScriptLayer = (ScriptLayer*) parentNode;
	this->fadedIn = false;
}

ScriptPlayer::~ScriptPlayer(void)
{
}

void ScriptPlayer::refresh()
{
	//when making choices, sometimes the next script id will be reset, so when loading that script,will need to set it back.
	this->resetNextScriptId();
	//when the script faded out, the background sprite will be released, so when loading that script, will need to create it again.
	this->initBg();

	//when the gamer load a game in the middle of playing, the iterator would have moved, and the state would have chanegd, reset them to default.
	m_iter = m_vec.begin();
	this->fadedIn = false;			
	this->m_parentScriptLayer->switchCue(false);//turn off cue

	refreshChildrenDlg();
}

void ScriptPlayer::refreshChildrenDlg()
{
	vector<ZDlg*>::iterator iter = m_vec.begin();
	for(; iter != m_vec.end(); iter++)
	{
		ZDlg* dlg = *iter;
		dlg->refresh();
	}
}

void ScriptPlayer::initBg()
{	
	this->m_bg = new ZSprite(Utility::zstrcat((char*)NeoConstants::BG_PIC_BASE, m_bgPic), m_parentScriptLayer);
	this->m_bg->setOpacity(0); // will fade in when the script plays
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	this->m_bg->setPosition(ccp(size.width/2, size.height/2));// positioned in the center

}
char* ScriptPlayer::getId()
{
	return m_id;
}

char* ScriptPlayer::getTitle()
{
	return m_title;
}

char* ScriptPlayer::getNextScriptPlayerId()
{
	return this->m_nextScriptPlayerId;
}

char* ScriptPlayer::getOriginNextScriptPlayerId()
{
	return this->m_originNextScriptPlayerId;
}

void ScriptPlayer::resetNextScriptId()
{
	this->m_nextScriptPlayerId = this->m_originNextScriptPlayerId;
}

void ScriptPlayer::setNextScriptPlayerId(char* id)
{
	this->m_nextScriptPlayerId = id;
}

void ScriptPlayer::setAnimationPlayingDone(CCNode* sender)
{
	this->m_parentScriptLayer->setAnimationPlaying(false);
}

void ScriptPlayer::switchCueOn(CCNode* sender)
{
	this->m_parentScriptLayer->switchCue(true);
}

void ScriptPlayer::switchCueOff(CCNode* sender)
{
	this->m_parentScriptLayer->switchCue(false);
}



void ScriptPlayer::fadeIn(bool delay)
{
	CCFiniteTimeAction* animationDone = CCCallFuncN::actionWithTarget(this,callfuncN_selector(ScriptPlayer::setAnimationPlayingDone));
	CCFiniteTimeAction* switchCueOn = CCCallFuncN::actionWithTarget(this,callfuncN_selector(ScriptPlayer::switchCueOn));
	
	CCFadeIn* pCCFadeIn= CCFadeIn::actionWithDuration(5);

	m_parentScriptLayer->setAnimationPlaying(true);

	if(delay)
	{
		//3+5 means 5s fadeout + 3s delay for the last script
		CCDelayTime *delayAction = CCDelayTime::actionWithDuration(3+5);
		m_bg->getSprite()->runAction(CCSequence::actions(delayAction, pCCFadeIn, animationDone, switchCueOn,  NULL));

		return ;
	}

	m_bg->getSprite()->runAction(CCSequence::actions(pCCFadeIn, animationDone, switchCueOn,  NULL));
}


void ScriptPlayer::bgFadeOut(float interval0, float interval1, bool delay, bool switchCueOnAndSetAnimationDone)
{	
	CCFiniteTimeAction* animationDone = NULL;
	CCFiniteTimeAction* switchCueOnAction = NULL;
	
	//only one scenario that we need to pass switchCueOn as false : when the user selects an option that jumps 
	//to another script, the cue will be switched on when the next script fades in, so don't need to switch it 
	//on when this one fades out (thus default value is true);
	//animation done is the same, since the fading out script and the fading in script can kindof be considered
	//play this fade-out-fade-in animation together, we do not reset the state for the fade-out and only do it 
	//after the fade-in is done.
	if(switchCueOnAndSetAnimationDone)
	{
		animationDone = CCCallFuncN::actionWithTarget(this,callfuncN_selector(ScriptPlayer::setAnimationPlayingDone));
		switchCueOnAction = CCCallFuncN::actionWithTarget(this,callfuncN_selector(ScriptPlayer::switchCueOn));
	}
	CCFiniteTimeAction* autoReleaseAction = CCCallFuncN::actionWithTarget(this,callfuncN_selector(ScriptPlayer::autoRelease));

	
	CCFadeOut* pCCFadeOut= CCFadeOut::actionWithDuration(interval0);

	m_parentScriptLayer->setAnimationPlaying(true);

	if(delay)
	{
		CCDelayTime *delayAction = CCDelayTime::actionWithDuration(interval1);

		if(switchCueOnAndSetAnimationDone)
		{
			m_bg->getSprite()->runAction(CCSequence::actions(delayAction, pCCFadeOut, switchCueOnAction, animationDone, autoReleaseAction, NULL));
		}
		else
		{
			m_bg->getSprite()->runAction(CCSequence::actions(delayAction, pCCFadeOut, autoReleaseAction, NULL));
		}
		
		return ;
	}

	//remember to release the background sprite when it has faded out.
	if(switchCueOnAndSetAnimationDone)
	{
		m_bg->getSprite()->runAction(CCSequence::actions(pCCFadeOut, switchCueOnAction, animationDone,autoReleaseAction, NULL));
	}
	else
	{
		m_bg->getSprite()->runAction(CCSequence::actions(pCCFadeOut, autoReleaseAction, NULL));
	}
	
}


void ScriptPlayer::bgFadeOut(bool delay, bool switchCueOnAndSetAnimationDone)
{	
	this->bgFadeOut(5,3,delay,switchCueOnAndSetAnimationDone);	
}

void ScriptPlayer::bgFadeOutInstantly()
{	
	this->bgFadeOut(0.1,0.1,false,true);	
}

void ScriptPlayer::fadeOut(bool switchCueOn)
{
	assert(m_iter != m_vec.end());

	ZDlg* dlg = *m_iter;
	dlg->fadeOut();
	//no next dlg, conclude the script with fading out the background
	this->bgFadeOut(true,switchCueOn);
}

void ScriptPlayer::fadeOutInstantly()
{
	if(m_iter != m_vec.end())
	{
		ZDlg* dlg = *m_iter;
		//if dlg->fadeOutInstantly() returns true, then the current state indicates that bg has been intialized and hasn't been faded out, then do it
		if(dlg->fadeOutInstantly())
		{
			this->bgFadeOutInstantly();
		}
		
	}	
	
	Utility::stopMusic();
}

void ScriptPlayer::jumpToLine(char* lineId)
{
	assert(m_iter != m_vec.end());
	ZDlg* dlg = *m_iter;
	dlg->jumpToLine(lineId);
}

bool ScriptPlayer::play(bool delay)
{
	if(!fadedIn)
	{
		//lazy-initialization
		this->initBg();

		this->fadeIn(delay);
		this->fadedIn = true;

		//turn off cue
		this->m_parentScriptLayer->switchCue(false);

		return false;
	}

	if(m_iter != m_vec.end())
	{
		ZDlg* dlg = *m_iter;

		if(dlg->play(false))
		{
			//entering here means the current dlg is done, play the next dlg or fade out the background

			m_iter++;

			//play the next dlg with delay
			if(m_iter != m_vec.end())
			{
				dlg = *m_iter;
				dlg->play(true);
				return false;
			}

			//no next dlg, conclude the script with fading out the background
			this->bgFadeOut(true);
			return true;
		}

		return false;
	}
	else
	{
		return true;
	}
}

void ScriptPlayer::autoRelease(CCNode* sender)
{
	CCSprite* sprite = (CCSprite*)sender;
	this->m_parentScriptLayer->removeChild(sprite,true);
	sprite->autorelease();
}

