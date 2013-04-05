#include "AutoScriptAttrHolder.h"


AutoScriptAttrHolder::AutoScriptAttrHolder(int preBlank, int fadeInTime, int presentTime, int fadeOutTime, int postBlank)
{
	this->m_preBlank = preBlank;
	this->m_fadeInTime = fadeInTime;
	this->m_presentTime = presentTime;
	this->m_fadeOutTime = fadeOutTime;
	this->m_postBlank = postBlank;
}

int AutoScriptAttrHolder::getPreBlank()
{
	return m_preBlank;
}

int AutoScriptAttrHolder::getFadeInTime()
{
	return m_fadeInTime;
}

int AutoScriptAttrHolder::getPresentTime()
{
	return m_presentTime;
}

int AutoScriptAttrHolder::getFadeOutTime()
{
	return m_fadeOutTime;
}

int AutoScriptAttrHolder::getPostBlank()
{
	return m_postBlank;
}

AutoScriptAttrHolder::~AutoScriptAttrHolder(void)
{
}
