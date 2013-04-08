#include "ValueWrapper.h"


ValueWrapper::ValueWrapper(char* lineId, char* text) : ScriptElement(ScriptElementType::LINE)
{
	this->m_lineId = lineId;
	this->m_text = text;
}

ValueWrapper::ValueWrapper(TiXmlElement* lineElem) : ScriptElement(ScriptElementType::LINE)
{
	char* line = (char*)lineElem->GetText();
	char* lineId = (char*)lineElem->Attribute(NeoConstants::SCRIPT_ATTR_ID);

	char* toLineId = (char*)lineElem->Attribute(NeoConstants::TO_LINE_ID);

	int size = ZLabelTTF::FONT_DEFAULT_SIZE;
	lineElem->Attribute(NeoConstants::SCRIPT_ATTR_SIZE, &size);

	int colorCode = ZLabelTTF::FONT_COLOR_DEFAULT;
	lineElem->Attribute(NeoConstants::SCRIPT_ATTR_COLOR, &colorCode);

	char* font = (char*)lineElem->Attribute(NeoConstants::SCRIPT_ATTR_FONT);
	if(font == NULL)
	{
		font = ZLabelTTF::YAHEI;
	}

	char* sound = (char*)lineElem->Attribute(NeoConstants::SCRIPT_ATTR_SOUND);

	char* music = (char*)lineElem->Attribute(NeoConstants::SCRIPT_ATTR_MUSIC);
	
	this->m_lineId = lineId;
	this->m_toLineId = toLineId;
	this->m_text = line;
	this->m_font = font;
	this->m_size = size;
	this->m_colorCode = colorCode;
	this->m_sound = sound;
	this->m_music = music;
}


char* ValueWrapper::getFont()
{
	return this->m_font;
}
int ValueWrapper::getSize()
{
	return this->m_size;
}
int ValueWrapper::getColorCode()
{
	return this->m_colorCode;
}
char* ValueWrapper::getSound()
{
	return this->m_sound;
}

char* ValueWrapper::getMusic()
{
	return this->m_music;
}

char* ValueWrapper::getLineId()
{
	return m_lineId;
}

char* ValueWrapper::getToLineId()
{
	return m_toLineId;
}


char* ValueWrapper::getText()
{
	return m_text;
}

ValueWrapper::~ValueWrapper(void)
{
}
