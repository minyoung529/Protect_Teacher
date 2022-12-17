#pragma once
#include "Object.h"
#include "Image.h"

class SkillGauge : public Object
{
public:
	SkillGauge();
	SkillGauge(int max, int val);
	SkillGauge(Vec2 scale);
	virtual ~SkillGauge();
	CLONE(SkillGauge);

public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

private:
	float GetRate()
	{
		if (m_max == 0) return 0;
		return m_val / (float)m_max;
	}

	void SetValue();

private:
	int m_max;
	float m_val;

	Image* m_backImg;
	Image* m_fillImg;
	Image* m_icon;
};

