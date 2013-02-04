#include "ScriptElement.h"


ScriptElement::ScriptElement(ScriptElementType type)
{
	this->m_type = type;
}

bool ScriptElement::isType(ScriptElementType type)
{
	return m_type == type;
}

char* ScriptElement::getText()
{
	return NULL;
}

ScriptElement::~ScriptElement(void)
{
}
