
#include "ScriptLayer.h"
#include "script\ScriptPlayer.h"



ScriptLayer::ScriptLayer(void)
{
	this->setTouchEnabled(true);
	this->m_isAnimationPlaying = false;
	m_player = NULL;
	loadScript("script\\script.xml");
}


ScriptLayer::~ScriptLayer(void)
{
}


void ScriptLayer::loadScript(const char* fileName)
{
	//need to new the TiXmlDocument here otherwise the doc strucure will be lost after exiting the callee
	TiXmlDocument* doc = new TiXmlDocument(fileName);
	assert(doc->LoadFile());
	TiXmlHandle hDoc(doc);
	TiXmlElement* pElem;
	pElem=hDoc.FirstChildElement().Element();
	assert(pElem != NULL);

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

void ScriptLayer::initScripts()
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
}

ScriptPlayer* ScriptLayer::findScriptPlayerByKey(char* key)
{
	assert(key != NULL);

	map<char*, ScriptPlayer*, CompareCString>::const_iterator iter = m_map.find(key);

	assert(iter != m_map.end());

	return iter->second;
}

void ScriptLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	if(this->isAnimationPlaying())
	{
		return;
	}

	if(m_player->play() && strcmp(m_player->getId(), "s1") == 0)
	{
		m_player = findScriptPlayerByKey("s2");
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