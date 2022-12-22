#include "pch.h"
#include "MonsterGenerator.h"
#include "KeyMgr.h"
#include "Core.h"
#include "Monster.h"
#include "ResMgr.h"
#include "GameMgr.h"
#include "func.h"

MonsterGenerator::MonsterGenerator()
{
	POINT res = Core::GetInst()->GetResolution();

	m_rect.left = 50;
	m_rect.top = 100;
	m_rect.right = res.x - 50;
	m_rect.bottom = res.y;

	m_width = m_rect.right - m_rect.left;
	m_height = m_rect.bottom - m_rect.top;

	m_monsterScale = Vec2(m_width / (float)MONSTER_W_COUNT, m_height / (float)MONSTER_H_COUNT);

	m_w_idx = { m_width / m_monsterScale.x, m_height / m_monsterScale.y };
	m_h_idx = { m_width / m_monsterScale.y, m_height / m_monsterScale.x };

	m_monsterDatas.push_back(MonsterData{ L"Enemy", 2,  /*ResMgr::GetInst()->ImgLoad(L"LEE", L"Image\\redbrick.bmp")*/ nullptr });
	m_monsterDatas.push_back(MonsterData{ L"Enemy", 10, /*ResMgr::GetInst()->ImgLoad(L"DONG", L"Image\\dongyun.bmp")*/ nullptr });
	m_monsterDatas.push_back(MonsterData{ L"Enemy", 1, /*ResMgr::GetInst()->ImgLoad(L"KANG", L"Image\\daehee.bmp") */ nullptr});
	m_monsterDatas.push_back(MonsterData{ L"Enemy", 1, /*ResMgr::GetInst()->ImgLoad(L"NAM", L"Image\\sojeong.bmp") */ nullptr});

	ResMgr::GetInst()->ImgLoad(L"GAME_BACK", L"Image\\GameBack.bmp");
	ResMgr::GetInst()->ImgLoad(L"STAR", L"Image\\Star.bmp");

	srand(1023);
}

MonsterGenerator::~MonsterGenerator() {}

void MonsterGenerator::Update()
{
}

void MonsterGenerator::Render(HDC _dc)
{
	Image* backImg = ResMgr::GetInst()->ImgFind(L"GAME_BACK");

	//Rectangle(_dc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);

	TransparentBlt(_dc, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top,
		backImg->GetDC(), 0, 0, backImg->GetWidth(), backImg->GetHeight(), RGB(255, 0, 255));
}

void MonsterGenerator::NextTurn()
{
	for (int i = 0; i < GameMgr::GetInst()->GetBlockCount(); i++)
	{
		GenerateVerticalMonster();
		GenerateHorizontalMonster();
	}
}

void MonsterGenerator::GenerateVerticalMonster()
{
	// l l
	Direction dir = Direction::Right;
	Vec2 position{ 0,0 };
	Vec2 scale = { m_monsterScale.y, m_monsterScale.x };	// x, y swap

	if (rand() % 2)
	{
		position.x = m_h_idx.x - 1;
		dir = Direction::Left;
	}

	position.y = (rand() % SPAWN_DIST + 1) + (m_h_idx.y - SPAWN_DIST) / 2;
	position = GetCenterVPos(position.x, position.y);

	CreateMonster(position, scale, dir);
}

void MonsterGenerator::GenerateHorizontalMonster()
{
	// _--
	Direction dir = Direction::Down;
	Vec2 position{ 0,0 };
	position.x = (rand() % SPAWN_DIST + 1) + (m_w_idx.x - SPAWN_DIST) / 2;

	// 1/2 확률로 아래에서 나온다 __
	if (rand() % 2)
	{
		position.y = m_w_idx.y - 1;
		dir = Direction::Up;
	}

	position = GetCenterHPos(position.x, position.y);

	CreateMonster(position, m_monsterScale, dir);
}

Monster* MonsterGenerator::CreateMonster(Vec2 position, Vec2 scale, Direction dir)
{
	Monster* pMonster = new Monster(m_monsterDatas[rand() % (int)m_monsterDatas.size()], static_cast<BRUSH_TYPE>(rand() % (int)BRUSH_TYPE::HOLLOW), scale);
	pMonster->SetName(L"Enemy");
	pMonster->SetPos(position);
	pMonster->SetDirection(dir);

	if (rand() % 2 == 0)
	{
		pMonster->SetIsItem();
	}

	CreateObject(pMonster, GROUP_TYPE::MONSTER);
	return pMonster;
}

Vec2 MonsterGenerator::GetCenterVPos(int x, int y)
{
	return
	{
		m_monsterScale.y * x + m_monsterScale.y / 2 + m_rect.left,
		m_monsterScale.x * y + m_monsterScale.x / 2 + m_rect.top,
	};
}

Vec2 MonsterGenerator::GetCenterHPos(int x, int y)
{
	return
	{
		m_monsterScale.x * x + m_monsterScale.x / 2 + m_rect.left,
		m_monsterScale.y * y + m_monsterScale.y / 2 + m_rect.top,
	};
}
