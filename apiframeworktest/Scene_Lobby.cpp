#include "pch.h"
#include "Scene_Lobby.h"
#include "Button.h"
#include "Core.h"
#include "Effect.h"
#include "HeartObject.h"
#include "WallBall.h"
#include "SoundMgr.h"
#include "TextBar.h"
#include "SelectGdi.h"

Scene_Lobby::Scene_Lobby()
{
}

Scene_Lobby::~Scene_Lobby()
{
}

void Scene_Lobby::Enter()
{
	SoundMgr::GetInst()->LoadSound(L"LOBBY_BGM", true, L"Sound\\LobbyBGM.mp3");
	SoundMgr::GetInst()->Play(L"LOBBY_BGM");

	Vec2 centerPos = Core::GetInst()->GetResolution();
	centerPos.x /= 2; centerPos.y /= 2;

	// Buttons
	{
		Object* button = new Button(centerPos, Vec2(1.f, 1.f), ButtonType::Game);
		CreateObject(button, GROUP_TYPE::UI);

		button = new Button(centerPos + Vec2(0.f, 100.f), Vec2(1.f, 1.f), ButtonType::Quit);
		CreateObject(button, GROUP_TYPE::UI);
	}

	{
		Object* textBar = new TextBar(L"선생님을 지켜요!", 60);
		textBar->SetPos(centerPos - Vec2(0.f, 200.f));
		CreateObject(textBar, GROUP_TYPE::UI);
	}


	// background Heart
	{
		POINT res = Core::GetInst()->GetResolution();
		int vHeart = 5, hHeart = 5;
		int vSpace, hSpace;
		int space = 75;

		vSpace = (res.y - space * 2) / (vHeart - 1);
		hSpace = (res.x - space * 2) / (hHeart - 1);

		for (int i = 0; i < vHeart; i++)
		{
			for (int j = 0; j < hHeart; j++)
			{
				HeartObject* heart = new HeartObject(i % 3);
				heart->SetPos(Vec2(j * hSpace + space, i * vSpace + space));
				CreateObject(heart, GROUP_TYPE::DEFAULT);
			}
		}
	}

	// moving heart
	{
		for (int i = 0; i < 3; i++)
		{
			int randX = rand() % 200;
			int randY = rand() % 200;

			Vec2 dir = Vec2((randX - 100) / 100.f, (randY - 100) / 100.f);
			Object* obj = new WallBall(dir.Normalize());
			CreateObject(obj, GROUP_TYPE::EFFECT);
		}
	}
}

void Scene_Lobby::Exit()
{
	DeleteAll();
}

void Scene_Lobby::Render(HDC _dc)
{
	Scene::Render(_dc);

	// StoryText
	{
		Vec2 centerPos = Core::GetInst()->GetResolution();
		centerPos.y /= 9;
		centerPos.x /= 2;

		HFONT font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
				VARIABLE_PITCH | FF_ROMAN, TEXT("맑은 고딕"));

		SelectGDI s(_dc, font);
		SetTextAlign(_dc, TA_CENTER);

		wstring storyText = L"학생들의 사랑을 받지 못해서 머리가 다 빠져버린 선생님!!";
		TextOut(_dc, centerPos.x, centerPos.y, storyText.c_str(), storyText.length());

		storyText = L"벽돌처럼 딱딱한 학생들의 마음을 녹여라!!";
		TextOut(_dc, centerPos.x, centerPos.y + 25, storyText.c_str(), storyText.length());

		SetTextAlign(_dc, TA_LEFT);
	}
}

//void Scene_Lobby::Update()
//{
//	Scene::Update();
//}
