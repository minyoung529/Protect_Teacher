#include "pch.h"
#include "Bullet.h"
#include "TimeMgr.h"
#include "Image.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Core.h"
#include "Player.h"
Bullet::Bullet()
	: m_fTheta(3.f * M_PI / 2.f)
	, m_vDir(Vec2(1.f, 1.f))
{
	m_pImage = ResMgr::GetInst()->ImgLoad(L"Heart", L"Image\\Heart.bmp");
	m_vDir.Normalize();
	CreateCollider();
	GetCollider()->SetScale(Vec2(15.f, 15.f));
}

Bullet::~Bullet()
{
}


void Bullet::Update()
{
	Vec2 vPos = GetPos();
	//vPos.x += 700.f * fDT; 
	//vPos.y += 700.f * fDT * m_fDir;
	//vPos.x += 700.f * cosf(m_fTheta) * fDT;
	//vPos.y -= 700.f * sinf(m_fTheta) * fDT;
	vPos.x += 700.f * m_vDir.x * fDT;
	vPos.y += 700.f * m_vDir.y * fDT;

	Vec2 res = Core::GetInst()->GetResolution();

	if (vPos.x < 0 || vPos.y < 0 || vPos.x > res.x || vPos.y > res.y)
	{
		DeleteObject(this);
		return;
	}

	SetPos(vPos);
}

void Bullet::Render(HDC _dc)
{
	int Width = (int)m_pImage->GetWidth();
	int Height = (int)m_pImage->GetHeight();

	Vec2 vPos = GetPos();
	//¸¶Á¨Å¸ »ö»ó »¬¶§ transparent: Åõ¸íÇÑ
	TransparentBlt(_dc
		, (int)(vPos.x - (float)(Width / 2))
		, (int)(vPos.y - (float)(Height / 2))
		, Width, Height
		, m_pImage->GetDC()
		, 0, 0, Width, Height
		, RGB(255, 255, 255));
	Component_Render(_dc);
}

void Bullet::EnterCollision(Collider* _pOther, RECT colRt)
{
	Player* player = new Player{};
	Vec2 bulletPos;
	Vec2 reflection;
	Vec2 direction;
	Vec2 normalVec;

	Vec2 monsterPos = _pOther->GetObj()->GetPos();
	Vec2 monsterScale = _pOther->GetObj()->GetScale();

	RECT rt =
	{
		(LONG)(monsterPos.x - monsterScale.x / 2),
		(LONG)(monsterPos.y - monsterScale.y / 2),
		(LONG)(monsterPos.x + monsterScale.x / 2),
		(LONG)(monsterPos.y + monsterScale.y / 2),
	};

	if (rt.left == colRt.left || rt.right == colRt.right)
	{
		m_vDir = Vec2(-m_vDir.x, m_vDir.y);
	}
	else if (rt.bottom == colRt.bottom || rt.top == colRt.top)
	{
		m_vDir = Vec2(m_vDir.x, -m_vDir.y);
	}
	/*else if((rt.left ==colRt.left && rt.bottom == colRt.bottom) || rt.left == colRt.left && ry )*/
}
