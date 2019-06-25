#include <DxLib.h>
#include "SceneMng.h"
#include "unit/Enemy.h"
#include "unit/Player.h"
#include "_DebugConOut.h"
#include "common/ImageMng.h"
#include "Scene/GameScene.h"

std::unique_ptr<SceneMng, SceneMng::SceneMngDeleter> SceneMng::s_Instance(new SceneMng);

void SceneMng::Run(void)
{
	

	
	ImageMng::GetInstance().GetID("ƒLƒƒƒ‰", "image/char.png", { 10,10 }, { 30,30 });

	_DebugConOut::GetInstance();

	_activeScene = std::make_unique<GameScene>();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();
		_activeScene = _activeScene->UpDate(std::move(_activeScene));
		ScreenFlip();
	}

}

bool SceneMng::Init(void)
{
	SetGraphMode(800, 600, 16);		// 65536FÓ°ÄŞ‚Éİ’è
	ChangeWindowMode(true);				// true:window@false:ÌÙ½¸Ø°İ
	SetWindowText("ƒMƒƒƒ‰ƒK");
	if (DxLib_Init() == -1) return false;	// DX×²ÌŞ×Ø‰Šú‰»ˆ—
	TRASCE("DXLIB‰Šú‰»Š®—¹\n");
	SetDrawScreen(DX_SCREEN_BACK);		// ‚Ğ‚Æ‚Ü‚¸ÊŞ¯¸ÊŞ¯Ì§‚É•`‰æ

	return false;
}

SceneMng::SceneMng()
{
	Init();
}


SceneMng::~SceneMng()
{
}
