#pragma once
#include "Object.h"
#include "Monster.h"

#define MONSTER_W_COUNT		30
#define MONSTER_H_COUNT		30

#define SPAWN_DIST			6

class MonsterGenerator : public Object
{
public:
	MonsterGenerator();
	~MonsterGenerator();

private:
	Vec2 m_monsterScale;
	Vec2 m_w_idx;
	Vec2 m_h_idx;

	CLONE(MonsterGenerator)

	vector<MonsterData> m_monsterDatas;

public:
	virtual void	Update() override;

private:
	void GenerateVerticalMonster();
	void GenerateHorizontalMonster();
	Monster* CreateMonster(Vec2 position, Vec2 scale, Direction dir);

private:
	Vec2 GetCenterVPos(int x, int y);
	Vec2 GetCenterHPos(int x, int y);
};