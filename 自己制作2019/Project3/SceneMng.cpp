#include "SceneMng.h"
#include <DxLib.h>

#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 600


void SceneMng::Run()
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		ClsDrawScreen();
		ScreenFlip();
	}
}

SceneMng::SceneMng()
{
	Init();
}


SceneMng::~SceneMng()
{
}

bool SceneMng::Init()
{
	// ¼½ÃÑˆ—
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 65536FÓ°ÄŞ‚Éİ’è
	ChangeWindowMode(true);				// true:window@false:ÌÙ½¸Ø°İ
	SetWindowText("practice");
	if (DxLib_Init() == -1) return false;	// DX×²ÌŞ×Ø‰Šú‰»ˆ—
	SetDrawScreen(DX_SCREEN_BACK);		// ‚Ğ‚Æ‚Ü‚¸ÊŞ¯¸ÊŞ¯Ì§‚É•`‰æ
}
