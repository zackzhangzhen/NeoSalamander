#include "ZMainScene.h"


ZMainScene::ZMainScene(void)
{
}

void ZMainScene::init()
{
	m_scene = CCScene::create();
	m_scene->addChild(new ScriptLayer(), 10);

	m_sceneName = (char*)NeoConstants::SCENE_NAME_MAIN;
}

ZMainScene::~ZMainScene(void)
{
}
