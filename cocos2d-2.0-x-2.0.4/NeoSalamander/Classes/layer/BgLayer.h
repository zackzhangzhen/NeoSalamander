
#ifndef __BG_LAYER_H__
#define __BG_LAYER_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

#include "sprite/ZSprite.h"

#include "NeoConstants.h"
class BgLayer : public cocos2d::CCLayer
{
public:
   BgLayer::BgLayer(void);
   BgLayer::BgLayer(CCArray* sprites);  
   
   BgLayer::~BgLayer(void);
   void BgLayer::scroll(float dt);
   void BgLayer::scheduleScroll(float dt);
   void ccTouchesEnded(CCSet* touches, CCEvent* event);
private:
	bool bg01;
	static const char* BG_01;
	static const char* BG_02;
	static const cocos2d::CCTexture2D* bgTex01;
	static const cocos2d::CCTexture2D* bgTex02;
	static float scrollFrequency;
	static float scrollVelocity;

	CCSprite* m_bgSprite;
};


#endif  // __BG_LAYER_H__
