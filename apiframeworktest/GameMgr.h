#pragma once
class GameMgr
{
public:
	SINGLE(GameMgr)

private:
	int m_score = 0;
	int m_highScore = 0;

public:
	void AddScore(int score)
	{
		m_score += score;

		if (m_score > m_highScore)
		{
			m_highScore = m_score;
		}
	}

	int GetScore()		{ return m_score; }
	int GetHighScore()	{ return m_highScore; }
};

