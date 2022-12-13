#pragma once
#include "Object.h"
#include "Image.h"

enum struct TextType
{
	Score,
	HighScore
};

class TextBar : public Object
{
public:
	TextBar(TextType type, int m_imgScale);
	~TextBar();

public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

private:
	TextType m_type;
	Image* m_image;
	int m_imgScale;

public:
	CLONE(TextBar);
};

