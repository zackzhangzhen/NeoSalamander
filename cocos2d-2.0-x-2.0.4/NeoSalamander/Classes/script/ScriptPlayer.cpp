#include "ScriptPlayer.h"


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

	for( ; dlgElem != NULL; dlgElem=dlgElem->NextSiblingElement())
	{
		ZDlg* dlg = new ZDlg(dlgElem, parentNode);
		m_vec.push_back(dlg);
	}

	this->m_id = id;
	m_iter = m_vec.begin();
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

