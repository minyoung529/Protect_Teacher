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
public:
    Player();
    ~Player();

private:
    void CreateBullet(POINT& a);
private:
    Vec2 mousePosition;
    float delay;
    float totalTime;
    float speed;
    int bulletCount = 1;
    int originalBulletCnt = 1;
    float time;
    bool isTime;
    float overTimer = 0.f;
    bool isOver = false;

    float animTimer = 0.f;
    bool isAttacking = false;

public:
    void Update()       override;
    void Render(HDC _dc) override;

    void AddBulletCnt(int add) { originalBulletCnt += add; }

private:
    void DrawDottedLine(HDC _dc);
    virtual void	EnterCollision(Collider* _pOther, RECT colRt) override;
    CLONE(Player);
};

