#include "ValueWrapper.h"


ValueWrapper::ValueWrapper(char* text) : ScriptElement(ScriptElementType::LINE)
{
	this->m_text = text;
}

char* ValueWrapper::getText()
{
	return m_text;
}

ValueWrapper::~ValueWrapper(void)
{
}
