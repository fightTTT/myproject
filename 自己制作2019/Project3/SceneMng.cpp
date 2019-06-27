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
	// ���я���
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);				// true:window�@false:�ٽ�ذ�
	SetWindowText("practice");
	if (DxLib_Init() == -1) return false;	// DXײ���؏���������
	SetDrawScreen(DX_SCREEN_BACK);		// �ЂƂ܂��ޯ��ޯ̧�ɕ`��
}
