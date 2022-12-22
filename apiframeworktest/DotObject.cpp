#include "pch.h"
#include "DotObject.h"
#include "TimeMgr.h"
#include "Image.h"
#include "ResMgr.h"

DotObject::DotObject(float rate, float time)
	: m_timer(0.f)
	, m_maxTime(time)
	, alpha(255)
	, m_reverse(false)
	, m_size(0)
{
	wstring number = to_wstring((int)(rate * (int)DotColor::Length - 1) + 1);
	m_pImage = ResMgr::GetInst()->ImgLoad(L"DOT" + number, L"Image\\Dots\\Dot" + number + L".bmp");
}

DotObject::DotObject(DotColor color, float time)
	: m_timer(0.f)
	, m_maxTime(time)
	, alpha(255)
	, m_reverse(false)
	, m_size(0)
{
	wstring number = to_wstring((int)color);
	m_pImage = ResMgr::GetInst()->ImgLoad(L"DOT" + number, L"Image\\Dots\\Dot" + number + L".bmp");
}

DotObject::DotObject(DotColor color, float time, bool reverse, int size)
	: m_timer(0.f)
	, m_maxTime(time)
	, m_reverse(reverse)
	, m_size(size)
{
	wstring number = to_wstring((int)color);
	m_pImage = ResMgr::GetInst()->ImgLoad(L"DOT" + number, L"Image\\Dots\\Dot" + number + L".bmp");

	if (reverse)
		alpha = 0;
	else
		alpha = 255;
}

void DotObject::Update()
{
	m_timer += DT;

	if (!m_reverse)
	{
		alpha -= DT * 255 / m_maxTime;

		if (alpha < 0)
			alpha = 0;
	}
	else
	{
		alpha += DT * 255 / m_maxTime;

		if (alpha > 255)
			alpha = 255;
	}

	if (m_timer > m_maxTime)
	{
		DeleteObject(this);
	}
}

void DotObject::Render(HDC _dc)
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	BLENDFUNCTION blend;
	blend.BlendOp = blend.BlendFlags = blend.AlphaFormat = 0;
	blend.SourceConstantAlpha = (BYTE)alpha;

	GdiAlphaBlend(_dc, pos.x - scale.x / 2 - m_size, pos.y - scale.y / 2 - m_size, scale.x + m_size, scale.y + m_size,
		m_pImage->GetDC(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), blend);
}