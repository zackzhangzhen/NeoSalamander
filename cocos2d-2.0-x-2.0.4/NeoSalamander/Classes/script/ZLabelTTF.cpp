#include "script\ZLabelTTF.h"


char* ZLabelTTF::FONT_COMIC = "Comic Sans MS";
char* ZLabelTTF::YAHEI = "Microsoft JhengHei";
int ZLabelTTF::FONT_DEFAULT_SIZE = 28;
int ZLabelTTF::FONT_COLOR_DEFAULT = 0;
int ZLabelTTF::FONT_COLOR_BLUE = 1;

void ZLabelTTF::init(vector<ScriptElement*>& scripts, CCSize scriptSize,int colorCode, char* font,  int size)
{
	this->m_scripts = scripts;
	this->m_iter = m_scripts.begin();

	//assert(m_iter != scripts.end());

	ScriptElement* elem = *m_iter;
	//Please put the first line of a dlg as a text, not an option.
	assert(elem->isType(ScriptElementType::LINE));
	
	ValueWrapper* text = (ValueWrapper*)elem;
	this->m_label = CCLabelTTF::create(text->getText(), font, size,scriptSize,kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);

	this->m_label->setOpacity(0);

	setColor(colorCode);
}

void ZLabelTTF::setColor(int colorCode)
{
	//0 : WHITE
	//1 : BLUE
	//2 : YELLOW 
	//3 : MAGENTA
	//4 : ORANGE
	//5 : GREEN
	//6 : RED
	//7 : BLACK
	//8 : GRAY
	//default(0) : WHITE
	switch(colorCode)
	{
	case 1:
		{
			this->m_label->setColor(ccBLUE  );
			break;
		}
	case 2:
		{
			this->m_label->setColor(ccYELLOW  );
			break;
		}
	case 3:
		{
			this->m_label->setColor(ccMAGENTA  );
			break;
		}
	case 4:
		{
			this->m_label->setColor(ccORANGE  );
			break;
		}
	case 5:
		{
			this->m_label->setColor(ccGREEN  );
			break;
		}
	case 6:
		{
			this->m_label->setColor(ccRED  );
			break;
		}
	case 7:
		{
			this->m_label->setColor(ccBLACK  );
			break;
		}
	case 8:
		{
			this->m_label->setColor(ccGRAY  );
			break;
		}
	default:
		{
			return;
		}
	}
}

ZLabelTTF::ZLabelTTF(vector<ScriptElement*>& scripts, CCSize scriptSize, int colorCode, char* font, int size)
{
	init(scripts, scriptSize, colorCode, font, size);
}


ZLabelTTF::~ZLabelTTF(void)
{
}

void ZLabelTTF::setPosition(CCPoint pos)
{
	this->m_label->setPosition(pos);
}

void ZLabelTTF::setPositionX(int x)
{
	this->m_label->setPositionX(x);
}

void ZLabelTTF::setPositionY(int y)
{
	this->m_label->setPositionY(y);
}

int ZLabelTTF::getPositionX(void)
{
	return this->m_label->getPositionX();
}

int ZLabelTTF::getPositionY(void)
{
	return this->m_label->getPositionY();
}

CCPoint ZLabelTTF::getPosition(void)
{
	return this->m_label->getPosition();
}

CCLabelTTF* ZLabelTTF::getLabel()
{
	return this->m_label;
}

void ZLabelTTF::addToCCNode(CCNode* node, int zOrder)
{
	assert(node!=NULL);

	if(this->m_label->getParent() != NULL)
	{
		return;
	}

	node->addChild(this->m_label, zOrder);
	m_parentNode = node;
}

CCAction * ZLabelTTF::runAction(CCAction* action)
{
	return this->m_label->runAction(action);
}

void ZLabelTTF::setOpacity(int opacity)
{
	this->m_label->setOpacity(opacity);
}

bool ZLabelTTF::rollScript()
{
	if(++m_iter != m_scripts.end())
	{
		ScriptElement* elem = *m_iter;
		if(elem->isType(ScriptElementType::LINE))
		{
			this->m_label->setString(elem->getText());
		}
		else if(elem->isType(ScriptElementType::OPTIONS))
		{
			ZMenu* menu = (ZMenu*)elem;
			menu->show();
		}

		return false;
	}

	return true;
}

void ZLabelTTF::jumpToLine(char* lineId)
{
	while(m_iter != m_scripts.end())
	{
		ScriptElement* elem = *m_iter;
		if(elem->isType(ScriptElementType::LINE))
		{
			ValueWrapper* line = (ValueWrapper*) elem;
			char* id = line->getLineId();

			if(id != NULL && strcmp(lineId, id) == 0)
			{
				this->m_label->setString(elem->getText());
				break;
			}			
		}

		m_iter++;
	}
}