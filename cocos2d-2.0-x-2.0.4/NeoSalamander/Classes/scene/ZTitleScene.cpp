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

	m_scene = CCScene::create();

	m_scene->addChild(objLayer,1);

	m_menuContainer = new ZGameMenuContainer(this->getSceneMgr());
	
}

void ZTitleScene::switchMainLoadMenu(bool mainOn)
{
	ZGameMenuContainer* container = this->getMenuContainer();
	ZLoadMenu* loadMenu = container->getLoadMenu();
	ZMainMenu* mainMenu = container->getMainMenu();
	if(mainOn)
	{
		loadMenu->hide();
		mainMenu->show();
	}
	else
	{
		loadMenu->show();
		mainMenu->hide();
	}

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
