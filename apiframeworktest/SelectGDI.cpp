#include "pch.h"
#include "SelectGDI.h"
#include "Core.h"
SelectGDI::SelectGDI(HDC _dc, PEN_TYPE _ePenType)
	: m_hDC(_dc)
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr)
	, m_hDefaultFont(nullptr)
	, m_type(CHANGE_TYPE::NONE)
{
	HPEN hColorPen = Core::GetInst()->GetPen(_ePenType);
	m_hDefaultPen = (HPEN)SelectObject(_dc, hColorPen);
}

SelectGDI::SelectGDI(HDC _dc, BRUSH_TYPE _eBrushType)
	: m_hDC(_dc)
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr)
	, m_hDefaultFont(nullptr)
	, m_type(CHANGE_TYPE::NONE)
{
	HBRUSH hColorBrush = Core::GetInst()->GetBrush(_eBrushType);
	m_hDefaultBrush = (HBRUSH)SelectObject(_dc, hColorBrush);
}

SelectGDI::SelectGDI(HDC _dc, HFONT _font)
	: m_hDC(_dc)
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr)
	, m_hDefaultFont(nullptr)
	, m_type(CHANGE_TYPE::NONE)

{
	m_hNewFont = _font;
	m_hDefaultFont = (HFONT)SelectObject(_dc, m_hNewFont);
}

SelectGDI::SelectGDI(HDC _dc, COLORREF _color, CHANGE_TYPE type)
	: m_hDC(_dc)
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr)
	, m_hDefaultFont(nullptr)
	, m_type(type)
{
	switch (m_type)
	{
	case CHANGE_TYPE::BK_COLOR:
		m_hDefaultColor = SetBkColor(_dc, _color);
		break;

	case CHANGE_TYPE::FONT_COLOR:
		m_hDefaultColor = SetTextColor(_dc, _color);
		break;
	}
}

SelectGDI::~SelectGDI()
{
	SelectObject(m_hDC, m_hDefaultPen);
	SelectObject(m_hDC, m_hDefaultBrush);
	SelectObject(m_hDC, m_hDefaultFont);

	if (m_hNewFont)
		DeleteObject(m_hNewFont);

	switch (m_type)
	{
	case CHANGE_TYPE::BK_COLOR:
		SetBkColor(m_hDC, m_hDefaultColor);
		break;

	case CHANGE_TYPE::FONT_COLOR:
		SetTextColor(m_hDC, m_hDefaultColor);
		break;
	}
}