#include "pch.h"
#include "Scene_Start.h"
#include "Object.h"
#include "Player.h"
#include "MonsterGenerator.h"
#include "Core.h"
#include "Image.h"
#include "PathMgr.h"
#include "CollisionMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
Scene_Start::Scene_Start()
{
}

Scene_Start::~Scene_Start()
{
}
void Scene_Start::Enter()
{
	SoundMgr::GetInst()->LoadSound(L"BGM", true, L"Sound\\pianobgm.wav");
	SoundMgr::GetInst()->Play(L"BGM");
	
	// Object 추가
	{
		Object* pObj = new Player;
		pObj->SetPos(Vec2(Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2));
		pObj->SetScale(Vec2(100.f, 100.f));
		AddObject(pObj, GROUP_TYPE::PLAYER);
	}

	// 몬스터 생성기 배치
	{
		Object* pObj = new MonsterGenerator;
		AddObject(pObj, GROUP_TYPE::MONSTER);
	}


	CollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::BULLET_PLAYER, GROUP_TYPE::MONSTER);

}

void Scene_Start::Exit()
{
	DeleteAll();
	CollisionMgr::GetInst()->CheckReset();
}

void Scene_Start::Update()
{  
	Scene::Update();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::SCENE_01);
	}
}
