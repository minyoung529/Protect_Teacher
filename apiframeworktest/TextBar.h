#pragma once
#include "Object.h"
#include "Image.h"

enum struct TextType
{
	None,
	Score,
	HighScore,
	Length
};

class TextBar : public Object
{
public:
	TextBar(TextType type, int m_imgScale);
	TextBar(TextType type, int m_imgScale, int fontSize);
	~TextBar();

public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

public:
	void SetAlign(UINT align) { m_align = align; }

private:
	TextType m_type;
	Image* m_image;
	int m_imgScale;
	UINT m_align;
	HFONT m_font;
	int m_fontSize;

public:
	CLONE(TextBar);
};

