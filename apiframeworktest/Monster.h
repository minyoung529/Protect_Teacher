#pragma once
#include "Object.h"
#include "Image.h"

enum class Direction
{
    Up, Down, Left, Right, Length
};

struct MonsterData
{
    wstring m_name;
    int m_maxHp;
    Image* m_image;
};

class Monster :
    public Object
{
public:
    Monster();
    Monster(const MonsterData& monsterData);
    ~Monster();

private:
    MonsterData m_monsterData;
    int     m_iHp;
    Direction m_direction;

public:
    virtual void Update() override;
    virtual void	EnterCollision(Collider* _pOther);
    void SetDirection(Direction dir) { m_direction = dir; }
//    Monster* Clone() { return new Monster(*this); }
    CLONE(Monster);
};

