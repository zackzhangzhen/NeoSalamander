#include "ZScene.h"


ZScene::ZScene(void)
{
}

char* ZScene::getSceneName()
{
	return m_sceneName;
}

void ZScene::runByDirector(CCDirector* pDirector)
{
	assert(pDirector != NULL);
	pDirector->runWithScene(this->m_scene);
}

ZScene::~ZScene(void)
{
}
