#pragma once
#include "Object.h"

enum struct TextType
{
	Score,
	HighScore
};

class TextBar : public Object
{
public:
	TextBar(TextType type);
	~TextBar();

private:
	TextType m_type;
};

