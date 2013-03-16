#include "ZTitleScene.h"
#include "layer\ObjectLayer.h"
#include "menu\ZGameMenuContainer.h"

ZTitleScene::ZTitleScene(ZSceneMgr* sceneMgr):ZScene(sceneMgr)
{
}

void ZTitleScene::init()
{
	m_menuContainer = new ZGameMenuContainer(this->getSceneMgr());

	m_layer = ObjectLayer::createObjectLayer(this);
	ObjectLayer* objLayer = (ObjectLayer*)m_layer;
	objLayer->scheduleObjects();
	objLayer->addGameMenu();

	m_scene = CCScene::create();

	m_scene->addChild(objLayer,1);

	m_sceneName = (char*)NeoConstants::SCENE_NAME_TITLE;
}

ZGameMenuContainer* ZTitleScene::getMenuContainer()
{
	return this->m_menuContainer;
}

ZTitleScene::~ZTitleScene(void)
{
}
