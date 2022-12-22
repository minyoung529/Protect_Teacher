#include "pch.h"
#include "Scene_Lobby.h"
#include "Button.h"
#include "Core.h"
#include "Effect.h"
#include "HeartObject.h"
#include "WallBall.h"
#include "SoundMgr.h"

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

	// Buttons
	{
		Vec2 centerPos = Core::GetInst()->GetResolution();
		centerPos.x /= 2; centerPos.y /= 2;

		Object* button = new Button(centerPos, Vec2(1.f,1.f), ButtonType::Game);
		AddObject(button, GROUP_TYPE::UI);
		centerPos.y += 100;

		button = new Button(centerPos, Vec2(1.f, 1.f), ButtonType::Quit);
		AddObject(button, GROUP_TYPE::UI);
	}

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
			HeartObject* heart = new HeartObject(i % 3 );
			heart->SetPos(Vec2(j * hSpace + space, i * vSpace + space));
			AddObject(heart, GROUP_TYPE::DEFAULT);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		int randX = rand() % 200;
		int randY = rand() % 200;

		Vec2 dir = Vec2((randX - 100) / 100.f, (randY - 100) / 100.f);
		Object* obj = new WallBall(dir.Normalize());
		AddObject(obj, GROUP_TYPE::EFFECT);
	}
}

void Scene_Lobby::Exit()
{
	DeleteAll();
}

//void Scene_Lobby::Update()
//{
//	Scene::Update();
//}
