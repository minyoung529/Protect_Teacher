#pragma once

enum class CHANGE_TYPE
{
	BK_COLOR,
	FONT_COLOR,
	NONE
};

class SelectGDI
{
private:
	HDC			m_hDC;
	HPEN		m_hDefaultPen;
	HBRUSH		m_hDefaultBrush;
	COLORREF	m_hDefaultColor;
	HFONT		m_hDefaultFont;
	HFONT		m_hNewFont;

	CHANGE_TYPE m_type;

public:
	SelectGDI(HDC _dc, PEN_TYPE _ePenType);
	SelectGDI(HDC _dc, BRUSH_TYPE _eBrushType);
	SelectGDI(HDC _dc, HFONT _font);
	SelectGDI(HDC _dc, COLORREF _color, CHANGE_TYPE type);
	~SelectGDI();
};

