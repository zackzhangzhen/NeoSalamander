#pragma once
#include <windows.h>
class GlobalFlag
{
public:
	static CRITICAL_SECTION m_csObject;
	
	~GlobalFlag(void);

private:
	GlobalFlag(void);
};

