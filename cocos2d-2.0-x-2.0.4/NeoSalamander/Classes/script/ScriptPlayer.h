#pragma once
#include "script\ZDlg.h"
#include <vector>
#include "tinyxml.h"
class ScriptPlayer
{
public:
	ScriptPlayer(char* id, vector<ZDlg*>& vec);
	ScriptPlayer(const char* id, TiXmlElement* scriptElem);
	~ScriptPlayer(void);
	bool play();
	char* getId();
private:
	vector<ZDlg*> m_vec;
	vector<ZDlg*>::const_iterator m_iter;
	char* m_id;
};


