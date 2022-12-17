#include "pch.h"
#include "WallBall.h"
#include "Core.h"
#include "TimeMgr.h"
#include "ResMgr.h"
#include "Image.h"
#include "DotObject.h"

WallBall::WallBall(Vec2 direction)
	: m_direction(direction)
	, m_speed(100.f)
	, m_timer(0.f)
{
	m_resolution = Core::GetInst()->GetResolution();
	m_pImage = ResMgr::GetInst()->ImgLoad(L"Heart", L"Image\\Heart.bmp");

	SetPos(Vec2(m_resolution.x / 2, m_resolution.y / 2));
	SetScale(Vec2(40, 40));
}

WallBall::~WallBall()
{
}

void WallBall::Update()
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();
	pos += m_direction * (m_speed * (float)(DT));
	m_dist += (m_speed * (float)(DT));

	if (m_timer < m_maxTime / 2)
	{
		m_timer += DT;
		m_curScale += DT * m_scaleIncrease;
	}
	else if (m_timer < m_maxTime)
	{
		m_timer += DT;
		m_curScale -= DT * m_scaleIncrease;
	}
	else
	{
		m_timer = 0.f;
	}

	if (!CheckLimit())
		SetPos(pos);

	if (m_dist > 6.f)
	{
		CreateDot();
		m_dist = 0.f;
	}
}

void WallBall::Render(HDC _dc)
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	TransparentBlt(_dc,
		pos.x - (scale.x + m_curScale) / 2, pos.y - (scale.y + m_curScale) / 2,
		m_pImage->GetWidth() + m_curScale, m_pImage->GetHeight() + m_curScale, m_pImage->GetDC(),
		0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), RGB(255, 255, 255));
}

void WallBall::CreateDot()
{
	int color = ((dotCnt++) / 3) % ((int)DotColor::Length - 1) + 1;
	Object* dot = new DotObject((DotColor)color, 2.f);

	dot->SetPos(GetPos());
	dot->SetScale(Vec2(30, 30));

	CreateObject(dot, GROUP_TYPE::DEFAULT);
}

bool WallBall::CheckLimit()
{
	Vec2 pos = GetPos();
	Vec2 temp = pos;
	Vec2 scale = GetScale();

	if (pos.x < scale.x / 2)
	{
		m_direction = Vec2(-m_direction.x, m_direction.y);
		pos.x = scale.x / 2;
	}
	if (pos.x > m_resolution.x - scale.x / 2)
	{
		m_direction = Vec2(-m_direction.x, m_direction.y);
		pos.x = m_resolution.x - scale.x / 2;
	}
	if (pos.y < scale.y / 2)
	{
		m_direction = Vec2(m_direction.x, -m_direction.y);
		pos.y = scale.y / 2;
	}
	if (pos.y > m_resolution.y - scale.y / 2)
	{
		m_direction = Vec2(m_direction.x, -m_direction.y);
		pos.y = m_resolution.y - scale.y / 2;
	}

	if (temp != pos)
	{
		SetPos(pos);
		return true;
	}

	return false;
}
