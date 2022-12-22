#pragma once

class Player;

class GameMgr
{
public:
	SINGLE(GameMgr)

private:
	int m_score = 0;
	int m_highScore = 0;

	int m_blockCnt = 1;

	int m_maxGauge = 20;
	int m_curGauge = 0;

	bool m_canUseSkill;
	bool m_usingSkill;

	bool m_canAttack = false;

	Vec2 m_heartPos;

	Player* m_player;

public:
	void ReloadScene();
	void AddScore(int score)
	{
		m_score += score;

		if (m_score > m_highScore)
		{
			m_highScore = m_score;
		}
	}
	void AddBlockCnt(int blockcnt) { m_blockCnt += blockcnt; }

	int GetScore() { return m_score; }
	int GetHighScore() { return m_highScore; }
	int GetBlockCount() { return m_blockCnt; }

	int GetMaxGauge() { return m_maxGauge; }
	int GetCurGauge() { return m_curGauge; }
	void AddCurGauge(int add)
	{
		m_curGauge += add;

		if (m_curGauge >= m_maxGauge)
		{
			m_canUseSkill = true;
			m_curGauge = m_maxGauge;
		}
		else
		{
			m_canUseSkill = false;
		}
	}
	bool GetCanUseSkill() { return m_canUseSkill; }
	bool GetUsingSkill() { return m_usingSkill; }
	void SetUsingSkill(bool skill) { m_usingSkill = skill; }

	void SetHeartPos(Vec2 pos) { m_heartPos = pos; }
	Vec2 GetHeartPos() { return m_heartPos; }

	bool GetCanAttack() { return m_canAttack; }
	void SetCanAttack(bool canAttack) { m_canAttack = canAttack; }

	Player* GetPlayer() { return m_player; }
	void SetPlayer(Player* p) { m_player = p; }
};