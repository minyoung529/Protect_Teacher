#include "pch.h"
#include "GameMgr.h"

void GameMgr::ReloadScene()
{
	m_score = 0;

	m_blockCnt = 1;
	m_curGauge = 0;
	m_canUseSkill = false;
	m_canAttack = false;
	m_usingSkill = false;
}