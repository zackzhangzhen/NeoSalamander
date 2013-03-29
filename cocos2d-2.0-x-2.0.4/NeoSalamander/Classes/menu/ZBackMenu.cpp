#include "menu\ZBackMenu.h"


ZBackMenu::ZBackMenu(CCNode* parentNode, bool visible): ZGameMenu(parentNode, visible)
{

}

void ZBackMenu::optionCallback(CCObject* sender)
{

	CCMenuItemImage* item = (CCMenuItemImage*)sender;
	ZBackMenu* menu = (ZBackMenu*)item->getUserObject();
	ScriptLayer* scriptLayer = (ScriptLayer*)menu->getParentLayer();
	scriptLayer->fadeOutCurrentScriptInstantly();
	ZMainScene* mainScene = scriptLayer->getParentMainScene();
	ZSceneMgr* sceneMgr = mainScene->getSceneMgr();

	ZTitleScene* titleScene = (ZTitleScene*)sceneMgr->getTitleScene();
	//titleScene->switchMainLoadMenu(true);
	
	Utility::playSound(NeoConstants::DEFAULT_SOUND_NAME);

	Utility::replaceMainWithTitleScene(sceneMgr);
}

void ZBackMenu::init()
{
	CCMenu* menu = NULL;

	CCMenuItemImage* menuItem = CCMenuItemImage::itemWithNormalImage(NeoConstants::BACK_MENU_NORMAL_IMAGE_PATH,NeoConstants::BACK_MENU_SELECTED_IMAGE_PATH,this,menu_selector(ZBackMenu::optionCallback));

	if(menu == NULL)
	{
		menu = CCMenu::menuWithItem(menuItem);

	}
	else
	{
		menu->addChild(menuItem);
	}
	menu->setUserObject(this);
	menuItem->setUserObject(this);


	//set position to center

	menu->setPosition(getPos());
	menu->alignItemsVertically();

	this->m_menu = menu;

	this->m_parentLayer->addChild(this->m_menu, 11);
	this->m_menu->setVisible(this->m_visible);
}

CCPoint ZBackMenu::getPos()
{
	CCPoint topRightPt = Utility::getTopRightPt();
	topRightPt.x = topRightPt.x - BACK_MENU_WIDTH;
	topRightPt.y = topRightPt.y - BACK_MENU_HEIGHT;

	return topRightPt;
}

ZBackMenu::~ZBackMenu(void)
{
}
