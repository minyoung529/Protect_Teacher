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
	TextBar(TextType type, int imgScale);
	TextBar(TextType type, int imgScale, int fontSize);
	TextBar(wstring text, int fontSize);
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
	wstring m_text;

public:
	CLONE(TextBar);
};

