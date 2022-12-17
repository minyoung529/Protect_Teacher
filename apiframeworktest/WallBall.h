#pragma once
#include "Object.h"
class WallBall : public Object
{
public:
	WallBall(Vec2 direction);
	virtual ~WallBall();
	CLONE(WallBall)

public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

private:
	void CreateDot();
	bool CheckLimit();

private:
	POINT m_resolution;
	Vec2 m_direction;
	float m_speed;
	class Image* m_pImage;

	float m_curScale = 0.f;
	float m_timer;

	float m_dist;
	int dotCnt = 0;

	const float m_maxTime = 1.f;
	const float m_scaleIncrease = 30.f;
};

