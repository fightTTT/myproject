#include <DxLib.h>
#include <Scene/SceneMng.h>
#include <Scene/GameScene.h>
#include <Public/ImageMng.h>
#include <_Debug/_DebugConOut.h>
#include <_Debug/_DebugDispOut.h>

// �ݽ�ݽ�����ڽ��n�����ذĐ���o�^
std::unique_ptr<SceneMng, SceneMng::SceneMngDeleter> SceneMng::s_Instance(new SceneMng);

SceneMng::SceneMng() :screenSize{ 800,600 }, gameScreenSize{ 500, 390 }, gameScreenPos{ (screenSize.x - gameScreenSize.x) / 2, (screenSize.y - gameScreenSize.y) / 2 }
{
}

SceneMng::~SceneMng()
{
}

bool SceneMng::SysInit(void)
{
	// ���я���
	SetGraphMode(screenSize.x, screenSize.y, 16);		// 65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);								// true:window�@false:�ٽ�ذ�

	SetWindowText("GALAGA");							// ����޳����
	if (DxLib_Init() == -1) return false;				// DXײ���؏���������	

	// ���ޯ��p(�o�͂�cin�cout��OK)
	TRASE("DXLIB����������\n");

	// �摜�o�^
	SET_IMAGE_ID("�g", "image/frame.png");

	// ���ޯ��p�̽�ذݍ쐬(���l200)
	_DebugSetup(200);

	return true;
}

void SceneMng::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);						// �ЂƂ܂��ޯ��ޯ̧�ɕ`��

	ClsDrawScreen();	// ��ʏ���

	for (auto _dque : _drawList)
	{
		// �摜�̕`��
		DrawGraph(
			std::get<static_cast<int>(DRAW_QUE::X)>(_dque),	// X���W
			std::get<static_cast<int>(DRAW_QUE::Y)>(_dque),	// Y���W
			std::get<static_cast<int>(DRAW_QUE::IMAGE)>(_dque),	// ���̨�������
			true);
	}

	ScreenFlip();		// �ް�ٰ�߂̍Ō�ɕK���K�v
}

void SceneMng::Run(void)
{
	// ���т̏�����
	SysInit();

	// �Ұ���Ȱ�ެ��̲ݽ�ݽ
	ImageMng::GetInstance().GetID("���", "image/char.png", Vector2(30, 32), Vector2(10, 10));
	ImageMng::GetInstance().GetID("PL����", "image/pl_blast.png", Vector2(64, 64), Vector2(4, 1));
	ImageMng::GetInstance().GetID("�G����", "image/en_blast.png", Vector2(64, 64), Vector2(5, 1));
	ImageMng::GetInstance().GetID("�e", "image/shot.png", Vector2(3, 4), Vector2(2, 1));

	// �ư��߲����̍쐬���̫�ĺݽ�׸��ŌĂԂ̂�()��t����
	_activeScene = std::make_unique<GameScene>();

	// ---------- �ް�ٰ��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ���ޯ��p�̕`��
		_DebugStartDraw

			// �摜�̷���폜
			_drawList.clear();

		// move�Ŏ������g��unique�߲����̏��L����n��
		_activeScene = _activeScene->UpDate(std::move(_activeScene));

		// �摜�̷���ǉ�
		addDrawQue({ IMAGE_ID("�g")[0],0,0 });

		// ���ޯ��̵ݵ̐؂�ւ�(���݂�Q,W��)
		_DebugAddDraw

			// �`��
			Draw();

		// ���Ă�i�߂�
		_cnt++;
	}

}

bool SceneMng::addDrawQue(DrawQueT dQue)
{
	// ����ق��擾�ł��Ȃ����false��Ԃ�
	if (std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue) == -1)
	{
		return false;
	}

	// �v�f�ǉ�
	_drawList.emplace_back(dQue);

	return true;
}

const int SceneMng::cnt(void)
{
	return _cnt;
}
