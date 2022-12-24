#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "GameMgr.h"

void Scene::Update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_vecObj[i].size(); j++)
		{
			if (!m_vecObj[i][j]->IsDead() && m_vecObj[i][j] != nullptr)
				m_vecObj[i][j]->Update();
		}
	}
}

void Scene::FinalUpdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_vecObj[i].size(); j++)
		{
			m_vecObj[i][j]->FinalUpdate();
		}
	}
}

void Scene::Render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		vector<Object*>::iterator iter = m_vecObj[i].begin();
		for (; iter != m_vecObj[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->Render(_dc);
				iter++;
			}
			else
			{
				iter = m_vecObj[i].erase(iter);
			}
		}
	}
}

void Scene::DeleteGroup(GROUP_TYPE _eTarget)
{
	for (size_t i = 0; i < m_vecObj[(UINT)_eTarget].size(); i++)
	{
		delete m_vecObj[(UINT)_eTarget][i];
	}

	m_vecObj[(UINT)_eTarget].clear();
}

void Scene::DeleteAll()
{
	GameMgr::GetInst()->deleteAll = true;

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

Scene::Scene()
{
}

Scene::~Scene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_vecObj[i].size(); j++)
		{
			m_vecObj[i][j]->m_bAlive = true;
			SAFE_DELETE(m_vecObj[i][j])
		}
	}
}
