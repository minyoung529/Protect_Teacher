#pragma once
#include "Object.h"
class WallBall :  public Object
{
public:
	WallBall();
	virtual ~WallBall();
	CLONE(WallBall)

public:
	virtual void Update() override;

private:
	POINT m_resolution;
	Vec2 m_direction;
	float m_speed;
};

