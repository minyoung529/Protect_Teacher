#include "pch.h"
#include "SkillGauge.h"
#include "ResMgr.h"
#include "KeyMgr.h"
#include "GameMgr.h"
#include "SelectGDI.h"
#include "TimeMgr.h"

SkillGauge::SkillGauge()
	: m_max(0)
	, m_val(0)
{
	SetValue();
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
	int curGauge = GameMgr::GetInst()->GetCurGauge();
	int max = GameMgr::GetInst()->GetMaxGauge();

	if ((int)m_val != curGauge)
	{
		if (m_val < curGauge)
			m_val += DT * 10.f;
		else
			m_val -= DT * 50.f;

		if (m_val > max)
			m_val = max;
		if (m_val < 0.f)
			m_val = 0.f;
	}
}

void SkillGauge::Render(HDC _dc)
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();
	Vec2 center = { pos.x + scale.x / 2, pos.y + scale.y / 2 };

	SetBkMode(_dc, TRANSPARENT);

	// Gauge
	{
		float rate = GetRate();

		TransparentBlt(_dc, center.x, center.y, m_backImg->GetWidth(), m_backImg->GetHeight(),
			m_backImg->GetDC(), 0, 0, m_backImg->GetWidth(), m_backImg->GetHeight(), RGB(255, 0, 255));

		TransparentBlt(_dc, center.x, center.y, m_fillImg->GetWidth() * rate, m_fillImg->GetHeight(),
			m_fillImg->GetDC(), 0, 0, m_fillImg->GetWidth() * rate, m_fillImg->GetHeight(), RGB(255, 0, 255));

		wchar_t str[5];
		wsprintf(str, L"%d%%", (int)(((int)m_val * 100) / m_max));

		TextOut(_dc, pos.x + m_fillImg->GetWidth() / 2 - 10, center.y + m_fillImg->GetHeight() / 4, str, lstrlen(str));
	}

	// StoryText
	{
		HFONT font = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
			VARIABLE_PITCH | FF_ROMAN, TEXT("맑은 고딕"));

		SelectGDI s(_dc, font);
		SetTextAlign(_dc, TA_CENTER);

		wstring storyText = L"스킬이 사용되면 적들이 모두 한 방입니다!";
		TextOut(_dc, pos.x + m_fillImg->GetWidth()/2, center.y + 30, storyText.c_str(), storyText.length());

		SetTextAlign(_dc, TA_LEFT);
	}

	SetBkMode(_dc, OPAQUE);
}

void SkillGauge::SetValue()
{
	m_backImg = ResMgr::GetInst()->ImgLoad(L"GAUGE_BACK", L"Image\\Gauge.bmp");
	m_fillImg = ResMgr::GetInst()->ImgLoad(L"GAUGE_FILL", L"Image\\Fill.bmp");
	m_icon = ResMgr::GetInst()->ImgLoad(L"HEART_ICON", L"Image\\HeartIcon.bmp");

	m_max = GameMgr::GetInst()->GetMaxGauge();
	m_val = 0;
}
