#include "pch.h"
#include "HeartObject.h"
#include "Animator.h"
#include "Animation.h"
#include "ResMgr.h"
#include "TimeMgr.h"

HeartObject::HeartObject(int idx)
	: m_timer(0.f)
	, m_maxTime(1.f)
	, m_speed(30.f)
{
	CreateAnimator();
	wstring animName = L"HEART_ANIM";
	wstring path = L"Image\\HeartAnim";

	if (idx > 0)
	{
		animName += to_wstring(idx);
		path += to_wstring(idx);
	}

	Image* img = ResMgr::GetInst()->ImgLoad(animName, path + L".bmp");

	GetAnimator()->CreateAnimation(animName, img, Vec2(0.f, 0.f), Vec2(83.f, 73.f), Vec2(83.f, 0.f), 3, 1.f);
	GetAnimator()->Play(animName, true);
	GetAnimator()->SetScale(Vec2(0.3f, 0.3));

	Animation* pAnim = GetAnimator()->FindAnimation(animName);
	for (size_t i = 0; i < pAnim->GetMaxFrame(); i++)
		pAnim->GetFrame(i).vOffset = Vec2(25, 25);

	if (idx % 2 == 0)
	{
		m_directions[0] = Vec2(-1, -1);
		m_directions[1] = Vec2(1, 1);
		m_directions[2] = Vec2(1, -1);
		m_directions[3] = Vec2(-1, 1);
	}
	else
	{
		m_directions[0] = Vec2(-1, 1);
		m_directions[1] = Vec2(1, -1);
		m_directions[2] = Vec2(1, 1);
		m_directions[3] = Vec2(-1, -1);
	}
}

HeartObject::~HeartObject()
{
}

void HeartObject::Update()
{
	float dt = TimeMgr::GetInst()->GetfDT();
	m_timer += dt;
	Vec2 pos = GetPos();

	if (m_timer > m_maxTime)
		m_timer = 0.f;

	for (int i = 3; i >= 0; i--)
	{
		if (m_timer > m_maxTime * i / 4)
		{
			pos += m_directions[i] * m_speed * dt;
			break;
		}
	}

	SetPos(pos);
	GetAnimator()->Update();
}

void HeartObject::Render(HDC _dc)
{
	Component_Render(_dc);
}
