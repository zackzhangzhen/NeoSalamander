#pragma once
#include "cocos2d.h"
#include "CCEGLView.h"
using namespace cocos2d;
class ZScene
{
public:
	ZScene(void);
	void virtual init() = 0;
	void runByDirector(CCDirector* pDirector);
	char* getSceneName();
	~ZScene(void);

protected:
	CCScene* m_scene;
	char* m_sceneName;
};

