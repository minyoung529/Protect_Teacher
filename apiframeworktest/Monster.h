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

#define COLOR_THICKNESS	5

class Monster :
	public Object
{
public:
	Monster();
	Monster(const MonsterData& monsterData, BRUSH_TYPE brush, Vec2 size);
	~Monster();

private:
	MonsterData m_monsterData;
	int     m_iHp;
	Direction m_direction;
	BRUSH_TYPE m_color;
	bool haveItem = false;

public:
	virtual void    Update() override;
	virtual void	Render(HDC _dc);
	void Move();

	virtual void	EnterCollision(Collider* _pOther, RECT colRt) override;
	void SetDirection(Direction dir) { m_direction = dir; }
	void Hit(int damage);

	void SetIsItem() { haveItem = true; }
	CLONE(Monster);

private:
	void PlayParticle();
};

