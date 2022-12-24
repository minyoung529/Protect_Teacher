#pragma once
#include"EventMgr.h"
#include"Object.h"

class Object;
void CreateObject(Object* _pObj, GROUP_TYPE _eGroup);
void DeleteObject(Object* _pObj);
void ChangeScene(SCENE_TYPE _eNext);
//
//void Safe_Delete_Vec(vector<Object*>& _vec)
//{
//	for (size_t i = 0; i < _vec.size(); i++)
//	{
//		if (nullptr != _vec[i])
//		{
//			if (!_vec[i]->IsDead())
//			{
//				delete _vec[i];
//			}
//		}
//	}
//	_vec.clear();
//}

template<typename T1, typename T2>
void Safe_Delete_Map(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator iter = _map.begin();
	for (; iter != _map.end(); ++iter)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
	_map.clear();
}