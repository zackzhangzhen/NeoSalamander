#include "CompareCString.h"


CompareCString::CompareCString(void)
{
}


CompareCString::~CompareCString(void)
{
}

bool CompareCString::operator()(const char* lhs,const char* rhs) 
{ return strcmp(lhs,rhs)>0; };
