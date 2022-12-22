#include "pch.h"
#include "Scene_End.h"
#include "SoundMgr.h"
#include "Core.h"
#include "Button.h"
#include "HeartObject.h"
#include "WallBall.h"
#include "TextBar.h"

Scene_End::Scene_End()
{
}

Scene_End::~Scene_End()
{
}

void Scene_End::Enter()
{
	SoundMgr::GetInst()->LoadSound(L"LOBBY_BGM", true, L"Sound\\LobbyBGM.mp3");
	SoundMgr::GetInst()->Play(L"LOBBY_BGM");
	
	Vec2 centerPos = Core::GetInst()->GetResolution();
	centerPos.x /= 2;
	centerPos.y /= 2;

	// Buttons
	{
		Vec2 buttonScale(0.7f, 0.7f);
		Vec2 buttonPos = centerPos;

		buttonPos.y += 200;
		buttonPos.x -= 100;
		Object* button = new Button(buttonPos, buttonScale, ButtonType::Game, L"Replay");
		AddObject(button, GROUP_TYPE::UI);

		buttonPos.x += 200;
		button = new Button(buttonPos, buttonScale, ButtonType::Quit);
		AddObject(button, GROUP_TYPE::UI);
	}

	// Text
	{
		Object* pObj = new TextBar(TextType::HighScore, 90, 30);
		pObj->SetPos(Vec2(centerPos.x-50, centerPos.y-200));
		AddObject(pObj, GROUP_TYPE::UI);

		pObj = new TextBar(TextType::Score, 90, 30);
		pObj->SetPos(Vec2(centerPos.x - 50, centerPos.y - 100));
		AddObject(pObj, GROUP_TYPE::UI);
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
			HeartObject* heart = new HeartObject(i % 3);
			heart->SetPos(Vec2(j * hSpace + space, i * vSpace + space));
			AddObject(heart, GROUP_TYPE::DEFAULT);
		}
	}
}

void Scene_End::Exit()
{
	DeleteAll();
}
