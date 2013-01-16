#pragma once
#include <string>
class CompareCString
{
public:
	CompareCString(void);
	~CompareCString(void);
	bool operator()(const char* one,const char* two);
};

