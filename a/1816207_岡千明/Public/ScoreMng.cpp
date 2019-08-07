#include <memory>
#include "ScoreMng.h"
#include <Public/FontMng.h>
#include <Scene/SceneMng.h>

// ≤›Ω¿›ΩÇµ±ƒﬁ⁄ΩÇìnÇ∑§√ﬁÿ∞ƒêÊÇ‡ìoò^
std::unique_ptr<ScoreMng, ScoreMng::ScoreMngDeleter> ScoreMng::s_Instance(new ScoreMng);

const void ScoreMng::AddScore(int score)
{
	_score += score;
}

void ScoreMng::ScoreReset(void)
{
	_score = 0;
}

void ScoreMng::Draw(void)
{
	DrawStringToHandle(80, 0, "SCORE", 0xffffff, lpFontMng.SetFont("Sim30"));
	int drawLengh;
	drawLengh = GetDrawFormatStringWidthToHandle(lpFontMng.SetFont("Sim30"), "%d", _score);
	
	DrawFormatStringToHandle(230 - drawLengh,0, 0xffffff, lpFontMng.SetFont("Sim30"), "%d", _score);
}

ScoreMng::ScoreMng()
{
	Init();
}

ScoreMng::~ScoreMng()
{
}

bool ScoreMng::Init(void)
{
	_score = 0;

	return true;
}
