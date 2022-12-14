#include "pch.h"
#include "SkillGauge.h"
#include "ResMgr.h"
#include "KeyMgr.h"

SkillGauge::SkillGauge()
	: m_max(0)
	, m_val(0)
{
	SetValue();
	m_max = 100;
	m_val = 0;
}

SkillGauge::SkillGauge(int max, int val)
	: m_max(max)
	, m_val(val)
{
	SetValue();
}

SkillGauge::SkillGauge(Vec2 scale)
	: m_max(0)
	, m_val(0)
{
	SetScale(scale);
	SetValue();
}

SkillGauge::~SkillGauge()
{
}

void SkillGauge::Update()
{
	if (KEY_HOLD(KEY::SPACE))
	{
		m_val++;
	}
}

void SkillGauge::Render(HDC _dc)
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();
	Vec2 center = { pos.x - scale.x / 2, pos.y - scale.y / 2 };
	float rate = GetRate();

	TransparentBlt(_dc, center.x, center.y, m_backImg->GetWidth(), m_backImg->GetHeight(),
		m_backImg->GetDC(), 0, 0, m_backImg->GetWidth(), m_backImg->GetHeight(), RGB(255, 0, 255));

	TransparentBlt(_dc, center.x, center.y, m_fillImg->GetWidth() * rate, m_fillImg->GetHeight(),
		m_fillImg->GetDC(), 0, 0, m_fillImg->GetWidth() * rate, m_fillImg->GetHeight(), RGB(255, 0, 255));

	TransparentBlt(_dc, pos.x + m_backImg->GetWidth() * rate - m_icon->GetWidth()/2, center.y - m_icon->GetHeight() / 3,
		m_icon->GetWidth(), m_icon->GetHeight(),
		m_icon->GetDC(), 0, 0, m_icon->GetWidth(), m_icon->GetHeight(), RGB(255, 0, 255));
}

void SkillGauge::SetValue()
{
	m_backImg = ResMgr::GetInst()->ImgLoad(L"GAUGE_BACK", L"Image\\Gauge.bmp");
	m_fillImg = ResMgr::GetInst()->ImgLoad(L"GAUGE_FILL", L"Image\\Fill.bmp");
	m_icon = ResMgr::GetInst()->ImgLoad(L"HEART_ICON", L"Image\\HeartIcon.bmp");
}
