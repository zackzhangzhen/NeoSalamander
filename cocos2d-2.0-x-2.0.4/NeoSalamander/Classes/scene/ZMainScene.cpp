#include "scene\ZMainScene.h"
#include "layer\ScriptLayer.h"

ZMainScene::ZMainScene(ZSceneMgr* sceneMgr):ZScene(sceneMgr)
{
}

void ZMainScene::init()
{
	m_scene = CCScene::create();
	m_layer = new ScriptLayer(this);
	m_scene->addChild(m_layer, 10);

	m_sceneName = (char*)NeoConstants::SCENE_NAME_MAIN;
}

ZMainScene::~ZMainScene(void)
{
}
