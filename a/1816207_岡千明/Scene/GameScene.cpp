#include <Dxlib.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <Scene/SceneMng.h>
#include "GameScene.h"
#include <Unit/Player.h>
#include <Unit/Enemy.h>
#include <Unit/Bullet.h>
#include <Public/FontMng.h>
#include <Public/ScoreMng.h>
#include <Public/SoundMng.h>

#define STAGE_STATE_TIME (-4 * 60)	// �ð�ނ��n�܂��Ĵ�а���ݽ�ݽ����܂ł̎���

GameScene::GameScene()
{
	Init();
}

GameScene::~GameScene()
{
}

shared_Base GameScene::UpDate(shared_Base own)
{
	keyFlagSpOld = keyFlagSp;
	keyFlagSp = (CheckHitKey(KEY_INPUT_SPACE));

	// ��ԍX�V
	for (auto _bullet : _bulletList)
	{
		if (_bullet->actFlg() != false)
		{
			// �e
			_bullet->UpDate();
		}
	}
	for (auto _e_Bullet : _e_BulletList)
	{
		if (_e_Bullet->actFlg() != false)
		{
			// �e
			_e_Bullet->UpDate();
		}
	}
	for (auto obj : _objList)
	{
		// ��ڲ԰�ƴ�а
		obj->UpDate();
	}

	// ��а�ƒe�̓����蔻��
	for (auto itr = std::remove_if(_objList.begin(), _objList.end(),
		[](shared_Obj& obj) {return obj->GetUnitType() == UNIT::ENEMY; }); itr != _objList.end(); itr++)
	{
		if ((*itr)->isAlive() != false && (*itr)->isDeath() != true)
		{
			(*itr)->CheckHit(_bulletList);
		}
	}
	// ��ڲ԰�ƒe�̓����蔻��
	for (auto itr:_objList)
	{
		if (itr->GetUnitType() == UNIT::PLAYER)
		{
			if ((itr)->isAlive() != false && (itr)->isDeath() != true)
			{
				(itr)->CheckHit(_e_BulletList);
			}
		}
	}

	// Obj��isDeath��false�̎�(���S��)�ɗv�f���폜����(�����ɍ폜�������v�f���܂Ƃ߂Ĉ��ŏ���)
	_objList.erase(std::remove_if(_objList.begin(),
		_objList.end(),
		[](shared_Obj& obj) {return (*obj).isDeath(); }), _objList.end());

	// �ð�޸ر�̏���
	// �Ō�̓G�̲ݽ�ݽ�̎��Ԃ��ްѶ��Ă��傫���Ƃ�
	if (_gameCnt >= _enemyInsCnt.back())
	{
		// ��а�̲�ڰ���擾(remove_if�Ŵ�а������)
		auto itr = std::remove_if(_objList.begin(), _objList.end(),
			[](shared_Obj& obj) {return obj->GetUnitType() == UNIT::ENEMY; });

		// ��ڰ����end�ł���ιްѸر
		if (itr == _objList.end())
		{
			// ���̽ð�ނ�
			_stageNum++;
			if (_stageNum>=3)
			{
				if (!_clearFlag)
				{
					_clearFlag = true;
					_staretFlag = false;
					_gameCnt = 0;

					// SE
					lpSoundMng.SetSound("�ر");
				}
			}
			else
			{
				// ������
				_cnt = 0;
				_gameCnt = STAGE_STATE_TIME;
				
				// ��а���ް��ǂݍ���
				EnemyInit();

				// ��а�̲ݽ�ݽ
				EnemyInstance();
			}
		}
	}
	if (_staretFlag)
	{
		// ��ڲ԰�̲�ڰ���擾
		auto itr = std::find_if(_objList.begin(), _objList.end(),
			[](shared_Obj& obj) {return obj->GetUnitType() == UNIT::PLAYER; });

		// ��ڰ����end�ł���ιްѵ��ް
		if (itr == _objList.end())
		{
			_gameOverFlag = true;
		}
	}

	// �`��
 	Draw();

	if (_staretFlag)
	{
		// �G�̲ݽ�ݽ
		EnemyInstance();

		if (_gameCnt == STAGE_STATE_TIME + 60)
		{
			lpSoundMng.SetSound("�ð��");
		}
		// �ްѓඳ��
		_gameCnt++;
	}
	else
	{
		// ��߰����Ŏn�߂�
		if (keyFlagSp && !keyFlagSpOld)
		{
			// �ر��̏���
			if (_clearFlag)
			{
				// ������
				_stageNum = 1;
				_cnt = 0;
				for (auto itr : _objList)
				{
					if (itr->GetUnitType() == UNIT::PLAYER)
					{
						itr->hp(3);
					}
				}
				// ��а���ް��ǂݍ���
				EnemyInit();
				// ����̏�����
				lpScoreMng.ScoreReset();

				_clearFlag = false;
			}

			// SE
			lpSoundMng.SetSound("����");
			_staretFlag = true;
			_gameCnt = STAGE_STATE_TIME;
		}
		_gameCnt--;
	}
	// �ްѵ��ް��
	if (_gameOverFlag)
	{
		_gameOverCnt--;
	}
	if (_gameOverCnt <= 0)
	{	
		// �V������݂�ǂݒ���
		return std::make_unique<GameScene>();
	}
	else
	{
		// ���L����n��
		return std::move(own);
	}
}

