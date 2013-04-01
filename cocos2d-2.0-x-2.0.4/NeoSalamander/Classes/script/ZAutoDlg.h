#pragma once
#include "script\ZDlg.h"
#include "menu\tinyxml.h"
#include "utility\Utility.h"
class ScriptLayer;
class ZLabelTTF;
class ZAutoDlg : public ZDlg
{
public:
	ZAutoDlg(TiXmlElement* dlgElem, CCNode* parentNode);
	bool play(bool delay);
	~ZAutoDlg(void);
};

