#include "pch.h"
#include "Player.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Bullet.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Core.h"
#include "Resource.h"
#include "GameMgr.h"
#include "DotObject.h"
#include "SoundMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "SelectGdi.h"

Player::Player()
{
	delay = 0.07;
	totalTime = 0;
	isTime = true;
	time = 0;
	bulletCount = 0;
	originalBulletCnt = 1;
	speed = 3;
	CreateCollider();
	GetCollider()->SetScale(Vec2(16 * 2.5f, 16 * 2.5f));

	CreateAnimator();

	// Idle Animation
	{
		Image* pImg = ResMgr::GetInst()->ImgLoad(L"PlayerIdle", L"Image\\Player\\Idle.bmp");
		GetAnimator()->CreateAnimation(L"PlayerIdle", pImg, Vec2(0.f, 0.f), Vec2(16.f, 16.f), Vec2(16.f, 0.f), 2, 0.2f);
		GetAnimator()->SetScale(Vec2(2.5f, 2.5f));

		Animation* pAnim = GetAnimator()->FindAnimation(L"PlayerIdle");
		for (size_t i = 0; i < pAnim->GetMaxFrame(); i++)
			pAnim->GetFrame(i).vOffset = Vec2(-12.f, -16.f);
	}

	// Attack Animation
	{
		Image* pImg = ResMgr::GetInst()->ImgLoad(L"PlayerAttack", L"Image\\Player\\Attack.bmp");
		GetAnimator()->CreateAnimation(L"PlayerAttack", pImg, Vec2(0.f, 0.f), Vec2(16.f, 18.f), Vec2(16.f, 0.f), 4, 0.1f);
		GetAnimator()->SetScale(Vec2(2.5f, 2.5f));

		Animation* pAnim = GetAnimator()->FindAnimation(L"PlayerAttack");
		for (size_t i = 0; i < pAnim->GetMaxFrame(); i++)
			pAnim->GetFrame(i).vOffset = Vec2(-12.f, -16.f);
	}

	// Bullet Sound
	{
		SoundMgr::GetInst()->LoadSound(L"BULLET", false, L"Sound\\Bullet.mp3");
	}
	
	GetAnimator()->Play(L"PlayerIdle", true);
}
Player::~Player()
{
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

	if (isAttacking)
	{
		animTimer += DT;

		if (animTimer >= 0.4f)
		{
			GetAnimator()->Play(L"PlayerIdle", true);
			isAttacking = false;
			animTimer = 0.f;
		}
	}

	if (KEY_AWAY(KEY::LBTN) && GameMgr::GetInst()->GetCanAttack())
	{
		GameMgr* mgr = GameMgr::GetInst();
		mgr->SetCanAttack(false);

		bulletCount = originalBulletCnt;
		Vec2 mousePos = Vec2(KeyMgr::GetInst()->GetMousePos());
		Vec2 pos = GetPos();
		mousePosition = Vec2(mousePos.x - pos.x, mousePos.y - pos.y);

		GetAnimator()->Play(L"PlayerAttack", true);
		isAttacking = true;
	}

	if (bulletCount >= 1 && totalTime > delay)
	{
		SoundMgr::GetInst()->Play(L"BULLET");
		Vec2 vBulletPos = GetPos();
		Bullet* pBullet = new Bullet();
		pBullet->SetName(L"Bullet_Player");
		pBullet->SetPos(vBulletPos);
		pBullet->SetScale(Vec2(25.f, 25.f));
		pBullet->SetDir(mousePosition.Normalize());
		totalTime = 0;
		bulletCount--;

		SceneMgr::GetInst()->GetCurScene()->AddObject(pBullet, GROUP_TYPE::BULLET_PLAYER);
		//CreateObject(pBullet, GROUP_TYPE::BULLET_PLAYER);
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
void Player::Render(HDC _dc)
{
	if (KEY_HOLD(KEY::LBTN) && GameMgr::GetInst()->GetCanAttack())
		DrawDottedLine(_dc);

	wchar_t bulletCnt[4];
	wsprintf(bulletCnt, L"%d", originalBulletCnt);
	TextOut(_dc, GetPos().x + 20, GetPos().y - 20, bulletCnt, lstrlen(bulletCnt));

	Component_Render(_dc);
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
