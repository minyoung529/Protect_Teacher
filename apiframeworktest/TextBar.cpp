#include "pch.h"
#include "TextBar.h"
#include "ResMgr.h"
#include "GameMgr.h"

TextBar::TextBar(TextType type, int m_imgScale)
	: m_type(type)
	, m_imgScale(m_imgScale)
{
	switch (type)
	{
	case TextType::Score:
		m_image = ResMgr::GetInst()->ImgLoad(L"Score", L"Image\\Score.bmp");
		break;

	case TextType::HighScore:
		m_image = ResMgr::GetInst()->ImgLoad(L"HighScore", L"Image\\HighScore.bmp");
		break;
	}
}

TextBar::~TextBar()
{
}

void TextBar::Update()
{
}

void TextBar::Render(HDC _dc)
{
	SetTextAlign(_dc, TA_LEFT);

	TransparentBlt(_dc, GetPos().x, GetPos().y, m_imgScale, m_imgScale,
		m_image->GetDC(), 0, 0, m_image->GetWidth(), m_image->GetHeight(), RGB(255, 0, 255));

	switch (m_type)
	{
		wchar_t s_hp[6];

	case TextType::Score:
		wsprintf(s_hp, L"x %d", GameMgr::GetInst()->GetScore());
		TextOut(_dc, GetPos().x + m_imgScale + 10, GetPos().y + m_imgScale / 2 - 10, s_hp, lstrlen(s_hp));
		break;

	case TextType::HighScore:
		wsprintf(s_hp, L"x %d", GameMgr::GetInst()->GetHighScore());
		TextOut(_dc, GetPos().x + m_imgScale + 10, GetPos().y + m_imgScale / 2 - 10, s_hp, lstrlen(s_hp));
		break;
	}
}