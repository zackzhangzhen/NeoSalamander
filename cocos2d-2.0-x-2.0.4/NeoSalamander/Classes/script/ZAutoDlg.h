#pragma once
#include "script\ZDlg.h"
#include "menu\tinyxml.h"
#include "utility\Utility.h"
class ScriptLayer;
class ZLabelTTF;
class ZAutoDlg : public ZDlg
{
public:
	ZAutoDlg(TiXmlElement* dlgElem, CCNode* parentNode, ScriptPlayer* parentPlayer);
	bool play(bool delay);
	void zDlgLazyInit();
	int getType();
	~ZAutoDlg(void);

};

