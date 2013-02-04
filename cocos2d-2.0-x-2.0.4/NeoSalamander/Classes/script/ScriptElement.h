#pragma once
#include "cocos2d.h"

enum ScriptElementType{
	LINE,
	OPTIONS
};

class ScriptElement : public cocos2d::CCObject
{
public:
	ScriptElement(ScriptElementType);
	bool isType(ScriptElementType);
	virtual char* getText();
	~ScriptElement(void);

private:
	ScriptElementType m_type;

};

