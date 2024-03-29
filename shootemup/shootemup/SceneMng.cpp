#include "SceneMng.h"
#include "GameScene.h"
#include "DxLib.h"


void SceneMng::Run(void)
{
	activeScene = std::make_unique<GameScene>();

	// ---------- ｹﾞｰﾑﾙｰﾌﾟ
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
	// ｼｽﾃﾑ処理
	SetGraphMode(800, 600, 16);		// 65536色ﾓｰﾄﾞに設定
	ChangeWindowMode(true);				// true:window　false:ﾌﾙｽｸﾘｰﾝ
	SetWindowText("BLUE SKY");
	if (DxLib_Init() == -1) return false;	// DXﾗｲﾌﾞﾗﾘ初期化処理
	SetDrawScreen(DX_SCREEN_BACK);		// ひとまずﾊﾞｯｸﾊﾞｯﾌｧに描画

	return true;
}
