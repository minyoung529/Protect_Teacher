#include "pch.h"
#include "Scene_Lobby.h"
#include "Button.h"
#include "Core.h"
#include "Effect.h"
#include "HeartObject.h"
#include "WallBall.h"

Scene_Lobby::Scene_Lobby()
{
}

Scene_Lobby::~Scene_Lobby()
{
}

void Scene_Lobby::Enter()
{
	// Buttons
	{
		Vec2 buttonScale(230, 80);
		Vec2 centerPos = Core::GetInst()->GetResolution();
		centerPos.x /= 2; centerPos.y /= 2;

		Object* button = new Button(centerPos, buttonScale, ButtonType::Game);
		AddObject(button, GROUP_TYPE::UI);
		centerPos.y += 100;

		button = new Button(centerPos, buttonScale, ButtonType::Quit);
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
			HeartObject* heart = new HeartObject((i) % 3 );
			heart->SetPos(Vec2(j * hSpace + space, i * vSpace + space));
			AddObject(heart, GROUP_TYPE::DEFAULT);
		}
	}

	Object* obj = new WallBall();
	AddObject(obj, GROUP_TYPE::DEFAULT);
}

void Scene_Lobby::Exit()
{
}

//void Scene_Lobby::Update()
//{
//	Scene::Update();
//}
