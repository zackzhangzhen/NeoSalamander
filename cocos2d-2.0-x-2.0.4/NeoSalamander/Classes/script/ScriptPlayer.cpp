#include "ScriptPlayer.h"


ScriptPlayer::ScriptPlayer(char* id, vector<ZDlg*>& vec)
{
	this->m_id = id;
	this->m_vec = vec;

	m_iter = m_vec.begin();
}

ScriptPlayer::ScriptPlayer(const char* id, TiXmlElement* scriptElem)
{
	TiXmlElement* dlgElem = scriptElem->FirstChildElement();
	assert(dlgElem != NULL);

	for( ; dlgElem != NULL; dlgElem=dlgElem->NextSiblingElement())
	{
		const char* id = scriptElem->Attribute("id");
		ScriptPlayer* player = new ScriptPlayer(id, scriptElem);

		//ZDlg* dlg = new ZDlg(ZDlg::POS_LEFT, charVec, "pic\\figure\\assassin.png", this, ZLabelTTF::YAHEI);
	}
	
}

ScriptPlayer::~ScriptPlayer(void)
{
}

char* ScriptPlayer::getId()
{
	return m_id;
}

bool ScriptPlayer::play()
{
	if(m_iter != m_vec.end())
	{
		ZDlg* dlg = *m_iter;

		if(dlg->play(false))
		{
			m_iter++;

			if(m_iter != m_vec.end())
			{
				dlg = *m_iter;
				dlg->play(true);
				return false;
			}
			return true;
		}

		return false;
	}
	else
	{
		return true;
	}
}

