#pragma once
#include "Scene.h"
class Scene_End : public Scene
{
public:
	Scene_End();
	virtual ~Scene_End();

public:
	virtual void Enter() override;
	virtual void Exit() override;
};

