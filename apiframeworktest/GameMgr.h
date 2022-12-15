#pragma once
class GameMgr
{
public:
	SINGLE(GameMgr)

private:
	int m_score = 0;
	int m_highScore = 0;

	int m_blockCnt = 2;

	int m_maxGauge = 100;
	int m_curGauge = 0;

	bool m_canUseSkill;

public:
	void AddScore(int score)
	{
		m_score += score;

		if (m_score > m_highScore)
		{
			m_highScore = m_score;
		}
	}
	void AddBlockCnt(int blockcnt) { m_blockCnt += blockcnt; }

	int GetScore()		{ return m_score; }
	int GetHighScore()	{ return m_highScore; }
	int GetBlockCount() { return m_blockCnt; }

	int GetMaxGauge()	{ return m_maxGauge; }
	int GetCurGauge()	{ return m_curGauge; }
	void AddCurGauge(int add)
	{
		m_curGauge += add;

		if (m_curGauge > m_maxGauge)
		{
			m_curGauge = m_maxGauge;
		}
	}
	bool GetCanUseSkill() { return m_canUseSkill; }
};

