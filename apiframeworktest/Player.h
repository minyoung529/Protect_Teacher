#pragma once
#include "Object.h"

class Image;
class Player :
    public Object
{
private:
    Image* m_pImage;
    Image* arrow;
public:
    Player();
    //Player(const Player& _origin) 
    //    : Object(_origin)
    //    , m_pImage(_origin.m_pImage)
    //{}
    ~Player();
    void CreateBullet(int _bulletCount,POINT& a);
     int bulletCount = 3;
     POINT mouse;
     POINT screenPoint;
     float time;
     bool isTime;
private:

//    Player* Clone{ return new Player(*this); }
    CLONE(Player);
public:
    void Update()       override;
    void Render(HDC _dc) override;
};

