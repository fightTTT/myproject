#include "SceneMng.h"
#include "GameScene.h"
#include "DxLib.h"


void SceneMng::Run(void)
{
	activeScene = std::make_unique<GameScene>();

	// ---------- ¹Ş°ÑÙ°Ìß
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		ClsDrawScreen();

		activeScene = activeScene->UpDate(std::move(activeScene));

		ScreenFlip();
	}
}

SceneMng::SceneMng()
{
}


SceneMng::~SceneMng()
{
}

bool SceneMng::SysInit(void)
{
	// ¼½ÃÑˆ—
	SetGraphMode(800, 600, 16);		// 65536FÓ°ÄŞ‚Éİ’è
	ChangeWindowMode(true);				// true:window@false:ÌÙ½¸Ø°İ
	SetWindowText("BLUE SKY");
	if (DxLib_Init() == -1) return false;	// DX×²ÌŞ×Ø‰Šú‰»ˆ—
	SetDrawScreen(DX_SCREEN_BACK);		// ‚Ğ‚Æ‚Ü‚¸ÊŞ¯¸ÊŞ¯Ì§‚É•`‰æ

	return true;
}
