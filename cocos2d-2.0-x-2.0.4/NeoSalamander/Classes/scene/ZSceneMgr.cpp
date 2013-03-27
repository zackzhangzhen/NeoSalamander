#include "ZSceneMgr.h"
#include "scene\ZScene.h"
#include "layer\ScriptLayer.h"
#include "layer\ObjectLayer.h"
ZSceneMgr::ZSceneMgr(CCDirector* pDirector)
{
	m_director = pDirector;
	init();
}

void ZSceneMgr::addScene(char* key, ZScene* scene)
{
	m_map.insert(map<char*, ZScene*>::value_type(key, scene));
}

void ZSceneMgr::init()
{
	ZScene* pTitleScene = new ZTitleScene(this);
	//need to call addScene before pTitleScene->init() otherwise ZGameMenuContainer::init() called by the latter won't find the scene in the map
	addScene(pTitleScene->getSceneName(), pTitleScene);
	pTitleScene->init();

	ZScene* pMainScene = new ZMainScene(this);
	addScene(pMainScene->getSceneName(), pMainScene);
	pMainScene->init();
	
}

void ZSceneMgr::runScene(const char* key)
{
	ZScene* pScene = getScene(key);

	pScene->runByDirector(m_director);
}

void ZSceneMgr::runTitleScene()
{
	runScene(NeoConstants::SCENE_NAME_TITLE);
}

void ZSceneMgr::runMainScene()
{
	runScene(NeoConstants::SCENE_NAME_MAIN);
}

ZScene* ZSceneMgr::getScene(const char* key)
{
	map<char*, ZScene*, CompareCString>::const_iterator iter = m_map.find((char*)key);
		
	assert(iter != m_map.end());

	return iter->second;
}

ZScene* ZSceneMgr::getTitleScene()
{
	return getScene(NeoConstants::SCENE_NAME_TITLE);
}

ZScene* ZSceneMgr::getMainScene()
{
	return getScene(NeoConstants::SCENE_NAME_MAIN);
}

ScriptLayer* ZSceneMgr::getScriptLayer()
{
	ZScene* mainScene = getMainScene();
	return (ScriptLayer*)mainScene->getLayer();
}

void ZSceneMgr::refreshMainScene(char* idStr)
{
	ZMainScene* mainScene = (ZMainScene*)getMainScene();
	return mainScene->refresh(idStr);
}

ObjectLayer* ZSceneMgr::getObjectLayer()
{
	ZScene* titleScene = getTitleScene();
	return (ObjectLayer*)titleScene->getLayer();
}

ZSceneMgr::~ZSceneMgr(void)
{
}
