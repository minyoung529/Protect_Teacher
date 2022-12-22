#include "pch.h"
#include "Button.h"
#include "Core.h"
#include "SceneMgr.h"
#include "func.h"
#include "KeyMgr.h"
#include "ResMgr.h"
#include "SelectGDI.h"
#include "TimeMgr.h"
#include "SoundMgr.h"

Button::Button(Vec2 pos, Vec2 scale, ButtonType type)
	: m_buttonType(type)
{
	SetPos(pos);
	SetScale(scale);

	switch (m_buttonType)
	{
	case ButtonType::Quit:
		m_image = ResMgr::GetInst()->ImgLoad(L"QUIT", L"Image\\QuitButton.bmp");
		break;

	case ButtonType::Game:
		m_image = ResMgr::GetInst()->ImgLoad(L"GAME", L"Image\\PlayButton.bmp");
		break;
	}

	m_selectImage = ResMgr::GetInst()->ImgLoad(L"SELECT", L"Image\\SelectButton.bmp");
	m_pushImage = ResMgr::GetInst()->ImgLoad(L"PUSH", L"Image\\PushButton.bmp");

	SoundMgr::GetInst()->LoadSound(L"CLICK", false, L"Sound\\Click.mp3");

	m_rect.left = pos.x - m_image->GetWidth() / 2 * scale.x;
	m_rect.right = pos.x + m_image->GetWidth() / 2 * scale.x;
	m_rect.top = pos.y - m_image->GetHeight() / 2 * scale.y;
	m_rect.bottom = pos.y + m_image->GetHeight() / 2 * scale.y;
}

Button::Button(Vec2 pos, Vec2 scale, ButtonType type, wstring name) : Button(pos, scale, type)
{
	m_name = name;
}

void Button::Update()
{
	ClickCheck();

	if (m_buttonType == ButtonType::Game)
	{
		m_timer += DT;

		if (m_timer > m_maxTime)
			m_timer = 0.f;

		else if (m_timer < m_maxTime / 2)
		{
			m_scalePlus += DT * 20.f;
		}
		else
		{
			m_scalePlus -= DT * 20.f;
		}
	}
}

void Button::Render(HDC _dc)
{
	Image* img = nullptr;

	switch (m_state)
	{
	case ButtonState::None:
		img = m_image;
		break;

	case ButtonState::Push:
		img = m_pushImage;
		break;

	case ButtonState::Select:
		img = m_selectImage;
		break;
	}

	if (img)
	{
		TransparentBlt(
			_dc,
			m_rect.left - m_scalePlus / 2 ,
			m_rect.top - m_scalePlus  / 2 ,
			img->GetWidth() * GetScale().x + m_scalePlus , img->GetHeight() * GetScale().y + m_scalePlus,
			img->GetDC(),
			0, 0, img->GetWidth(), img->GetHeight(), RGB(255, 0, 255));
	}

	SetTextAlign(_dc, TA_CENTER);
	SetBkMode(_dc, TRANSPARENT);

	SelectGDI s(_dc, CreateFont(40, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("여기어때 잘난체")));
	SelectGDI s1(_dc, RGB(255, 255, 255), CHANGE_TYPE::FONT_COLOR);

	if (m_name.empty())
	{
		switch (m_buttonType)
		{
		case ButtonType::Quit:
			TextOut(_dc, GetPos().x, GetPos().y - 20, L"Quit...", lstrlen(L"Quit..."));
			break;

		case ButtonType::Game:
			TextOut(_dc, GetPos().x, GetPos().y - 20, L"Play!", lstrlen(L"Play!"));
			break;
		}
	}
	else
	{
		TextOut(_dc, GetPos().x, GetPos().y - 20, m_name.c_str(), lstrlen(m_name.c_str()));
	}

	SetBkMode(_dc, OPAQUE);
	SetTextAlign(_dc, TA_LEFT);
}

void Button::OnClick()
{
	SoundMgr::GetInst()->Play(L"CLICK");

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

void Button::ClickCheck()
{
	POINT mousePos;
	GetCursorPos(&mousePos);
	ScreenToClient(Core::GetInst()->GetWndHandle(), &mousePos);

	if (PtInRect(&m_rect, mousePos))
	{
		if (KEY_AWAY(KEY::LBTN))
		{
			OnClick();
		}
		else if (KEY_HOLD(KEY::LBTN))
		{
			m_state = ButtonState::Push;
		}
		else
		{
			m_state = ButtonState::Select;
		}
	}
	else
	{
		m_state = ButtonState::None;
	}
}