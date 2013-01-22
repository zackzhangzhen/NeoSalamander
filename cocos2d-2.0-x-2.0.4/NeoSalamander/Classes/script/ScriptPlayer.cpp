

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

	//Initialize the background sprite
	initBg(scriptElem, parentNode);

	for( ; dlgElem != NULL; dlgElem=dlgElem->NextSiblingElement())
	{
		ZDlg* dlg = new ZDlg(dlgElem, parentNode);
		m_vec.push_back(dlg);
	}

	this->m_id = id;
	m_iter = m_vec.begin();
	this->m_parentScriptLayer = (ScriptLayer*) parentNode;
	this->fadedIn = false;
}

ScriptPlayer::~ScriptPlayer(void)
{
}
void ScriptPlayer::initBg(TiXmlElement* scriptElem, CCNode* parentNode)
{
	char* bg_pic_name = (char*)scriptElem->Attribute(NeoConstants::SCRIPT_ATTR_PIC);
	this->m_bg = new ZSprite(Utility::zstrcat((char*)NeoConstants::BG_PIC_BASE, bg_pic_name), parentNode);
	this->m_bg->setOpacity(0); // will fade in when the script plays
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	this->m_bg->setPosition(ccp(size.width/2, size.height/2));// positioned in the center

}
char* ScriptPlayer::getId()
{
	return m_id;
}


void ScriptPlayer::setAnimationPlayingDone(CCNode* sender)
{
	this->m_parentScriptLayer->setAnimationPlaying(false);
}

void ScriptPlayer::fadeIn(bool delay)
{
	CCFiniteTimeAction* animationDone = CCCallFuncN::actionWithTarget(this,callfuncN_selector(ScriptPlayer::setAnimationPlayingDone));

	CCFadeIn* pCCFadeIn= CCFadeIn::actionWithDuration(5);

	m_parentScriptLayer->setAnimationPlaying(true);

	if(delay)
	{
		CCDelayTime *delayAction = CCDelayTime::actionWithDuration(1);
		m_bg->getSprite()->runAction(CCSequence::actions(delayAction, pCCFadeIn, animationDone, NULL));

		return ;
	}

	m_bg->getSprite()->runAction(CCSequence::actions(pCCFadeIn, animationDone, NULL));
}

void ScriptPlayer::fadeOut(bool delay)
{
	CCFiniteTimeAction* animationDone = CCCallFuncN::actionWithTarget(this,callfuncN_selector(ScriptPlayer::setAnimationPlayingDone));

	CCFadeOut* pCCFadeOut= CCFadeOut::actionWithDuration(5);

	m_parentScriptLayer->setAnimationPlaying(true);

	if(delay)
	{
		CCDelayTime *delayAction = CCDelayTime::actionWithDuration(3);
		m_bg->getSprite()->runAction(CCSequence::actions(delayAction, pCCFadeOut, animationDone, NULL));

		return ;
	}

	m_bg->getSprite()->runAction(CCSequence::actions(pCCFadeOut, animationDone, NULL));
}


bool ScriptPlayer::play()
{
	if(!fadedIn)
	{
		this->fadeIn(false);
		this->fadedIn = true;
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
			this->fadeOut(true);
			return true;
		}

		return false;
	}
	else
	{
		return true;
	}
}

