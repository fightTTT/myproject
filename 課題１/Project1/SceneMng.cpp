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
	

	
	ImageMng::GetInstance().GetID("�L����", "image/char.png", { 10,10 }, { 30,30 });

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
	SetGraphMode(800, 600, 16);		// 65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);				// true:window�@false:�ٽ�ذ�
	SetWindowText("�M�����K");
	if (DxLib_Init() == -1) return false;	// DXײ���؏���������
	TRASCE("DXLIB����������\n");
	SetDrawScreen(DX_SCREEN_BACK);		// �ЂƂ܂��ޯ��ޯ̧�ɕ`��

	return false;
}

SceneMng::SceneMng()
{
	Init();
}


SceneMng::~SceneMng()
{
}
