#pragma once
#include "Object.h"

class HeartObject : public Object
{
public:
	HeartObject(int idx);
	~HeartObject();
	CLONE(HeartObject);

public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

private:
	float m_timer = 0.f;
	const float m_maxTime;
	float m_speed;

	Vec2 m_directions[4];
};

