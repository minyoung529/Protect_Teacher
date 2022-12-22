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
#include <wingdi.h>
#include "Resource.h"
#include "GameMgr.h"
#include "SelectGdi.h"
#include "DotObject.h"

Player::Player()
{

	delay = 0.07;
	i = 0;
	totalTime = 0;
	isTime = true;
	time = 0;
	bulletCount = 0;
	originalBulletCnt = 1;
	// collider 새성
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f, 30.f));
	speed = 3;
	angle = 0;
	// image 업로드
	Image* pImg = ResMgr::GetInst()->ImgLoad(L"PlayerAni", L"Image\\jiwoo.bmp");
	arrow = ResMgr::GetInst()->ImgLoad(L"Arrow", L"Image\\Arrow.bmp");

	// animator 생성 및 animation 사용
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Jiwoofront", pImg, Vec2(0.f, 150.f), Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.2f);
	GetAnimator()->Play(L"Jiwoofront", true);
}
Player::~Player()
{
	//if(nullptr !=m_pImage	)
	//	delete m_pImage;
}

void Player::Update()
{
	if (isOver)
	{
		overTimer += DT;

		if (overTimer > 2.f)
		{
			ChangeScene(SCENE_TYPE::GAMEOVER);
		}

		return;
	}

	totalTime += DT;

	angle += speed * DT;
	if (angle > 360.0f)
		angle = 0;

	Rotate(angle);

	if (KEY_AWAY(KEY::LBTN) && GameMgr::GetInst()->GetCanAttack())
	{
		GameMgr* mgr = GameMgr::GetInst();
		mgr->SetCanAttack(false);

		bulletCount = originalBulletCnt;
		Vec2 mousePos = Vec2(KeyMgr::GetInst()->GetMousePos());
		pos = GetPos();
		mousePosition = Vec2(mousePos.x - pos.x, mousePos.y - pos.y);
	}

	if (bulletCount >= 1 && totalTime > delay)
	{
		Vec2 vBulletPos = GetPos();
		//delete pBullet;
		pBullet = new Bullet();
		pBullet->SetName(L"Bullet_Player");
		pBullet->SetPos(vBulletPos);
		pBullet->SetScale(Vec2(25.f, 25.f));
		pBullet->SetDir(mousePosition.Normalize());
		totalTime = 0;
		bulletCount--;

		SceneMgr::GetInst()->GetCurScene()->AddObject(pBullet, GROUP_TYPE::BULLET_PLAYER);
	}

	GetAnimator()->Update();
}

void Player::CreateBullet(POINT& mouse)
{
}
void Player::EnterCollision(Collider* _pOther, RECT colRt)
{
	if (_pOther->GetObj()->GetName() == L"Enemy")
	{
		if (isOver)return;

		DotObject* dot = new DotObject(DotColor::Black, 1.99f, true, 0);
		dot->SetScale(Vec2(1000, 1000));
		dot->SetPos(Vec2(400, 400));
		CreateObject(dot, GROUP_TYPE::UI);
		isOver = true;
	}
}
void Player::Rotate(float _angle)
{
	float theta = _angle * M_PI / 180.0f;
	float s = sinf(theta);
	float c = cosf(theta);

	float posXSrcL = arrow->GetWidth();
	float posYSrcL = arrow->GetHeight();
	float posXSrcR = arrow->GetWidth() * -2;
	float posYScrR = arrow->GetHeight() * -2;

	dot[0].x = (LONG)(s);
	dot[0].y = (LONG)(c);
	dot[1].x = (LONG)(s);
	dot[1].y = (LONG)(c);
	dot[2].x = (LONG)(s);
	dot[2].y = (LONG)(c);
}
void Player::Render(HDC _dc)
{

	int arrowWidth = (int)arrow->GetWidth();
	int arrowHeight = (int)arrow->GetHeight();
	Vec2 pos = GetPos();
	PlgBlt(_dc, dot, _dc, pos.x - arrowWidth / 2, pos.y - arrowHeight / 2, arrowWidth, arrowHeight, NULL, 0, 0);

	Vec2 vPos = GetPos();
	//TransparentBlt(_dc, (int)(vPos.x - (float)(arrowWidth / 2))
	//	, (int)(vPos.y - (float)(arrowHeight / 2))
	//	, arrowWidth, arrowHeight
	//	, arrow->GetDC()
	//	, 0, 0, arrowWidth, arrowWidth
	//	, RGB(255, 255, 255));
	//BitBlt(_dc, (int)(vPos.x - (float)(arrowWidth / 2))
	//	, (int)(vPos.y - (float)(arrowHeight / 2))
	//	, arrowWidth, arrowHeight
	//	, arrow->GetDC()
	//	, 0, 0, SRCCOPY);

	if (KEY_HOLD(KEY::LBTN))
		DrawDottedLine(_dc);

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
}

void Player::DrawDottedLine(HDC _dc)
{
	Vec2 pos = GetPos();
	Vec2 dir = Vec2(KeyMgr::GetInst()->GetMousePos()) - pos;
	dir.Normalize();

	SelectGDI s(_dc, BRUSH_TYPE::GREEN);

	for (int i = 0; i < 7; i++)
	{
		pos += dir * 15.f;
		Ellipse(_dc, pos.x - 3, pos.y - 3, pos.x + 3, pos.y + 3);
	}
}
