#pragma once


enum ScriptElementType{
	LINE,
	OPTIONS
};

class ScriptElement
{
public:
	ScriptElement(ScriptElementType);
	bool isType(ScriptElementType);
	virtual char* getText() = 0;
	~ScriptElement(void);

private:
	ScriptElementType m_type;

};

