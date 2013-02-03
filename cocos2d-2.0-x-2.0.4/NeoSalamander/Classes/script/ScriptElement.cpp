#include "ScriptElement.h"


ScriptElement::ScriptElement(ScriptElementType type)
{
	this->m_type = type;
}

bool ScriptElement::isType(ScriptElementType type)
{
	return m_type == type;
}

ScriptElement::~ScriptElement(void)
{
}
