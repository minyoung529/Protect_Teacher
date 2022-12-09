#include "pch.h"
#include "Monster.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "KeyMgr.h"

Monster::Monster():
	 m_iHp(5)

{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

Monster::Monster(const MonsterData& monsterData)
	: m_monsterData(monsterData)
{
	m_iHp = monsterData.m_maxHp;
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

void Monster::EnterCollision(Collider* _pOther)
{
	Object* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Bullet_Player")
	{
		m_iHp -= 1;
		if(m_iHp <= 0)
			DeleteObject(this);
	}
}

