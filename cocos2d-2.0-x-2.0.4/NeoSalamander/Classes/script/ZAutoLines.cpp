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

		this->m_label = CCLabelTTF::create(text, font, size, Utility::getDefaultScriptSize(), kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);

		this->m_label->setOpacity(0);
		this->m_label->setVisible(true);

		//set position to center
		CCPoint centerPt = Utility::getCenterPt();
		m_label->setPosition(centerPt);
		this->m_parentScriptLayer->addChild(this->m_label, 11);
		this->m_parentScriptLayer = (ScriptLayer*)parentNode;
	}	
}

ZAutoLines::~ZAutoLines(void)
{
}
