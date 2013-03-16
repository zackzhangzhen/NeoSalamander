#pragma once
#include "scene\ZScene.h"

class ScriptLayer;
class ZMainScene : public ZScene
{
public:
	ZMainScene(ZSceneMgr*);
	virtual void init();
	~ZMainScene(void);
};

