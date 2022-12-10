#include "pch.h"
#include "Monster.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "KeyMgr.h"
#include "SelectGDI.h"

Monster::Monster() 
	: m_iHp(5)
	, m_monsterData{}
	, m_color(BRUSH_TYPE::END)
	, m_direction(Direction::Length)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

Monster::Monster(const MonsterData& monsterData, BRUSH_TYPE brush)
	: m_monsterData(monsterData)
	, m_color(brush)
	, m_iHp(monsterData.m_maxHp)
	, m_direction(Direction::Length)
{
}

Monster::~Monster()
{
}

void Monster::Update()
{
	if (KEY_TAP(KEY::SPACE))
	{
		Vec2 position = GetPos();

		switch (m_direction)
		{
		case Direction::Up:
			position.y -= GetScale().y;
			break;

		case Direction::Down:
			position.y += GetScale().y;
			break;

		case Direction::Left:
			position.x -= GetScale().x;
			break;

		case Direction::Right:
			position.x += GetScale().x;
			break;
		}

		SetPos(position);
	}
}

void Monster::Render(HDC _dc)
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	BRUSH_TYPE eBrush = m_color;
	SelectGDI b(_dc, eBrush);

	Rectangle(_dc,
		(int)(pos.x - scale.x / 2.f)
		, (int)(pos.y - scale.y / 2.f)
		, (int)(pos.x + scale.x / 2.f)
		, (int)(pos.y + scale.y / 2.f));

	// Hp Ãâ·Â
	wchar_t s_hp[6];
	wsprintf(s_hp, L"%d", m_iHp);

	SetTextAlign(_dc, TA_CENTER);
	TextOut(_dc, pos.x, pos.y - 5, s_hp, lstrlen(s_hp));

	SelectGDI b2(_dc, BRUSH_TYPE::HOLLOW);
}

void Monster::EnterCollision(Collider* _pOther)
{
	Object* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player")
	{
		Hit(1);
	}
}

void Monster::Hit(int damage)
{
	m_iHp -= damage;

	if (m_iHp <= 0)
	{
		SetDead(true);
	}
}
