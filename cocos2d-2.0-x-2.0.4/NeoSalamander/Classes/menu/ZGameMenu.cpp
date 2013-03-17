#include "ZGameMenu.h"


ZGameMenu::ZGameMenu(CCNode* parentNode, bool visible) : ScriptElement(ScriptElementType::OPTIONS)
{
	assert(parentNode != NULL);

	
	this->m_parentLayer = (CCLayer*)parentNode;
	this->m_visible = visible;
}

CCLayer* ZGameMenu::getParentLayer()
{
	return m_parentLayer;
}

void ZGameMenu::show()
{
	this->m_menu->setVisible(true);
}

void ZGameMenu::hide()
{
	this->m_menu->setVisible(false);
}


ZGameMenu::~ZGameMenu(void)
{
}
