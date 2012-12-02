#include "ZSprite.h"
using namespace cocos2d;
//The base class for the sprites
ZSprite::ZSprite(void)
{

}

ZSprite::ZSprite(char* fileName, CCSize originalSize)
{
	this->m_sprite = CCSprite::create(fileName);
	this->m_originSize = originalSize;
}

ZSprite::~ZSprite(void)
{
}
