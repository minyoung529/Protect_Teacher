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
#include "ResMgr.h"
#include "TextBar.h"
#include "SkillGauge.h"
#include "GameMgr.h"

Scene_Start::Scene_Start()
{
	ResMgr::GetInst()->ImgLoad(L"BACK", L"Image\\Background.bmp");
}

Scene_Start::~Scene_Start()
{
}
void Scene_Start::Enter()
{
	GameMgr::GetInst()->ReloadScene();

	SoundMgr::GetInst()->Stop(SOUND_CHANNEL::SC_BGM);
	SoundMgr::GetInst()->LoadSound(L"GAME_BGM", true, L"Sound\\GameBGM.mp3");
	SoundMgr::GetInst()->Play(L"GAME_BGM");

	{	// 몬스터 생성기 배치
		MonsterGenerator* pObj = new MonsterGenerator;
		AddObject(pObj, GROUP_TYPE::MONSTER_GENERATOR);
	}

	{	// Score Text
		Object* pObj = new TextBar(TextType::Score, 50);
		pObj->SetPos(Vec2(50, 30));
		AddObject(pObj, GROUP_TYPE::UI);
	}

	{	// HighScore Text
		Object* pObj = new TextBar(TextType::HighScore, 50);
		pObj->SetPos(Vec2(180, 30));
		AddObject(pObj, GROUP_TYPE::UI);
	}

	{	// Gauge
		Object* pObj = new SkillGauge();
		pObj->SetPos(Vec2(350, 40));
		AddObject(pObj, GROUP_TYPE::UI);
	}

	{	// Player
		Object* pObj = new Player();
		pObj->SetPos(Vec2(350, 350));
		AddObject(pObj, GROUP_TYPE::PLAYER);
		GameMgr::GetInst()->SetPlayer(dynamic_cast<Player*>(pObj));
	}

	//CollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::BULLET_PLAYER, GROUP_TYPE::MONSTER);
	CollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
}

void Scene_Start::Exit()
{
	DeleteAll();
	CollisionMgr::GetInst()->CheckReset();
}

void Scene_Start::Update()
{
	Scene::Update();

	// NEXT TURN
	int size = (int)GetGroupObject(GROUP_TYPE::BULLET_PLAYER).size();

	if (!GameMgr::GetInst()->GetCanAttack() && size == 0)
	{
		NextTurn();
	}
}

void Scene_Start::Render(HDC _dc)
{
	POINT res = Core::GetInst()->GetResolution();
	Image* img = ResMgr::GetInst()->ImgFind(L"BACK");

	StretchBlt(_dc, 0, 0, res.x, res.y, img->GetDC(), 0, 0, img->GetWidth(), img->GetHeight(), SRCCOPY);

	Scene::Render(_dc);
}

void Scene_Start::NextTurn()
{
	GameMgr* gameMgr = GameMgr::GetInst();
	vector<Object*> monsters = GetGroupObject(GROUP_TYPE::MONSTER);

	for (Object* obj : monsters)
	{
		if (obj == nullptr || obj->IsDead())continue;

		Monster* m = dynamic_cast<Monster*>(obj);
		m->Move();
	}

	MonsterGenerator* mg = dynamic_cast<MonsterGenerator*>(GetGroupObject(GROUP_TYPE::MONSTER_GENERATOR)[0]);
	mg->NextTurn();

	if (gameMgr->GetUsingSkill())
	{
		gameMgr->AddCurGauge(-gameMgr->GetCurGauge());
	}
	else if (gameMgr->GetCurGauge() >= gameMgr->GetMaxGauge())
	{
		gameMgr->SetUsingSkill(true);
	}


	gameMgr->SetCanAttack(true);
}