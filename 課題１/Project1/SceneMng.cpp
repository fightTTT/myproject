#include <DxLib.h>
#include "SceneMng.h"
#include "unit/Enemy.h"
#include "unit/Player.h"
#include "_DebugConOut.h"
#include "common/ImageMng.h"
#include "Scene/GameScene.h"
#include "_DebugDispOut.h"

std::unique_ptr<SceneMng, SceneMng::SceneMngDeleter> SceneMng::s_Instance(new SceneMng);

void SceneMng::Run(void)
{
	Init();
	
	ImageMng::GetInstance().GetID("�L����", "image/char.png", { 10,10 }, { 30,30 });

	_DebugConOut::GetInstance();

	_activeScene = std::make_unique<GameScene>();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_DbgStartDraw;
		drawList.clear();
		_activeScene = _activeScene->UpDate(std::move(_activeScene));
		AddDrawQue({ IMAGE_ID("�g")[0],0,0 });
		Draw();
	}

}

bool SceneMng::AddDrawQue(DrawQueT dQue)
{
	if (std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue) == -1)	// std::get<0>(dQue)�Ə������Ƃɂ����tuple��0�Ԗڂ̗v�f�����邱�Ƃ��ł���
	{
		return false;
	}
	drawList.emplace_back(dQue);
	return true;
}

bool SceneMng::Init(void)
{
	SetGraphMode(screenSize.x, screenSize.y, 16);		// 65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);				// true:window�@false:�ٽ�ذ�
	SetWindowText("�M�����K");
	if (DxLib_Init() == -1) return false;	// DXײ���؏���������
	TRASCE("DXLIB����������\n");
	SetDrawScreen(DX_SCREEN_BACK);		// �ЂƂ܂��ޯ��ޯ̧�ɕ`��

	SET_IMAGE_ID("�g", "image/frame.png");
	_DbgSetUp(200);

	return true;
}

void SceneMng::Draw(void)
{
	_DbgAddDraw;
	SetDrawScreen(DX_SCREEN_BACK);		// �ЂƂ܂��ޯ��ޯ̧�ɕ`��
	
	ClsDrawScreen();
	
	for (auto _dQue : drawList)
	{
		DrawGraph(std::get<static_cast<int>(DRAW_QUE::X)>(_dQue),
				  std::get<static_cast<int>(DRAW_QUE::Y)>(_dQue),
				  std::get<static_cast<int>(DRAW_QUE::IMAGE)>(_dQue), true);
	}
	
	ScreenFlip();
	
}

SceneMng::SceneMng() :screenSize{ 800,600 }, gameScreenSize{ 500,390 }, gameScreenPos{(800-500)/2,(600-390)/2}
{
	
}


SceneMng::~SceneMng()
{
}
