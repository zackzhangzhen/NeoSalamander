#include "scene\ZMainScene.h"
#include "layer\ScriptLayer.h"

ZMainScene::ZMainScene(ZSceneMgr* sceneMgr):ZScene(sceneMgr)
{
	m_sceneName = (char*)NeoConstants::SCENE_NAME_MAIN;
}

void ZMainScene::init()
{
	m_scene = CCScene::create();
	CCDirector::sharedDirector()->pushScene(m_scene);
	m_layer = new ScriptLayer(this);
	m_scene->addChild(m_layer, 10);

	
}

ZMainScene::~ZMainScene(void)
{
}
