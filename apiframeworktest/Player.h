#pragma once
#include "Object.h"
#include "Resource.h"
#include "Bullet.h"
#include <math.h>

#define DOT_SCALE 3

class Image;
class Player :
    public Object
{
private:
public:
    POINT dot[3];
    XFORM xForm;
    Image* arrow;
    Bullet* pBullet;

    Vec2 mousePosition;
    Vec2 pos;
    Player();
    //Player(const Player& _origin) 
    //    : Object(_origin)
    //    , m_pImage(_origin.m_pImage)
    //{}
    ~Player();
    float delay;
    int width;
    int height;
    float angle;
    float totalTime;
    float speed;
    void CreateBullet(POINT& a);
    int bulletCount = 1;
    int originalBulletCnt = 1;
    POINT mouse;
    int i;
    POINT screenPoint;
    float time;
    bool isTime;

    float overTimer = 0.f;

    bool isOver = false;
private:

    virtual void	EnterCollision(Collider* _pOther, RECT colRt) override;

    //    Player* Clone{ return new Player(*this); }
    CLONE(Player);

public:
    void Rotate(float _angle);
    void Update()       override;
    void Render(HDC _dc) override;

private:
    void DrawDottedLine(HDC _dc);
};

