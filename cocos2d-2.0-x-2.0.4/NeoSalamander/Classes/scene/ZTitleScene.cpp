#include "ZTitleScene.h"


ZTitleScene::ZTitleScene(void)
{
}

void ZTitleScene::init()
{
	ObjectLayer* l = ObjectLayer::createObjectLayer();
	l->scheduleObjects();
	l->addGameMenu();

	m_scene = CCScene::create();

	m_scene->addChild(l,1);

	m_sceneName = (char*)NeoConstants::SCENE_NAME_TITLE;
}

ZTitleScene::~ZTitleScene(void)
{
}