void GameScene::Draw(void)
{
	int ghBefor;

	// ���݂̉�ʂ�����
	ghBefor = GetDrawScreen();

	// ���݂̽�ذ݂�ްѼ�ݗp��ذ݂ɕύX
	SetDrawScreen(_ghGameScreen);

	// �w�i�F
	SetBackgroundColor(0, 0, 0);

	ClsDrawScreen();	// ��ʏ���

	// �`��
	for (auto _bullet : _bulletList)
	{
		if (_bullet->actFlg() != false)
		{
			// �e
			_bullet->Obj::Draw();
		}
	}

	// �`��
	for (auto _bullet : _e_BulletList)
	{
		if (_bullet->actFlg() != false)
		{
			// �e
			_bullet->Obj::Draw();
		}
	}
	for (auto obj : _objList)
	{
		// ������ڲ԰�ƴ�а

		obj->Obj::Draw();
	}

	// �J�n�p����
	if (!_staretFlag)
	{
		if (_gameCnt / 60 % 2 == 0)
		{
			// �����̒������擾
			int drawLengh;
			drawLengh = GetDrawStringWidthToHandle("- PUSH SPACE KEY -", strlen("- PUSH SPACE KEY -"), lpFontMng.SetFont("Sim40"));

			// �����̕\��
			DrawStringToHandle((lpSceneMng.gameScreenSize.x - drawLengh) / 2, 250, "- PUSH SPACE KEY -", 0xffffff, lpFontMng.SetFont("Sim40"));
		}
	}
	// �ð�ޗp����
	else
	{
		if (_gameCnt < -60 && _gameCnt > STAGE_STATE_TIME + 60)
		{
			int drawLengh;
			drawLengh = GetDrawFormatStringWidthToHandle(lpFontMng.SetFont("Sim40"), "STAGE %d", _stageNum);

			DrawFormatStringToHandle((lpSceneMng.gameScreenSize.x - drawLengh) / 2, 180, 0xffffff, lpFontMng.SetFont("Sim40"), "STAGE %d", _stageNum);
		}
	}
	// �ر���̕���
	if (_clearFlag)
	{
		// �����̒������擾
		int drawLengh;
		drawLengh = GetDrawStringWidthToHandle("CONGRATULATION!!", strlen("CONGRATULATION!!"), lpFontMng.SetFont("Sim40"));

		// �����̕\��
		DrawStringToHandle((lpSceneMng.gameScreenSize.x - drawLengh) / 2, 180, "CONGRATULATION!!", 0xffffff, lpFontMng.SetFont("Sim40"));
	}
	// �ްѵ��ް��
	else if (_gameOverFlag)
	{
		// �����̒������擾
		int drawLengh;
		drawLengh = GetDrawStringWidthToHandle("-GAME OVER-", strlen("-GAME OVER-"), lpFontMng.SetFont("Sim40"));

		// �����̕\��
		DrawStringToHandle((lpSceneMng.gameScreenSize.x - drawLengh) / 2, 180, "-GAME OVER-", 0xffffff, lpFontMng.SetFont("Sim40"));
	}

	// ��ڲ԰�̎c�@�\��
	for (auto itr : _objList)
	{
		if (itr->GetUnitType() == UNIT::PLAYER)
		{
			for (int k = itr->hp() - 1; k > 0; k--)
			{
				DrawRotaGraph(430 - (20 * k), 18, 0.4, 0, _playerLife, true, false);
			}
		}
	}
	DrawStringToHandle(300, 0, "LIFE", 0xffffff, lpFontMng.SetFont("Sim30"));

	// ����̕\��
	lpScoreMng.Draw();

	// �摜�̷���ǉ�
	lpSceneMng.addDrawQue({ _ghGameScreen,lpSceneMng.gameScreenPos.x,lpSceneMng.gameScreenPos.y });

	// ���̽�ذ݂ɖ߂�
	SetDrawScreen(ghBefor);
}

