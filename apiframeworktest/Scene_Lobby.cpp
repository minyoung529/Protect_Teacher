#include "pch.h"
#include "Scene_Lobby.h"
#include "Button.h"
#include "Core.h"

Scene_Lobby::Scene_Lobby()
{
}

Scene_Lobby::~Scene_Lobby()
{
}

void Scene_Lobby::Enter()
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

void Scene_Lobby::Exit()
{
}

//void Scene_Lobby::Update()
//{
//	Scene::Update();
//}
