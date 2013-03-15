#pragma once
#include "cocos2d.h"
#include "CCEGLView.h"
#include "scene\ZScene.h"
#include "utility\CompareCString.h"
#include <map>
using namespace cocos2d;
using namespace std;
class ZSceneMgr
{
public:
	ZSceneMgr(void);
	void addScene(char*, ZScene*);
	ZScene* getScene(char*);
	~ZSceneMgr(void);



private:
	std::map<char*, ZScene*, CompareCString> m_map;

};

