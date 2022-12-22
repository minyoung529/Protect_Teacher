#pragma once
#include "Object.h"

enum class DotColor
{
	Black,
	Red, 
	Orange,
	Yellow,
	Green,
	Blue,
	Purple,
	Length,
	Rainbow
};

class DotObject : public Object
{
public:
	DotObject(float rate, float time);
	DotObject(DotColor color, float time);
	DotObject(DotColor color, float time, bool reverse, int size);
	CLONE(DotObject)

public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

private:
	float m_timer;
	float m_maxTime;
	float alpha;
	class Image* m_pImage;

	bool m_reverse;
	int m_size;
};

