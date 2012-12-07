#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class CCMoveToWrapper
{
public:
	CCMoveToWrapper();
	CCMoveToWrapper(float duration, CCPoint endPoint);
	CCMoveTo* getMoveTo();
	float getDuration();
	CCPoint getEndPoint();
	~CCMoveToWrapper(void);

private:
	CCMoveTo* m_moveTo;
	float m_duration;
	CCPoint m_endPoint;
};

