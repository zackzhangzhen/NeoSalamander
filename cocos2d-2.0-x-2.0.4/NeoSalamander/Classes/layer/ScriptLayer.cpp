
#include "ScriptLayer.h"
#include "script\ScriptPlayer.h"
#include "menu\ZMenu.h"
#include "scene\ZMainScene.h"
#include "menu\ZBackMenu.h"
ScriptLayer::ScriptLayer(ZMainScene* parentScene)
{

	/*CCSprite* spriteNormal1 = CCSprite::spriteWithFile("pic\\menu\\CloseNormal.png");
	CCSprite* spriteSelected1 = CCSprite::spriteWithFile("pic\\menu\\CloseSelected.png");
	CCSprite* spriteDisabled1 = CCSprite::spriteWithFile("pic\\menu\\CloseSelected.png");

	CCSprite* spriteNormal2 = CCSprite::spriteWithFile("pic\\menu\\CloseNormal.png");
	CCSprite* spriteSelected2 = CCSprite::spriteWithFile("pic\\menu\\CloseSelected.png");
	CCSprite* spriteDisabled2 = CCSprite::spriteWithFile("pic\\menu\\CloseSelected.png");

	CCMenuItemFont* menuItemStart = CCMenuItemFont::itemWithString("Start", this, menu_selector(ScriptLayer::menuCallback));  
	CCMenuItemFont* menuItemStart2 = CCMenuItemFont::itemWithString("Yes let's do this", this, menu_selector(ScriptLayer::menuCallback));  
	CCMenuItemFont* menuItemStart3 = CCMenuItemFont::itemWithString("Yes let's do that", this, menu_selector(ScriptLayer::menuCallback));  
	


	CCMenuItemSprite* item1 = CCMenuItemSprite::itemWithNormalSprite(spriteNormal1, spriteSelected1, spriteDisabled1, this, menu_selector(ScriptLayer::menuCallback));
	item1->setTag(10);
	CCMenuItemSprite* item2 = CCMenuItemSprite::itemWithNormalSprite(spriteNormal2, spriteSelected2, spriteDisabled2, this, menu_selector(ScriptLayer::menuCallback));
	item2->setTag(20);
	CCMenu* menu = CCMenu::menuWithItems( menuItemStart, menuItemStart2, menuItemStart3,NULL);


	menu->alignItemsVertically();

	 CCSize size = CCDirector::sharedDirector()->getWinSize();
	 menu->setPosition(ccp(size.width/2, size.height/2));


	this->addChild(menu,10);*/

	this->setTouchEnabled(true);
	this->m_isAnimationPlaying = false;
	this->m_isInOption = false;
	m_parentScene = parentScene;
	m_player = NULL;
	m_backMenu = new ZBackMenu(this, true);
	m_backMenu->init();
	initCueSprite();
	loadScript(NeoConstants::SCRIPT_FILE_LOC);
}

ZMainScene* ScriptLayer::getParentMainScene()
{
	return m_parentScene;
}

void ScriptLayer::menuCallback(CCObject* sender)
{
	/*CCMenuItemSprite* item = (CCMenuItemSprite*)sender;
	int i = item->getTag();
	int  j = 0;*/
}

ScriptLayer::~ScriptLayer(void)
{
}

void ScriptLayer::initCueSprite(void)
{
	m_cue = new ZSprite(Utility::zstrcat((char*)NeoConstants::CUE_PIC_LOC,"0.png"), this, 1);

	m_cue->addAnimation("cue",Utility::getAnimationAction((char*)NeoConstants::CUE_PIC_LOC,"png",5,true, true));
	m_cue->playAnimation("cue");
	m_cue->getSprite()->setVisible(true);

	//put it in the right bottom corner
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSize spriteSize = m_cue->getSize();
	m_cue->setPosition(ccp(size.width-spriteSize.width/2, spriteSize.height/2));
}

void ScriptLayer::switchCue(bool on)
{
	m_cue->getSprite()->setVisible(on);
}

void ScriptLayer::switchBackMenu(bool on)
{
	if(on)
	{
		this->m_backMenu->show();
	}
	else
	{
		this->m_backMenu->hide();
	}
}

void ScriptLayer::loadScript(const char* fileName)
{

	TiXmlElement* pElem = Utility::getRootElementFromFile(fileName);

	TiXmlElement* scriptElem = pElem->FirstChildElement();

	assert(scriptElem != NULL);

	bool firstScriptPlayer = true;
	
	for( ; scriptElem != NULL; scriptElem=scriptElem->NextSiblingElement())
	{
		char* id = (char*)scriptElem->Attribute("id");

		ScriptPlayer* player = new ScriptPlayer(id, scriptElem, this);
		
		if(firstScriptPlayer)
		{
			this->m_player = player;
			firstScriptPlayer = false;
		}

		m_map.insert(map<char*, ScriptPlayer*>::value_type((char*)id, player));
	}
}

