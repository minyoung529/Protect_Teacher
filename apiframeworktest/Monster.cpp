#include "pch.h"
#include "Monster.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "KeyMgr.h"
#include "SelectGDI.h"
#include "Effect.h"
#include "Animator.h"
#include "func.h"
#include "GameMgr.h"
#include "SoundMgr.h"
#include "FollowHeart.h"
#include "ResMgr.h"
#include "Player.h"

Monster::Monster()
	: m_iHp(5)
	, m_monsterData{}
	, m_color(BRUSH_TYPE::END)
	, m_direction(Direction::Length)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

Monster::Monster(const MonsterData& monsterData, BRUSH_TYPE brush, Vec2 size)
	: m_monsterData(monsterData)
	, m_color(brush)
	, m_iHp(monsterData.m_maxHp)
	, m_direction(Direction::Length)
{
	SetScale(size);
	CreateCollider();
	GetCollider()->SetScale(size);

	SoundMgr::GetInst()->LoadSound(L"HIT", false, L"Sound\\Hit.mp3");
	SoundMgr::GetInst()->LoadSound(L"DIE", false, L"Sound\\Die.mp3");
}


Monster::~Monster()
{
}

void Monster::Update()
{
}

void Monster::Render(HDC _dc)
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	//int width = (int)m_monsterData.m_image->GetWidth();
	//int height = (int)m_monsterData.m_image->GetHeight();

	//SetStretchBltMode(_dc, COLORONCOLOR);

	SelectGDI s(_dc, m_color);
	SelectGDI s1(_dc, PEN_TYPE::HOLLOW);

	Rectangle(_dc, pos.x - (GetScale().x / 2), pos.y - (GetScale().y / 2)
		, pos.x + (GetScale().x / 2), pos.y + (GetScale().y / 2));

	if (haveItem)
	{
		Image* img = ResMgr::GetInst()->ImgFind(L"STAR");
		Vec2 star = GetPos();
		TransparentBlt(_dc, star.x - img->GetWidth() / 4, star.y - img->GetHeight() / 2, img->GetWidth() / 2, img->GetHeight() / 2,
			img->GetDC(), 0, 0, img->GetWidth(), img->GetHeight(), RGB(255, 0, 255));
	}

	//StretchBlt(
	//	_dc,
	//	(int)(pos.x - (GetScale().x / 2) + COLOR_THICKNESS),
	//	(int)(pos.y - (GetScale().y / 2) + COLOR_THICKNESS),
	//	GetScale().x - COLOR_THICKNESS*2, GetScale().y - COLOR_THICKNESS*2,
	//	m_monsterData.m_image->GetDC(),
	//	0, 0, width, height, SRCCOPY);

	// Hp Ãâ·Â
	wchar_t s_hp[6];
	wsprintf(s_hp, L"%d", m_iHp);

	SetTextAlign(_dc, TA_CENTER);
	TextOut(_dc, pos.x, pos.y + 4, s_hp, lstrlen(s_hp));

	//Component_Render(_dc);
}

void Monster::Move()
{
	if (this == nullptr)
		return;

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

void Monster::EnterCollision(Collider* _pOther, RECT colRt)
{
	Object* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Bullet_Player")
	{
		PlayParticle();
		Hit(1);
	}
}

void Monster::Hit(int damage)
{
	m_iHp -= damage;

	if (m_iHp <= 0 || GameMgr::GetInst()->GetUsingSkill())
	{
		GameMgr::GetInst()->AddScore(1);
		SoundMgr::GetInst()->Play(L"DIE");

		Object* follow = new FollowHeart();

		follow->SetPos(Vec2(GetPos().x + GetScale().x / 2, GetPos().y + GetScale().y / 2));
		CreateObject(follow, GROUP_TYPE::MONSTER);

		if (!GameMgr::GetInst()->GetUsingSkill())
			GameMgr::GetInst()->AddCurGauge(1);

		if (haveItem)
		{
			Vec2 playerPos = GameMgr::GetInst()->GetPlayer()->GetPos();
			FollowHeart* follow = new FollowHeart(playerPos, true);
			follow->SetColor(DotColor::Black);
			follow->SetPos(Vec2(GetPos().x + GetScale().x / 2, GetPos().y + GetScale().y / 2));
			CreateObject(follow, GROUP_TYPE::MONSTER);
			GameMgr::GetInst()->GetPlayer()->originalBulletCnt += 1;
		}

		DeleteObject(this);
	}
	else
	{
		SoundMgr::GetInst()->Play(L"HIT");
	}
}

void Monster::PlayParticle()
{
	Object* effect = new Effect(L"Pop_Red", BRUSH_TYPE::RED);
	CreateObject(effect, GROUP_TYPE::EFFECT);
	effect->SetPos(Vec2(-30, 0) + GetPos());
}