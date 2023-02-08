#pragma once
#include "Object.h"
class Square :
    public Object
{
public:
     Square(Vec2 pos, Vec2 scale);
     virtual ~Square();

public:
     virtual void Update() override;
     virtual void Render(HDC _dc) override;

     CLONE(Square)
};