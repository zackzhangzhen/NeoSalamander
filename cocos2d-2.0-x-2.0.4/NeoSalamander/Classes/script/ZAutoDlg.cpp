#include "ZAutoDlg.h"
#include "layer\ScriptLayer.h"
#include "script\ZLabelTTF.h"
ZAutoDlg::ZAutoDlg(TiXmlElement* dlgElem, CCNode* parentNode): ZDlg()
{
	m_parentScriptLayer = (ScriptLayer*)parentNode;

	TiXmlElement* lineElem = dlgElem->FirstChildElement();
	assert(lineElem != NULL);

	vector<ScriptElement*> lines = Utility::createLines(lineElem, this->m_parentScriptLayer);

	this->m_scriptLabel = new ZLabelTTF(lines, Utility::getDefaultScriptSize(), ZLabelTTF::FONT_COLOR_DEFAULT , ZLabelTTF::YAHEI, ZLabelTTF::FONT_DEFAULT_SIZE);
	
	m_scriptLabel->addToCCNode(parentNode, 12);
}

bool ZAutoDlg::play(bool delay)
{
	//when the background fades in, the cue is turned on, will need to turn it off when the scripts start to play.
	this->m_parentScriptLayer->switchCue(false);

	m_scriptLabel->rollScript();

	return true;
}

ZAutoDlg::~ZAutoDlg(void)
{
}
