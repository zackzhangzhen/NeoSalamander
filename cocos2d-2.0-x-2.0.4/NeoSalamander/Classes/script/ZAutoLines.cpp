#include "ZAutoLines.h"
#include "layer\ScriptLayer.h"
#include "script\ZLabelTTF.h"
ZAutoLines::ZAutoLines(TiXmlElement* autolinesElem, CCNode* parentNode, bool visible) : ScriptElement(ScriptElementType::AUTO_LINES)
{
	assert(parentNode != NULL);

	TiXmlElement* autoScriptElem = autolinesElem->FirstChildElement();
	assert(autoScriptElem != NULL);

	//populate menu items and options 
	for( ; autoScriptElem != NULL; autoScriptElem=autoScriptElem->NextSiblingElement())
	{

		int size = ZLabelTTF::FONT_DEFAULT_SIZE;
		autoScriptElem->Attribute(NeoConstants::SCRIPT_ATTR_SIZE, &size);

		int colorCode = ZLabelTTF::FONT_COLOR_DEFAULT;
		autoScriptElem->Attribute(NeoConstants::SCRIPT_ATTR_COLOR, &colorCode);


		char* font = (char*)autoScriptElem->Attribute(NeoConstants::SCRIPT_ATTR_FONT);
		if(font == NULL)
		{
			font = ZLabelTTF::YAHEI;
		}

		//text
		char* text = (char*)autoScriptElem->GetText();

		this->m_parentScriptLayer = (ScriptLayer*)parentNode;

		CCLabelTTF* label = this->createLabel(text, font, size);

		this->m_labels.push_back(label);

		
	}	
}

CCLabelTTF* ZAutoLines::createLabel(char* text, char* font, int size)
{
	CCLabelTTF* label = CCLabelTTF::create(text, font, size, Utility::getDefaultScriptSize(), kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);

	label->setOpacity(0);
	label->setVisible(true);

	//set position to center
	CCPoint centerPt = Utility::getCenterPt();
	label->setPosition(centerPt);

	this->m_parentScriptLayer->addChild(label, 11);

	return label;
}

void ZAutoLines::play()
{

}

ZAutoLines::~ZAutoLines(void)
{
}
