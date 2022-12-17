#include "pch.h"
#include "FollowHeart.h"
#include "GameMgr.h"
#include "ResMgr.h"
#include "Image.h"
#include "TimeMgr.h"
#include "DotObject.h"

FollowHeart::FollowHeart()
	: m_speed(1200.f)
	, m_imgScale(50.f)
	, m_dist(0.f)
	, m_curDist(0.f)
	, m_damping(0.f)
	, m_accDist(0.f)
{
	m_target = GameMgr::GetInst()->GetHeartPos();
	m_image = ResMgr::GetInst()->ImgLoad(L"Score", L"Image\\Score.bmp");
}

FollowHeart::~FollowHeart()
{
}

void FollowHeart::Update()
{
	Vec2 pos = GetPos();
	float remainDist = GetDist(pos, m_target);

	if (m_dist == 0.f)
	{
		m_dist = remainDist;
	}

	if (remainDist < 2.f)
	{
		DeleteObject(this);
		return;
	}

	m_dir = (m_target - pos).Normalize();
	Vec2 nextPos = pos + (m_dir * (remainDist / 15.f));

	float d = GetDist(pos, nextPos);
	m_accDist += d;
	m_curDist += d;

	if (m_accDist >= 4.f)
	{
		CreateDot(m_curDist / m_dist);
		m_accDist = 0.f;
	}

	SetPos(nextPos);
}

void FollowHeart::Render(HDC _dc)
{
	Vec2 pos = GetPos();

	TransparentBlt(_dc, GetPos().x, GetPos().y, m_imgScale, m_imgScale,
		m_image->GetDC(), 0, 0, m_image->GetWidth(), m_image->GetHeight(), RGB(255, 0, 255));
}

void FollowHeart::CreateDot(float rate)
{
	Object* dot = new DotObject(rate, 0.5f);
	dot->SetPos(Vec2(GetPos().x + m_imgScale / 2, GetPos().y + m_imgScale / 2));
	dot->SetScale(Vec2(20, 20));
	CreateObject(dot, GROUP_TYPE::DEFAULT);
}

float FollowHeart::GetDist(Vec2 one, Vec2 two)
{
	return sqrt(pow(one.x - two.x, 2.f) + pow(one.y - two.y, 2.f));
}
