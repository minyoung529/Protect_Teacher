#include "pch.h"
#include "MonsterGenerator.h"
#include "KeyMgr.h"
#include "Core.h"
#include "Monster.h"
#include "ResMgr.h"

MonsterGenerator::MonsterGenerator()
{
	POINT res = Core::GetInst()->GetResolution();
	m_monsterScale = Vec2(res.x / MONSTER_W_COUNT, res.y / MONSTER_H_COUNT);

	m_w_idx = { res.x / m_monsterScale.x, res.y / m_monsterScale.y };
	m_h_idx = { res.x / m_monsterScale.y, res.y / m_monsterScale.x };

	Image* image = ResMgr::GetInst()->ImgLoad(L"RED", L"Image\\redbrick.bmp");

	m_monsterDatas.push_back(MonsterData{ L"이민영", 2, image });
}

MonsterGenerator::~MonsterGenerator()
{
}

void MonsterGenerator::Update()
{
	if (KeyMgr::GetInst()->GetKey(KEY::SPACE) == KEY_STATE::TAP)
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

	position.y = rand() % SPAWN_DIST + (m_h_idx.y - SPAWN_DIST) / 2;
	position = GetCenterVPos(position.x, position.y);

	CreateMonster(position, scale, dir);
}

void MonsterGenerator::GenerateHorizontalMonster()
{
	// _--
	Direction dir = Direction::Down;
	Vec2 position{ 0,0 };
	position.x = rand() % SPAWN_DIST + (m_w_idx.x - SPAWN_DIST) / 2;

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
	Monster* pMonster = new Monster(m_monsterDatas[rand() % (int)m_monsterDatas.size()], static_cast<BRUSH_TYPE>(rand() % (int)BRUSH_TYPE::END), scale);
	pMonster->SetName(L"Enemy");
	pMonster->SetPos(position);
	pMonster->SetDirection(dir);
	CreateObject(pMonster, GROUP_TYPE::MONSTER);

	return pMonster;
}

Vec2 MonsterGenerator::GetCenterVPos(int x, int y)
{
	return
	{
		m_monsterScale.y * x + m_monsterScale.y / 2,
		m_monsterScale.x * y + m_monsterScale.x / 2,
	};
}

Vec2 MonsterGenerator::GetCenterHPos(int x, int y)
{
	return
	{
		m_monsterScale.x * x + m_monsterScale.x / 2,
		m_monsterScale.y * y + m_monsterScale.y / 2,
	};
}
