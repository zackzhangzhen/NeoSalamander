#pragma once
#include "cocos2d.h"
#include "CCEGLView.h"

using namespace cocos2d;

class ZSceneMgr;
class ZScene
{
public:
	ZScene(ZSceneMgr*);
	void virtual init() = 0;
	void runByDirector(CCDirector* pDirector);
	char* getSceneName();
	ZSceneMgr* getSceneMgr();
	CCLayer* getLayer();
	CCScene* getScene();
	~ZScene(void);

protected:
	CCScene* m_scene;
	ZSceneMgr* m_sceneMgr;
	char* m_sceneName;
	CCLayer* m_layer;
};

