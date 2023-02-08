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
#include "Square.h"
#include "GameMgr.h"


Scene_Start::Scene_Start()
{
	ResMgr::GetInst()->ImgLoad(L"BACK", L"Image\\Background.bmp");
	SoundMgr::GetInst()->LoadSound(L"GAME_BGM", true, L"Sound\\GameBGM.mp3");
}

Scene_Start::~Scene_Start()
{
}
void Scene_Start::Enter()
{
	stageCount = 0;
	GameMgr::GetInst()->ReloadScene();
	SoundMgr::GetInst()->Stop(SOUND_CHANNEL::SC_BGM);
	SoundMgr::GetInst()->Play(L"GAME_BGM");

	{	// 몬스터 생성기 배치
		MonsterGenerator* pObj = new MonsterGenerator;
		CreateObject(pObj, GROUP_TYPE::MONSTER_GENERATOR);
	}

	{	// Score Text
		Object* pObj = new TextBar(TextType::Score, 50);
		pObj->SetPos(Vec2(50, 30));
		CreateObject(pObj, GROUP_TYPE::UI);
	}

	{	// HighScore Text
		Object* pObj = new TextBar(TextType::HighScore, 50);
		pObj->SetPos(Vec2(180, 30));
		CreateObject(pObj, GROUP_TYPE::UI);
	}

	{	// Gauge
		Object* pObj = new SkillGauge();
		pObj->SetPos(Vec2(350, 40));
		CreateObject(pObj, GROUP_TYPE::UI);
	}

	{	// Player
		Object* pObj = new Player();
		pObj->SetPos(Vec2(350, 350));
		CreateObject(pObj, GROUP_TYPE::PLAYER);
		GameMgr::GetInst()->SetPlayer(dynamic_cast<Player*>(pObj));
	}

	CreateSquares();

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

	if (gameMgr->GetUsingSkill())	// 전 턴에 썼다면
	{
		gameMgr->AddCurGauge(-gameMgr->GetCurGauge());	// 초기화
		gameMgr->SetUsingSkill(false);
	}
	else if (gameMgr->GetCanUseSkill())
	{
		gameMgr->SetUsingSkill(true);
	}

	if (gameMgr->GetScore() / 5 != stageCount)
	{
		stageCount = gameMgr->GetScore() / 5;
		gameMgr->AddMonsterHp(2);
		gameMgr->AddBlockCount(1);
	}

	gameMgr->SetCanAttack(true);
}

void Scene_Start::CreateSquares()
{
	Vec2 res = Core::GetInst()->GetResolution();

	{	// left
		Object* obj = new Square(Vec2(54, 250), Vec2(8, 100));
		CreateObject(obj, GROUP_TYPE::MONSTER);

		obj = new Square(Vec2(54, 550), Vec2(8, 100));
		CreateObject(obj, GROUP_TYPE::MONSTER);
	}

	{	// right
		Object* obj = new Square(Vec2((int)res.x - 54, 250), Vec2(8, 100));
		CreateObject(obj, GROUP_TYPE::MONSTER);

		obj = new Square(Vec2((int)res.x - 54, 550), Vec2(8, 100));
		CreateObject(obj, GROUP_TYPE::MONSTER);
	}

	{	// top
		Object* obj = new Square(Vec2(200, 104), Vec2(100, 8));
		CreateObject(obj, GROUP_TYPE::MONSTER);

		obj = new Square(Vec2(500, 104), Vec2(100, 8));
		CreateObject(obj, GROUP_TYPE::MONSTER);
	}

	{	// botton
		Object* obj = new Square(Vec2(200, (int)res.y - 5), Vec2(100, 8));
		CreateObject(obj, GROUP_TYPE::MONSTER);

		obj = new Square(Vec2(500, (int)res.y - 5), Vec2(100, 8));
		CreateObject(obj, GROUP_TYPE::MONSTER);
	}
}