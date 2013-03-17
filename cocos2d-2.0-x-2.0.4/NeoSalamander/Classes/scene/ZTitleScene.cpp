#include "ZTitleScene.h"
#include "layer\ObjectLayer.h"
#include "menu\ZGameMenuContainer.h"

ZTitleScene::ZTitleScene(ZSceneMgr* sceneMgr):ZScene(sceneMgr)
{
	m_sceneName = (char*)NeoConstants::SCENE_NAME_TITLE;
}

void ZTitleScene::init()
{
	

	m_layer = ObjectLayer::createObjectLayer(this);
	ObjectLayer* objLayer = (ObjectLayer*)m_layer;
	objLayer->scheduleObjects();
	objLayer->addGameMenu();

	m_scene = CCScene::create();

	m_scene->addChild(objLayer,1);

	m_menuContainer = new ZGameMenuContainer(this->getSceneMgr());
	
}

ZGameMenuContainer* ZTitleScene::getMenuContainer()
{
	return this->m_menuContainer;
}

ObjectLayer* ZTitleScene::getObjectLayer()
{
	return (ObjectLayer*)this->m_layer;
}

ZTitleScene::~ZTitleScene(void)
{
}
