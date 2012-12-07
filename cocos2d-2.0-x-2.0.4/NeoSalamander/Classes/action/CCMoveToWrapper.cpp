#include "CCMoveToWrapper.h"

CCMoveToWrapper::CCMoveToWrapper()
{
}

CCMoveToWrapper::CCMoveToWrapper(float duration, CCPoint endPoint)
{
	this->m_moveTo = CCMoveTo::actionWithDuration(duration, endPoint);
	this->m_duration = duration;
	this->m_endPoint = endPoint;
}

CCMoveTo* CCMoveToWrapper::getMoveTo()
{
	return m_moveTo;
}

float CCMoveToWrapper::getDuration()
{
	return m_duration;
}

CCPoint CCMoveToWrapper::getEndPoint()
{
	return m_endPoint;
}

CCMoveToWrapper::~CCMoveToWrapper(void)
{
}
