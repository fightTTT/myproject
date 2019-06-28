#include "SceneMng.h"
#include "GameScene.h"
#include "DxLib.h"


void SceneMng::Run(void)
{
	activeScene = std::make_unique<GameScene>();

	// ---------- �ް�ٰ��
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
	// ���я���
	SetGraphMode(800, 600, 16);		// 65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);				// true:window�@false:�ٽ�ذ�
	SetWindowText("BLUE SKY");
	if (DxLib_Init() == -1) return false;	// DXײ���؏���������
	SetDrawScreen(DX_SCREEN_BACK);		// �ЂƂ܂��ޯ��ޯ̧�ɕ`��

	return true;
}
