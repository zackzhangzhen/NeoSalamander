#include "ZSceneMgr.h"


ZSceneMgr::ZSceneMgr(void)
{
}

void ZSceneMgr::addScene(char* key, ZScene* scene)
{
	m_map.insert(map<char*, ZScene*>::value_type(key, scene));
}

ZScene* ZSceneMgr::getScene(char* key)
{
	map<char*, ZScene*, CompareCString>::const_iterator iter = m_map.find(key);
		
	assert(iter != m_map.end());

	return iter->second;
}

ZSceneMgr::~ZSceneMgr(void)
{
}
