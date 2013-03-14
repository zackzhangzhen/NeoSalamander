#include "ZGameMenu.h"
#include "layer\ScriptLayer.h"


ZGameMenu::ZGameMenu(CCNode* parentNode, bool visible) : ScriptElement(ScriptElementType::OPTIONS)
{
	assert(parentNode != NULL);

	
	this->m_parentScriptLayer = (ScriptLayer*)parentNode;
	this->m_visible = visible;
}

ScriptLayer* ZGameMenu::getParentScriptLayer()
{
	return m_parentScriptLayer;
}

void ZGameMenu::show()
{
	this->m_menu->setVisible(true);
	this->m_parentScriptLayer->setInOption(true);
}

void ZGameMenu::hide()
{
	this->m_menu->setVisible(false);
	this->m_parentScriptLayer->setInOption(false);
}


ZGameMenu::~ZGameMenu(void)
{
}
