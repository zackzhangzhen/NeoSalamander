#pragma once
#include "scene\ZScene.h"

class ScriptLayer;
class ZMainScene : public ZScene
{
public:
	ZMainScene(ZSceneMgr*);
	void refresh(char* idStr);
	virtual void init();
	~ZMainScene(void);
};

