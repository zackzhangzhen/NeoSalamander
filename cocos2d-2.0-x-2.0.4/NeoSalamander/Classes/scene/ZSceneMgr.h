#pragma once
#include "cocos2d.h"
#include "CCEGLView.h"

#include "utility\CompareCString.h"
#include "scene\ZTitleScene.h"
#include "scene\ZMainScene.h"
#include "NeoConstants.h"
#include <map>
using namespace cocos2d;
using namespace std;
class ZScene;
class ScriptLayer;
class ObjectLayer;
class ZSceneMgr
{
public:
	ZSceneMgr(CCDirector* pDirector);
	void addScene(char*, ZScene*);
	ZScene* getScene(const char*);
	ZScene* getTitleScene();
	ZScene* getMainScene();
	ScriptLayer* getScriptLayer();
	ObjectLayer* getObjectLayer();
	void init();
	void runScene(const char* key);
	void runTitleScene();
	void runMainScene();
	~ZSceneMgr(void);

private:
	std::map<char*, ZScene*, CompareCString> m_map;
	CCDirector* m_director;

};

