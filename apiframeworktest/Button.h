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

class Button : public Object
{
public:
	Button(Vec2 pos, Vec2 scale, ButtonType type);

public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

private:
	virtual void OnClick();

private:
	ButtonType m_buttonType;
	RECT m_rect;
	Image* m_image;

public:
	CLONE(Button)
};

