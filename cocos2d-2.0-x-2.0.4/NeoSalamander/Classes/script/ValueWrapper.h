#pragma once
#include "ScriptElement.h"
class ValueWrapper : public ScriptElement
{
public:
	ValueWrapper(char*, char*);
	~ValueWrapper(void);
	char* getLineId();
	virtual char* getText();

private:
	char* m_text;
	char* m_lineId;
};

