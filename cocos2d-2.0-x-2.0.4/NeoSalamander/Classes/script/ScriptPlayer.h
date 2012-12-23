#pragma once
#include "script\ZDlg.h"
#include <vector>
class ScriptPlayer
{
public:
	ScriptPlayer(char* id, vector<ZDlg*>& vec);
	~ScriptPlayer(void);
	bool play();
	char* getId();
private:
	vector<ZDlg*> m_vec;
	vector<ZDlg*>::const_iterator m_iter;
	char* m_id;
};


