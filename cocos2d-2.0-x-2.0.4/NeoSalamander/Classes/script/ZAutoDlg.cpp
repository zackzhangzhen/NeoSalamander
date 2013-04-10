#include "ZAutoDlg.h"
#include "layer\ScriptLayer.h"
#include "script\ZLabelTTF.h"
ZAutoDlg::ZAutoDlg(TiXmlElement* dlgElem, CCNode* parentNode, ScriptPlayer* parentPlayer): ZDlg()
{
	m_parentScriptLayer = (ScriptLayer*)parentNode;

	TiXmlElement* lineElem = dlgElem->FirstChildElement();
	assert(lineElem != NULL);

	vector<ScriptElement*> lines = Utility::createLines(lineElem, this->m_parentScriptLayer, parentPlayer);

	m_musicName = (char*)dlgElem->Attribute(NeoConstants::SCRIPT_ATTR_MUSIC);	
	char* stopMusic = (char*)dlgElem->Attribute(NeoConstants::SCRIPT_ATTR_STOP_MUSIC);
	bool m_stopMusic = stopMusic == NULL?false:true;

	this->m_scriptLabel = new ZLabelTTF(lines, Utility::getDefaultScriptSize(), ZLabelTTF::FONT_COLOR_DEFAULT , ZLabelTTF::YAHEI, ZLabelTTF::FONT_DEFAULT_SIZE);
	
	//m_scriptLabel->addToCCNode(parentNode, 12);
}

void ZAutoDlg::zDlgLazyInit()
{	
	this->m_scriptState = ScriptState::NOT_FADED_IN;
	this->m_scriptLabel->resetIter();
	//this->addToCCNode(m_parentScriptLayer, 10);
}

int ZAutoDlg::getType()
{
	return NeoConstants::DLG_TYPE_AUTO;
}

bool ZAutoDlg::play(bool delay)
{
	if(this->m_scriptState == ScriptState::NOT_FADED_IN)
	{
		this->m_scriptLabel->resetIter();
		this->m_scriptState = ScriptState::SCRIPT_DONE;		
	}


	//when the background fades in, the cue is turned on, will need to turn it off when the scripts start to play.
	this->m_parentScriptLayer->switchCue(false);
	this->m_parentScriptLayer->setAnimationPlaying(true);
	m_scriptLabel->rollScript();

	Utility::playMusic((const char*)(this->m_musicName));

	return true;
}

ZAutoDlg::~ZAutoDlg(void)
{
}
