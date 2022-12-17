#pragma once
#include "Object.h"

class Image;

class FollowHeart : public Object
{
public:
	FollowHeart();
	~FollowHeart();
	CLONE(FollowHeart);	

public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

private:
	void CreateDot(float rate);
	float GetDist(Vec2 one, Vec2 two);

private:
	Vec2 m_target;
	Vec2 m_dir;
	Image* m_image;
	int m_imgScale;

	float m_speed;
	float m_damping;
	float m_dist;

	float m_accDist;
	float m_curDist;
};

