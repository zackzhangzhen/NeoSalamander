#include "scene\ZScene.h"
#include "scene\ZSceneMgr.h"
ZScene::ZScene(ZSceneMgr* sceneMgr)
{
	this->m_sceneMgr = sceneMgr;
}

ZSceneMgr* ZScene::getSceneMgr()
{
	return this->m_sceneMgr;
}

CCLayer* ZScene::getLayer()
{
	return m_layer;
}

char* ZScene::getSceneName()
{
	return m_sceneName;
}

CCScene* ZScene::getScene()
{
	return m_scene;
}

void ZScene::runByDirector(CCDirector* pDirector)
{
	assert(pDirector != NULL);
	pDirector->runWithScene(this->m_scene);
}

ZScene::~ZScene(void)
{
}
