#include "pch.h"
#include "Effect.h"
#include "Animator.h"
#include "ResMgr.h"
#include "Image.h"
#include "TimeMgr.h"
#include "func.h"

Effect::Effect(wstring effectName, BRUSH_TYPE type)
	: m_type(type)
{
	CreateAnimator();

	wstring fileName = L"Image\\" + effectName + L".bmp";
	Image* pImg = ResMgr::GetInst()->ImgLoad(effectName, fileName);
	

	GetAnimator()->CreateAnimation(effectName, pImg, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 27, 0.025f);
	GetAnimator()->Play(effectName, false);
	GetAnimator()->SetColor(RGB(0, 0, 0));
	GetAnimator()->SetScale(Vec2(2, 2));

	m_timer = 0.f;
	m_maxTime = 27 * 0.025f;
}

Effect::~Effect()
{
}

void Effect::Update()
{
	m_timer += TimeMgr::GetInst()->GetDT();
	GetAnimator()->Update();

	if (m_timer > m_maxTime)
	{
		DeleteObject(this);
	}
}

void Effect::Render(HDC _dc)
{
	Component_Render(_dc);
}