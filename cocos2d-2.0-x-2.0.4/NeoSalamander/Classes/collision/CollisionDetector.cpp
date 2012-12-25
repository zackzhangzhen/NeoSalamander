#include "CollisionDetector.h"

map<string,CollisionHandler*> collHandlers;

CollObjArray::CollObjArray(void)
{
   m_Tag = "";
   m_objArr = NULL;
}

CollObjArray::CollObjArray(string tag)
{
   m_objArr = new vector<CollidableObject*>;
   m_Tag = tag;
}

void CollObjArray::addElement(CollidableObject* obj)
{
	m_objArr->push_back(obj);
}

int CollObjArray::getSize()
{
	return m_objArr->size();
}

CollidableObject* CollObjArray::getAt(int i)
{
	return (*m_objArr)[i];
}



void CollObjArray::removeByPointer(CollidableObject* obj)
{
	for(vector<CollidableObject*>::iterator it = m_objArr->begin();it!=m_objArr->end();it++)
	{
		CollidableObject* temp1 = obj;
		CollidableObject* temp2 = *it;
		if(temp1 == temp2)
		{
			m_objArr->erase(it);
			return;
		}
	}
}

CollisionHandler::CollisionHandler(CCNode* parent)
{
	m_Parent = parent;
}

CollisionDetector::CollisionDetector(void)
{
}


CollisionDetector::~CollisionDetector(void)
{
	
}

void CollisionHandler::HandleCollison(CCNode* layer,CollidableObject* obj1, CollidableObject* obj2)
{

}

void CollisionDetector::AddToCollArray(CollObjArray* _collObjArray)
{
	m_AllCollObj.push_back(_collObjArray);
}


void CollisionDetector::removeObjectByPointer(CollidableObject* obj)
{
	for(int i = 0;i<m_AllCollObj.size();i++)
	{
		for(int j = 0;j<m_AllCollObj[i]->getSize();j++ )
		{
			if(obj == (m_AllCollObj[i]->getAt(j)))
			{
				m_AllCollObj[i]->removeByPointer(obj);
				return;
			}
		}
	}
}

void CollisionDetector::AddToTargetMap(string& tag, vector<string>& vec)
{
	m_tgtMap.insert(map<string,vector<string>>::value_type(tag,vec));
}

CollObjArray* CollisionDetector::FindArrayByTag(string tag)
{
	for(int i = 0;i<m_AllCollObj.size();i++)
	{
		if(tag == m_AllCollObj[i]->m_Tag)
		{
		    return m_AllCollObj[i];
		}			
	}
}

void CollisionDetector::CollideTwoArrays(CollObjArray* arrLeft,CollObjArray* arrRight)
{
	for(int i = 0;i<arrLeft->m_objArr->size();i++)
	{
		CollidableObject* leftObj = arrLeft->m_objArr->at(i);
		/*CCObject* leftObj = arrLeft->m_objArr->data->arr[i];
		CCObject* rightObj = NULL;
		CCSprite* leftSprite = (CCSprite*)leftObj;
		if(left == NULL)
			continue;
		CCSprite* rightSprite = NULL;
		CCRect leftRect;
		CCRect rightRect;
		leftRect = CCRectMake(leftSprite->getPosition().x - (leftSprite->getContentSize().width/2),leftSprite->getPosition().y - (leftSprite->getContentSize().height/2),leftSprite->getContentSize().width,leftSprite->getContentSize().height);*/

		for(int j = 0; j<arrRight->m_objArr->size();j++)
		{
			CollidableObject* rightObj = (CollidableObject*)arrRight->m_objArr->at(j);
			if(leftObj->IsCollidingWith(rightObj))
			{
				string str = arrLeft->m_Tag + "_"+arrRight->m_Tag;
				map<string,CollisionHandler*>::iterator it = collHandlers.find(str);
				it->second->HandleCollison(it->second->m_Parent,leftObj,rightObj);
			}
			/*rightObj = arrRight->m_objArr->data->arr[j];
			rightSprite = (CCSprite*)rightObj;
			if(right == NULL)
				continue; 
		    rightRect = CCRectMake(rightSprite->getPosition().x - (rightSprite->getContentSize().width/2),rightSprite->getPosition().y - (rightSprite->getContentSize().height/2),rightSprite->getContentSize().width,rightSprite->getContentSize().height);

			if (CCRect::CCRectIntersectsRect(leftRect, rightRect))
			{
				string str = arrLeft->m_Tag + "_"+arrRight->m_Tag;
				map<string,CollisionHandler*>::iterator it = collHandlers.find(str);
				it->second->HandleCollison(it->second->m_Layer,leftObj,rightObj);
			}*/
		}
	}
}


void CollisionDetector::Detect()
{
	for(map<string,vector<string>>::iterator it1 = m_tgtMap.begin();it1 != m_tgtMap.end();it1++)
	{
		CollObjArray* collSide1 = FindArrayByTag(it1->first);
		CollObjArray* collSide2 = NULL;
		for(vector<string>::iterator it2 = it1->second.begin();it2!=it1->second.end();it2++)
		{
		    collSide2 = FindArrayByTag(*it2);
			CollideTwoArrays(collSide1,collSide2);
		}	
	}
}

CollisionHandler::CollisionHandler(void)
{
	m_Parent = NULL;
}

bool CollidableObject::IsCollidingWith(CollidableObject* obj)
{
   return true;
}