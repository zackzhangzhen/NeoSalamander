#pragma once
#include "ScriptElement.h"
class ValueWrapper : public ScriptElement
{
public:
	ValueWrapper(char*);
	~ValueWrapper(void);
	virtual char* getText();

private:
	char* m_text;
};

