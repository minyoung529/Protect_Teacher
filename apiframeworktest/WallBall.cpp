#include "pch.h"
#include "WallBall.h"
#include "Core.h"
#include "TimeMgr.h"

WallBall::WallBall()
{
	m_resolution = Core::GetInst()->GetResolution();
	m_direction = Vec2(3.f, 1.f);
	m_speed = 100.f;

	SetPos(Vec2(100, 100));
	SetScale(Vec2(30, 30));
}

WallBall::~WallBall()
{
}

void WallBall::Update()
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();
	pos += m_direction * (m_speed * TimeMgr::GetInst()->GetfDT());

	if (pos.x < scale.x / 2 || pos.x > m_resolution.x - scale.x / 2)
	{
		m_direction = Vec2(-m_direction.x, m_direction.y);
	}
	if (pos.y < scale.y / 2 || pos.y > m_resolution.y - scale.y / 2)
	{
		m_direction = Vec2(m_direction.x, -m_direction.y);
	}

	SetPos(pos);
}