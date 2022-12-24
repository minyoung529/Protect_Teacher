#include "pch.h"
#include "GameMgr.h"
#include "SoundMgr.h"

void GameMgr::ReloadScene()
{
	m_score = 0;

	m_blockCnt = 1;
	m_curGauge = 0;
	m_monsterMinHp = 1;
	m_canUseSkill = false;
	m_canAttack = false;
	m_usingSkill = false;

	SoundMgr::GetInst()->LoadSound(L"SKILL", false, L"Sound\\Skill.mp3");
}

void GameMgr::AddCurGauge(int add)
{
	m_curGauge += add;

	if (m_curGauge >= m_maxGauge)
	{
		m_canUseSkill = true;
		m_curGauge = m_maxGauge;

		SoundMgr::GetInst()->Play(L"SKILL");
	}
	else
	{
		m_canUseSkill = false;
	}
}
