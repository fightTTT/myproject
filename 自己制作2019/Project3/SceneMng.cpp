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
	// ｼｽﾃﾑ処理
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 65536色ﾓｰﾄﾞに設定
	ChangeWindowMode(true);				// true:window　false:ﾌﾙｽｸﾘｰﾝ
	SetWindowText("practice");
	if (DxLib_Init() == -1) return false;	// DXﾗｲﾌﾞﾗﾘ初期化処理
	SetDrawScreen(DX_SCREEN_BACK);		// ひとまずﾊﾞｯｸﾊﾞｯﾌｧに描画
}
