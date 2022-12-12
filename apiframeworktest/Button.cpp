#include "pch.h"
#include "Button.h"
#include "Core.h"
#include "SceneMgr.h"
#include "func.h"
#include "KeyMgr.h"
#include "ResMgr.h"

Button::Button(Vec2 pos, Vec2 scale, ButtonType type)
	: m_buttonType(type)
{
	SetPos(pos);
	SetScale(scale);

	m_rect.left	= pos.x - scale.x / 2;
	m_rect.right	= pos.x + scale.x / 2;
	m_rect.top	= pos.y - scale.y / 2;
	m_rect.bottom = pos.y + scale.y / 2;

	switch (m_buttonType)
	{
	case ButtonType::Quit:
		m_image = ResMgr::GetInst()->ImgLoad(L"QUIT", L"Image\\QuitButton.bmp");
		break;

	case ButtonType::Game:
		m_image = ResMgr::GetInst()->ImgLoad(L"GAME", L"Image\\PlayButton.bmp");
		break;
	}
}

void Button::Update()
{
	POINT mousePos;
	GetCursorPos(&mousePos);

	if (KEY_TAP(KEY::LBTN) && PtInRect(&m_rect, mousePos))
	{
		OnClick();
	}
}

void Button::Render(HDC _dc)
{
	//TransparentBlt(_dc, m_rect.left, m_rect.right, GetScale().x, GetScale().y,
	//	m_image->GetDC(), 0, 0, m_image->GetWidth(), m_image->GetHeight(), RGB(255, 0, 255));

	StretchBlt(
		_dc,
		m_rect.left,
		m_rect.top,
		GetScale().x, GetScale().y,
		m_image->GetDC(),
		0, 0, m_image->GetWidth(), m_image->GetHeight(), SRCCOPY);
}

void Button::OnClick()
{
	switch (m_buttonType)
	{
	case ButtonType::Lobby:
		ChangeScene(SCENE_TYPE::LOBBY);
		break;

	case ButtonType::Quit:
		Core::GetInst()->SetGameOver(true);
		break;

	case ButtonType::Game:
		ChangeScene(SCENE_TYPE::START);
		break;
	}
}