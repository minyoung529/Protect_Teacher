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
Player::Player()
{
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
	for(size_t i=0;i<pAnim->GetMaxFrame();i++)
		pAnim->GetFrame(i).vOffset = Vec2(10.f, -50.f);
}
Player::~Player()
{
	//if(nullptr !=m_pImage)
	//	delete m_pImage;
}
void Player::Update()
{
	Vec2 vPos = GetPos();
	if(KEY_HOLD(KEY::UP))
	{
		vPos.y -= 300.f * fDT;
	}
	if (KEY_HOLD(KEY::DOWN))
	{
		vPos.y += 300.f * fDT;
	}
	if (KEY_HOLD(KEY::LEFT))
	{
		vPos.x -= 300.f * fDT;
	}
	if (KEY_HOLD(KEY::RIGHT))
	{
		vPos.x += 300.f * fDT;
	}
	if (KEY_TAP(KEY::SPACE))
	{
		CreateBullet();
	}
	SetPos(vPos);
	GetAnimator()->Update();
}

void Player::CreateBullet()
{
	Vec2 vBulletPos = GetPos();
	vBulletPos.y -= GetScale().y / 2.f;

	// 
	Bullet* pBullet = new Bullet;
	pBullet->SetName(L"Bullet_Player");
	pBullet->SetPos(vBulletPos);
	pBullet->SetScale(Vec2(25.f, 25.f));
	pBullet->SetDir(Vec2(0.f, -1.f));
	CreateObject(pBullet, GROUP_TYPE::BULLET_PLAYER);
	//Scene* pCurScene = SceneMgr::GetInst()->GetCurScene();
	//pCurScene->AddObject(pBullet,GROUP_TYPE::BULLET);
}
void Player::Render(HDC _dc)
{
	Component_Render(_dc);
}