SCN_ID GameScene::GetScnID(void)
{
	return SCN_ID::GAME;
}

bool GameScene::Init(void)
{
	// �ްѼ�ݗp��ذ݂̍쐬
	_ghGameScreen = MakeScreen(lpSceneMng.gameScreenSize.x, lpSceneMng.gameScreenSize.y, true);

	// �����̎���쐬
	srand(time(NULL));

	// �ݽ�ݽ(ؽĂɗv�f�ǉ�)
	// ��ڲ԰(��ʉ������ɔz�u)
	_objList.emplace_back(new Player(
		Vector2(lpSceneMng.gameScreenSize.x / 2, lpSceneMng.gameScreenSize.y - 16), _bulletList));

	// �c�@�摜
	_playerLife = LoadGraph("image/player.png");

	// ��а�ް��̓ǂݍ���
	EnemyData();
	EnemyInit();

	// ����̏�����
	lpScoreMng.ScoreReset();

	// ̫�Ă̓o�^
	lpFontMng.FontInit("font/Simple.ttf", "Simple", "Sim30", 30, -1, false, false);
	lpFontMng.FontInit("font/Simple.ttf", "Simple", "Sim40", 40, -1, false, false);

	// SE�̓o�^
	lpSoundMng.SoundInit("sound/Start.mp3", "����");
	lpSoundMng.SoundInit("sound/StageSE.mp3", "�ð��");
	lpSoundMng.SoundInit("sound/Clear.mp3", "�ر");

	return true;
}

bool GameScene::EnemyData(void)
{
	// ��а�o���p���Wð��ٍ쐬
	_enemyPos.reserve(6);
	_enemyPos =
	{	// ����,������,����,�E��,�E��,�E��
		Vector2Dbl(-16.0,15.0),
		Vector2Dbl(-16.0,static_cast<double>(lpSceneMng.gameScreenSize.y) / 2.0),
		Vector2Dbl(-16.0,static_cast<double>(lpSceneMng.gameScreenSize.y) - 15.0 - 40.0),
		Vector2Dbl(static_cast<double>(lpSceneMng.gameScreenSize.x) + 16.0,+15.0),
		Vector2Dbl(static_cast<double>(lpSceneMng.gameScreenSize.x) + 16.0,static_cast<double>(lpSceneMng.gameScreenSize.y) / 2.0),
		Vector2Dbl(static_cast<double>(lpSceneMng.gameScreenSize.x) + 16.0,static_cast<double>(lpSceneMng.gameScreenSize.y) - 15.0 - 40.0)
	};

	// ��а�̍ŏI�ڕW�n�_
	for (int k = 0; k < 4; k++)
	{
		// �{�X�p
		_aimPos.emplace_back(Vector2(190 + (k * 40), 40));
	}
	for (int k = 0; k < 16; k++)
	{
		// ��q�p
		_aimPos.emplace_back(Vector2(110 + 40 * (k % 8), 80 + 40 * (k / 8 % 2)));
	}
	for (int k = 0; k < 20; k++)
	{
		// �U�R�p
		_aimPos.emplace_back(Vector2(70 + 40 * (k % 10), 160 + 40 * (k / 10 % 2)));
	}

	return true;
}