/*void ScriptLayer::initScripts()
{
	//==========================================================
	vector<ZDlg*> vec1;

	vector<char*> charVec;
	charVec.push_back("你好呀，大家都过来做一个简单的自我介绍好不好呀啊？");
	charVec.push_back("其实没什么别的意思，我就是想测试一下剧本播放器");
	charVec.push_back("有木有发现我现在在说着中文呢？");
	ZDlg* dlg = new ZDlg(ZDlg::POS_LEFT, charVec, "pic\\figure\\assassin.png", this, ZLabelTTF::YAHEI);
	//ZDlg* dlg = new ZDlg(ZDlg::POS_RIGHT, "Fine thank you! My name is Li Lei, what about you?", "pic\\figure\\master_chief.png", this);
	vec1.push_back(dlg);

	vector<char*> charVec2;
	charVec2.push_back("我是说英文的知道呢吗");
	charVec2.push_back("Fine thank you! My name is Li Lei, what about you?");
	charVec2.push_back("This is a very brief self-introduction!");
	dlg = new ZDlg(ZDlg::POS_RIGHT, charVec2, "pic\\figure\\master_chief.png", this);
	vec1.push_back(dlg);

	dlg = new ZDlg(ZDlg::POS_LEFT, "My name is Han Meimei, nice to meet you!", "pic\\figure\\assassin.png", this);
	vec1.push_back(dlg);

	dlg = new ZDlg(ZDlg::POS_FULL, "Hi there, my name is Jim Green, don't forget me!", "pic\\figure\\jedi.png", this);
	vec1.push_back(dlg);

	ScriptPlayer* player = new ScriptPlayer("s1", vec1);

	m_map.insert(map<char*, ScriptPlayer*>::value_type((char*)"s1",player));
	//==========================================================
	vector<ZDlg*> vec2;

	dlg = new ZDlg(ZDlg::POS_LEFT, "What are you going to do now?", "pic\\figure\\jedi.png", this);
	vec2.push_back(dlg);

	dlg = new ZDlg(ZDlg::POS_RIGHT, "I'm going to play Halo 4!", "pic\\figure\\assassin.png", this);
	vec2.push_back(dlg);

	dlg = new ZDlg(ZDlg::POS_LEFT, "Oh, I was just done playing it!", "pic\\figure\\jedi.png", this);
	vec2.push_back(dlg);

	dlg = new ZDlg(ZDlg::POS_FULL, "Ok, I get it, now get lost!", "pic\\figure\\master_chief.png", this);
	vec2.push_back(dlg);

	player = new ScriptPlayer("s2", vec2);
	m_map.insert(map<char*, ScriptPlayer*>::value_type((char*)"s2",player));
	//==========================================================


	m_player = findScriptPlayerByKey("s1");
}*/

ScriptPlayer* ScriptLayer::findScriptPlayerByKey(char* key)
{
	assert(key != NULL);

	map<char*, ScriptPlayer*, CompareCString>::const_iterator iter = m_map.find(key);

	assert(iter != m_map.end());

	return iter->second;
}
void ScriptLayer::setCurrentScriptPlayer(ScriptPlayer* player)
{
	this->m_player = player;
}
void ScriptLayer::setNextScriptPlayerAsync(char* id)
{
	if(id != NULL)// if for some reason the id was not configured for this option, just ignore and go on rolling the script
	{
		this->m_player->setNextScriptPlayerId(id);
	}
	
}

void ScriptLayer::play()
{
	this->m_player->play();
}

void ScriptLayer::refresh(char* strId)
{
	resetCurrentScriptPlayer(strId);

	this->setInOption(false);
	this->setAnimationPlaying(false);
	this->switchBackMenu(true);
	this->switchCue(true);
}

void ScriptLayer::resetCurrentScriptPlayer(char* idStr)
{
	ScriptPlayer* scriptPlayer = this->findScriptPlayerByKey(idStr);
	scriptPlayer->refresh();

	this->setCurrentScriptPlayer(scriptPlayer);
}

ScriptPlayer* ScriptLayer::getCurrentScriptPlayer()
{
	return this->m_player;
}

void ScriptLayer::jumpToLine(char* lineId)
{
	assert(m_player != NULL);
	m_player->jumpToLine(lineId);
}

void ScriptLayer::setNextScriptPlayerSync(char* id)
{	
	fadeOutCurrentScript();
	if(id != NULL)// if for some reason the id was not configured for this option, just ignore and move on to the currently configured script
	{
		m_player = findScriptPlayerByKey(id);
		//set delay to true to wait for the cut-off dlg to fade out
		m_player->play(true);
	}		
}

void ScriptLayer::fadeOutCurrentScript()
{
	assert(m_player != NULL);
	m_player->fadeOut(false);
}

void ScriptLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	if(this->isAnimationPlaying() ||
		this->isInOption())
	{
		return;
	}

	if(m_player->play())
	{
		char* nextScriptId = m_player->getNextScriptPlayerId();
		if(nextScriptId != NULL)
		{
			m_player = findScriptPlayerByKey(nextScriptId);
		}		
		//this->setAnimationPlaying(false);
	}
}

bool ScriptLayer::isAnimationPlaying()
{
	return this->m_isAnimationPlaying;
}

void ScriptLayer::setAnimationPlaying(bool playing)
{
	this->m_isAnimationPlaying = playing;
}

bool ScriptLayer::isInOption()
{
	return this->m_isInOption;
}

void ScriptLayer::setInOption(bool inOption)
{
	this->m_isInOption = inOption;
}