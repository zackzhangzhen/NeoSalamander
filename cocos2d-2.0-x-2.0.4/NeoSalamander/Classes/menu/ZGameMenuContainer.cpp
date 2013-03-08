#include "ZGameMenuContainer.h"
#include "ZMainMenu.h"

map<int, ZGameMenu*> ZGameMenuContainer::m_optionMap;

ZGameMenuContainer::ZGameMenuContainer(void)
{

}

ZGameMenuContainer& ZGameMenuContainer::getInstance()
{
	static ZGameMenuContainer instance;
	return instance;
}

void ZGameMenuContainer::init()
{
	m_optionMap.insert(make_pair(0 ,new ZMainMenu(NULL, NULL, false)));
}

ZGameMenuContainer::~ZGameMenuContainer(void)
{
}
