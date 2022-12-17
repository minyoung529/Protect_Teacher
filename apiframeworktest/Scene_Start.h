#pragma once
#include "Scene.h"
class Scene_Start :
    public Scene
{
public:
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Update() override;
    virtual void Render(HDC _dc) override;

private:
    void NextTurn();

public:
    Scene_Start();
    virtual ~Scene_Start();
};

