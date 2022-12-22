#include "pch.h"
#include "SceneMgr.h"
#include "Scene_Start.h"
#include "Scene_01.h"
#include "EventMgr.h"
#include "Scene_Lobby.h"
#include "Scene_End.h"
SceneMgr::SceneMgr()
	: m_pCurScene(nullptr)
	, m_arrScene{}
{
}

SceneMgr::~SceneMgr()
{
	// 씬 전부 삭제
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}

void SceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	m_pCurScene->Exit();
	m_pCurScene = m_arrScene[(UINT)_eNext];
	m_pCurScene->Enter();
}

void SceneMgr::Init()
{
	// Scene 생성
	m_arrScene[(UINT)SCENE_TYPE::START] = new Scene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	m_arrScene[(UINT)SCENE_TYPE::LOBBY] = new Scene_Lobby;
	m_arrScene[(UINT)SCENE_TYPE::LOBBY]->SetName(L"Lobby Scene");

	m_arrScene[(UINT)SCENE_TYPE::GAMEOVER] = new Scene_End;
	m_arrScene[(UINT)SCENE_TYPE::GAMEOVER]->SetName(L"End Scene");
	// 현재 씬 지정
	//m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::LOBBY];
	m_pCurScene->Enter();
}

void SceneMgr::Update()
{
	m_pCurScene->Update();
	m_pCurScene->FinalUpdate();
}

void SceneMgr::Render(HDC _dc)
{ 
	m_pCurScene->Render(_dc);
}
