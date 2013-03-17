#pragma once
#include "scene\ZScene.h"
#include "scene\ZSceneMgr.h"
class ObjectLayer;
class ZGameMenuContainer;
class ZTitleScene : public ZScene
{
public:
	ZTitleScene(ZSceneMgr*);
	virtual void init();	
	ZGameMenuContainer* getMenuContainer();
	ObjectLayer* getObjectLayer();
	~ZTitleScene(void);

private:
	ZGameMenuContainer* m_menuContainer;
};

