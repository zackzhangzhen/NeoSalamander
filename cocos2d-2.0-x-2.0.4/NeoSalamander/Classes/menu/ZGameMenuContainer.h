#pragma once
#include <iostream>
#include "ZGameMenu.h"
using namespace std;
class ZGameMenuContainer
{
public:
	
	static ZGameMenuContainer& getInstance();

	~ZGameMenuContainer(void);

	

private:
	ZGameMenuContainer(void);
	static void init();
	static map<int, ZGameMenu*> m_optionMap;
};

