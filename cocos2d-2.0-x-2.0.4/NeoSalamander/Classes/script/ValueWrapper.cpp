#include "ValueWrapper.h"


ValueWrapper::ValueWrapper(char* lineId, char* text) : ScriptElement(ScriptElementType::LINE)
{
	this->m_lineId = lineId;
	this->m_text = text;
}

char* ValueWrapper::getLineId()
{
	return m_lineId;
}


char* ValueWrapper::getText()
{
	return m_text;
}

ValueWrapper::~ValueWrapper(void)
{
}