bool GameScene::EnemyInit(void)
{
	Vector2Dbl tmp;
	MOVE_TYPE move;

	// �v�f�̍폜
	_enemyInsCnt.clear();
	_enemyInsCnt.resize(0);
	_enemyStartPos.clear();
	_enemyStartPos.resize(0);
	_enemyType.clear();
	_enemyType.resize(0);
	_enemySize.clear();
	_enemySize.resize(0);
	_enemyAim.clear();
	_enemyAim.resize(0);

	enum ENEMY_DATA {
		MAX,
		INS_TIME,// �G��ݽ�ݽ���鎞��
		F_POS_X, // ����posX
		F_POS_Y, // ����posY
	};
	FILE *fp = nullptr;
	char buf[256];
	int c;
	int col = 1;
	int row = 0;

	// buf�̂��ׂĂ̗v�f��0������(������)
	memset(buf, 0, sizeof(buf));

	if (_stageNum == 1)
	{
		// ̧�يJ��
		fopen_s(&fp, "Excel/Stage1.csv", "rb");
	}
	else if (_stageNum == 2)
	{
		// ̧�يJ��
		fopen_s(&fp, "Excel/Stage2.csv", "rb");
	}
	// ̧�ق��Ȃ�������false��Ԃ�
	if (&fp == nullptr)
	{
		return false;
	}
	else
	{
		//�w�b�_�ǂݔ�΂�
		while (fgetc(fp) != '\n');

		while (1)
		{
			while (1)
			{
				// �����ǂݎ��
				c = fgetc(fp);

				// �����Ȃ�ٰ�߂𔲂���B
				if (c == EOF)
				{
					goto out;
				}

				// ��ς����s�łȂ���΁A�����Ƃ��ĂȂ���
				if (c != ',' && c != '\n')
				{
					strcat_s(buf, sizeof(buf), (const char*)&c);
				}
				// ��ς����s�Ȃ�ٰ�ߔ�����B

				else
				{
					break;
				}
			}
			// �����ɗ����Ƃ������Ƃ́A1�Z�����̕����񂪏o���オ�����Ƃ�������
			// atoi�֐�(int�^�ŕԂ�)�Œl���擾���Ă���
			switch (col)
			{
			case INS_TIME:
				_enemyInsCnt.emplace_back(atoi(buf));
				break;
				//1��ڂ͓G��ނ�\���Batoi�֐��Ő��l�Ƃ��đ���B
			case F_POS_X:
				_enemyStartPos.emplace_back(_enemyPos[atoi(buf)]);
				break;
			case 3:		// ��а�̎��
				_enemyType.emplace_back(static_cast<ENEMY_TYPE> (atoi(buf)));
				break;
			case 4:		// ����x
				tmp.x = static_cast<int>(atoi(buf));
				break;
			case 5:		// ����y
				tmp.y = static_cast<int>(atoi(buf));
				// �v�f�ǉ�
				_enemySize.emplace_back(Vector2(tmp.x, tmp.y));
				break;
			case 6:		// �ړ����@1�̖ڕW�n�_x
				tmp.x = atoi(buf);
			case 7:		// �ړ����@2�ڕW�n�_y
				tmp.y = atoi(buf);
				break;
			case 8:		// �ړ����@1
				move = static_cast<MOVE_TYPE>(atoi(buf));
				// �v�f�ǉ�
				_enemyAim.emplace_back(Vector2Dbl(tmp.x, tmp.y), move);
				break;
			case 9:		// �ړ����@2�̖ڕW�n�_x
				tmp.x = atoi(buf);
				break;
			case 10:	// �ړ����@2�̖ڕW�n�_y
				tmp.y = atoi(buf);
				break;
			case 11:	// �ړ����@2
				move = static_cast<MOVE_TYPE>(atoi(buf));
				// �v�f�ǉ�
				_enemyAim.emplace_back(Vector2Dbl(tmp.x, tmp.y), move);
				break;
			case 12:	// �ړ����@3�̖ڕW�n�_y
				tmp.x = _aimPos[atoi(buf)].x;
				tmp.y = _aimPos[atoi(buf)].y;
				break;
			case 13:	// �ړ����@3
				move = static_cast<MOVE_TYPE>(atoi(buf));
				// �v�f�ǉ�
				_enemyAim.emplace_back(Vector2Dbl(tmp.x, tmp.y), move);
				break;
			default:
				break;
			}
			//�o�b�t�@��������
			memset(buf, 0, sizeof(buf));

			//�񐔂𑫂�
			++col;

			//�����ǂݍ��񂾕��������s��������񐔂����������čs���𑝂₷
			if (c == '\n')
			{
				col = 1;
				++row;
			}
		}
	}
out:

	// ̧�ق����
	fclose(fp);

	return true;
}

void GameScene::EnemyInstance(void)
{
	if (_cnt != _enemyInsCnt.size())
	{
		if (_enemyInsCnt[_cnt] <= _gameCnt)
		{
			_objList.emplace_back(new Enemy({
				_enemyStartPos[_cnt],
				_enemyType[_cnt],
				_enemySize[_cnt],
				{_enemyAim[_cnt * 3],_enemyAim[1 + (_cnt * 3)],_enemyAim[2 + (_cnt * 3)]} ,
				_e_BulletList }));
			_cnt++;
		}
	}
}