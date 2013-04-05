#pragma once
class AutoScriptAttrHolder
{
public:
	AutoScriptAttrHolder(int preBlank, int fadeInTime, int presentTime, int fadeOutTime, int postBlank);
	~AutoScriptAttrHolder(void);
	int getPreBlank();
	int getFadeInTime();
	int getPresentTime();
	int getFadeOutTime();
	int getPostBlank();

private:
	int m_preBlank;
	int m_fadeInTime;
	int m_presentTime;
	int m_fadeOutTime;
	int m_postBlank;
};

