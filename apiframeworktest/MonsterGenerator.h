#pragma once
#include "Object.h"
#include "Monster.h"

#define MONSTER_W_COUNT		25
#define MONSTER_H_COUNT		15

#define SPAWN_DIST			3

#define V_SPACE				50
#define H_SPACE				50

class MonsterGenerator : public Object
{
public:
	MonsterGenerator();
	~MonsterGenerator();

private:
	Vec2 m_monsterScale;
	Vec2 m_w_idx;
	Vec2 m_h_idx;

	RECT m_rect;
	int m_width = 0;
	int m_height = 0;

	CLONE(MonsterGenerator)

	vector<MonsterData> m_monsterDatas;

public:
	virtual void	Update() override;
	virtual void	Render(HDC _dc) override;

public:
	void NextTurn();

private:
	void GenerateVerticalMonster();
	void GenerateHorizontalMonster();
	Monster* CreateMonster(Vec2 position, Vec2 scale, Direction dir);

private:
	Vec2 GetCenterVPos(int x, int y);
	Vec2 GetCenterHPos(int x, int y);
};