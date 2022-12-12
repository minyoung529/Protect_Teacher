#include "pch.h"
#include "Player.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Image.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include <Windows.h>
#include "Core.h"
Player::Player()
{
	isTime = true;
	time = 0;
	bulletCount = 3;
	// collider 새성
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f, 30.f));

	// image 업로드
	Image* pImg = ResMgr::GetInst()->ImgLoad(L"PlayerAni", L"Image\\jiwoo.bmp");

	// animator 생성 및 animation 사용
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Jiwoofront", pImg, Vec2(0.f, 150.f), Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.2f);
	GetAnimator()->Play(L"Jiwoofront", true);

	// animation offset 위로 올리기. 
	Animation* pAnim = GetAnimator()->FindAnimation(L"Jiwoofront");
	for (size_t i = 0; i < pAnim->GetMaxFrame(); i++)
		pAnim->GetFrame(i).vOffset = Vec2(10.f, -50.f);
}
Player::~Player()
{
	//if(nullptr !=m_pImage	)
	//	delete m_pImage;
}
void Player::Update()
{
	if (time < 0.1f)
	{
		time += DT;
	}
	else
	{
		isTime = true;
	}
	GetCursorPos(&mouse);
	if (KEY_TAP(KEY::LBTN))
	{
		CreateBullet(bulletCount, mouse);
	}

	GetAnimator()->Update();
}

void Player::CreateBullet(int _bulletCount, POINT& mouse)
{

	//ClientToScreen(Core::GetInst()->GetWndHandle(), &mouse);
	Vec2 mousePos = Vec2(mouse);
	Vec2 pos = GetPos();
	Vec2 mousePosition = Vec2(mousePos.x - pos.x, mousePos.y - pos.y);

	Vec2 dir = mousePos - pos;
	Vec2 vBulletPos = GetPos();

	Bullet* pBullet = new Bullet;
	pBullet->SetName(L"Bullet_Player");
	 pBullet->SetPos(vBulletPos);
	pBullet->SetScale(Vec2(25.f, 25.f));
	pBullet->SetDir(mousePosition.Normalize());

	for (int i = 0; i < _bulletCount; i++)
	{
		if (isTime)
		{
			time = 0;
			isTime = false;
			CreateObject(pBullet, GROUP_TYPE::BULLET_PLAYER);
		}
	}
}
void Player::Render(HDC _dc)
{
	Component_Render(_dc);
	/*int Width = (int)m_pImage->GetWidth();
	int Height = (int)m_pImage->GetHeight();

	Vec2 vPos = GetPos();*/
	//BitBlt(_dc
	//	,(int)(vPos.x - (float)(Width / 2))
	//	,(int)(vPos.y - (float)(Height / 2))
	//    , Width, Height
	//    , m_pImage->GetDC()
	//    , 0,0, SRCCOPY);

	//마젠타 색상 뺄때 transparent: 투명한
	//TransparentBlt(_dc
	//	, (int)(vPos.x - (float)(Width / 2))
	//	, (int)(vPos.y - (float)(Height / 2))
	//	,Width, Height
	//    , m_pImage->GetDC()
	//    ,0,0, Width, Height
	//    , RGB(255,0,255));

	Rectangle(_dc, GetPos().x, GetPos().y, GetPos().x + 10, GetPos().y + 10);

}
