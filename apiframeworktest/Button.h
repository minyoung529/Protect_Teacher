#pragma once
#include "Object.h"
#include "Image.h"

enum class ButtonType
{
	Lobby,
	Quit,
	Game,
	Help,
	Length
};

enum class ButtonState
{
	None,
	Select,
	Push
};

class Button : public Object
{
public:
	Button(Vec2 pos, Vec2 scale, ButtonType type);

public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

private:
	virtual void OnClick();
	virtual void ClickCheck();

private:
	ButtonType m_buttonType;
	ButtonState m_state = ButtonState::None;
	RECT m_rect;
	Image* m_image;
	Image* m_selectImage;
	Image* m_pushImage;

private:
	float m_scalePlus = 0.f;
	float m_timer;
	const float m_maxTime = 1.f;

public:
	CLONE(Button)
};

