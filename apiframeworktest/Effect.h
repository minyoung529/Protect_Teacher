#pragma once
#include "Object.h"

class Image;

class Effect : public Object
{
public:
	Effect(wstring effectName, BRUSH_TYPE m_type);
	~Effect();
	CLONE(Effect);

public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
	
private:
	BRUSH_TYPE m_type;
	float m_timer;
	float m_maxTime;
};

