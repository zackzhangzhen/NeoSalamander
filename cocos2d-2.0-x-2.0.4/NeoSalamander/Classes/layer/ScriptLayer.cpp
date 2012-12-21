#include "ScriptLayer.h"


ScriptLayer::ScriptLayer(void)
{
	this->setTouchEnabled(true);
	m_player = NULL;
	initScripts();
}


ScriptLayer::~ScriptLayer(void)
{
}

void ScriptLayer::initScripts()
{
	//==========================================================
	vector<ZDlg*> vec1;

	ZDlg* dlg = new ZDlg(ZDlg::POS_LEFT, "你好呀，大家都过来做一个简单的自我介绍好不好呀啊？", "pic\\figure\\assassin.png", this);
	vec1.push_back(dlg);

	dlg = new ZDlg(ZDlg::POS_RIGHT, "Fine thank you! My name is Li Lei, what about you?", "pic\\figure\\master_chief.png", this);
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

	map<char*, ScriptPlayer*>::const_iterator iter = m_map.find(key);

	assert(iter != m_map.end());

	return iter->second;
}

void ScriptLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	if(m_player->play() && strcmp(m_player->getId(), "s1") == 0)
	{
		m_player = findScriptPlayerByKey("s2");
	}
}