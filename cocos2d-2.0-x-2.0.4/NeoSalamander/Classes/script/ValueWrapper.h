#pragma once
#include "script\ScriptElement.h"
#include "menu\tinyxml.h"
#include "NeoConstants.h"
#include "script\ZLabelTTF.h"
class ValueWrapper : public ScriptElement
{
public:
	ValueWrapper(char*, char*);
	ValueWrapper(TiXmlElement* autolinesElem);
	~ValueWrapper(void);
	char* getLineId();
	char* getToLineId();
	virtual char* getText();
	char* getFont();
	int getSize();
	int getColorCode();
	char* getSound();
	char* getMusic();
private:
	char* m_text;
	char* m_lineId;
	char* m_font;
	int m_size;
	int m_colorCode;
	char* m_sound;
	char* m_music;
	char* m_toLineId;
};

