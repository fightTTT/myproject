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

#define STAGE_STATE_TIME (-4 * 60)	// ｽﾃｰｼﾞが始まってｴﾈﾐｰがｲﾝｽﾀﾝｽするまでの時間

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

	// 状態更新
	for (auto _bullet : _bulletList)
	{
		if (_bullet->actFlg() != false)
		{
			// 弾
			_bullet->UpDate();
		}
	}
	for (auto _e_Bullet : _e_BulletList)
	{
		if (_e_Bullet->actFlg() != false)
		{
			// 弾
			_e_Bullet->UpDate();
		}
	}
	for (auto obj : _objList)
	{
		// ﾌﾟﾚｲﾔｰとｴﾈﾐｰ
		obj->UpDate();
	}

	// ｴﾈﾐｰと弾の当たり判定
	for (auto itr = std::remove_if(_objList.begin(), _objList.end(),
		[](shared_Obj& obj) {return obj->GetUnitType() == UNIT::ENEMY; }); itr != _objList.end(); itr++)
	{
		if ((*itr)->isAlive() != false && (*itr)->isDeath() != true)
		{
			(*itr)->CheckHit(_bulletList);
		}
	}
	// ﾌﾟﾚｲﾔｰと弾の当たり判定
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

	// ObjのisDeathがfalseの時(死亡時)に要素を削除する(末尾に削除したい要素をまとめて一回で消す)
	_objList.erase(std::remove_if(_objList.begin(),
		_objList.end(),
		[](shared_Obj& obj) {return (*obj).isDeath(); }), _objList.end());

	// ｽﾃｰｼﾞｸﾘｱの処理
	// 最後の敵のｲﾝｽﾀﾝｽの時間よりｹﾞｰﾑｶｳﾝﾄが大きいとき
	if (_gameCnt >= _enemyInsCnt.back())
	{
		// ｴﾈﾐｰのｲﾃﾚｰﾀｰ取得(remove_ifでｴﾈﾐｰを後ろに)
		auto itr = std::remove_if(_objList.begin(), _objList.end(),
			[](shared_Obj& obj) {return obj->GetUnitType() == UNIT::ENEMY; });

		// ｲﾃﾚｰﾀｰがendであればｹﾞｰﾑｸﾘｱ
		if (itr == _objList.end())
		{
			// 次のｽﾃｰｼﾞへ
			_stageNum++;
			if (_stageNum>=3)
			{
				if (!_clearFlag)
				{
					_clearFlag = true;
					_staretFlag = false;
					_gameCnt = 0;

					// SE
					lpSoundMng.SetSound("ｸﾘｱ");
				}
			}
			else
			{
				// 初期化
				_cnt = 0;
				_gameCnt = STAGE_STATE_TIME;
				
				// ｴﾈﾐｰのﾃﾞｰﾀ読み込み
				EnemyInit();

				// ｴﾈﾐｰのｲﾝｽﾀﾝｽ
				EnemyInstance();
			}
		}
	}
	if (_staretFlag)
	{
		// ﾌﾟﾚｲﾔｰのｲﾃﾚｰﾀｰ取得
		auto itr = std::find_if(_objList.begin(), _objList.end(),
			[](shared_Obj& obj) {return obj->GetUnitType() == UNIT::PLAYER; });

		// ｲﾃﾚｰﾀｰがendであればｹﾞｰﾑｵｰﾊﾞｰ
		if (itr == _objList.end())
		{
			_gameOverFlag = true;
		}
	}

	// 描画
 	Draw();

	if (_staretFlag)
	{
		// 敵のｲﾝｽﾀﾝｽ
		EnemyInstance();

		if (_gameCnt == STAGE_STATE_TIME + 60)
		{
			lpSoundMng.SetSound("ｽﾃｰｼﾞ");
		}
		// ｹﾞｰﾑ内ｶｳﾝﾄ
		_gameCnt++;
	}
	else
	{
		// ｽﾍﾟｰｽｷｰで始める
		if (keyFlagSp && !keyFlagSpOld)
		{
			// ｸﾘｱ後の処理
			if (_clearFlag)
			{
				// 初期化
				_stageNum = 1;
				_cnt = 0;
				for (auto itr : _objList)
				{
					if (itr->GetUnitType() == UNIT::PLAYER)
					{
						itr->hp(3);
					}
				}
				// ｴﾈﾐｰのﾃﾞｰﾀ読み込み
				EnemyInit();
				// ｽｺｱの初期化
				lpScoreMng.ScoreReset();

				_clearFlag = false;
			}

			// SE
			lpSoundMng.SetSound("ｽﾀｰﾄ");
			_staretFlag = true;
			_gameCnt = STAGE_STATE_TIME;
		}
		_gameCnt--;
	}
	// ｹﾞｰﾑｵｰﾊﾞｰ時
	if (_gameOverFlag)
	{
		_gameOverCnt--;
	}
	if (_gameOverCnt <= 0)
	{	
		// 新しくｼｰﾝを読み直す
		return std::make_unique<GameScene>();
	}
	else
	{
		// 所有権を渡す
		return std::move(own);
	}
}

void GameScene::Draw(void)
{
	int ghBefor;

	// 現在の画面を入れる
	ghBefor = GetDrawScreen();

	// 現在のｽｸﾘｰﾝをｹﾞｰﾑｼｰﾝ用ｽｸﾘｰﾝに変更
	SetDrawScreen(_ghGameScreen);

	// 背景色
	SetBackgroundColor(0, 0, 0);

	ClsDrawScreen();	// 画面消去

	// 描画
	for (auto _bullet : _bulletList)
	{
		if (_bullet->actFlg() != false)
		{
			// 弾
			_bullet->Obj::Draw();
		}
	}

	// 描画
	for (auto _bullet : _e_BulletList)
	{
		if (_bullet->actFlg() != false)
		{
			// 弾
			_bullet->Obj::Draw();
		}
	}
	for (auto obj : _objList)
	{
		// 現在ﾌﾟﾚｲﾔｰとｴﾈﾐｰ

		obj->Obj::Draw();
	}

	// 開始用文字
	if (!_staretFlag)
	{
		if (_gameCnt / 60 % 2 == 0)
		{
			// 文字の長さを取得
			int drawLengh;
			drawLengh = GetDrawStringWidthToHandle("- PUSH SPACE KEY -", strlen("- PUSH SPACE KEY -"), lpFontMng.SetFont("Sim40"));

			// 文字の表示
			DrawStringToHandle((lpSceneMng.gameScreenSize.x - drawLengh) / 2, 250, "- PUSH SPACE KEY -", 0xffffff, lpFontMng.SetFont("Sim40"));
		}
	}
	// ｽﾃｰｼﾞ用文字
	else
	{
		if (_gameCnt < -60 && _gameCnt > STAGE_STATE_TIME + 60)
		{
			int drawLengh;
			drawLengh = GetDrawFormatStringWidthToHandle(lpFontMng.SetFont("Sim40"), "STAGE %d", _stageNum);

			DrawFormatStringToHandle((lpSceneMng.gameScreenSize.x - drawLengh) / 2, 180, 0xffffff, lpFontMng.SetFont("Sim40"), "STAGE %d", _stageNum);
		}
	}
	// ｸﾘｱ時の文字
	if (_clearFlag)
	{
		// 文字の長さを取得
		int drawLengh;
		drawLengh = GetDrawStringWidthToHandle("CONGRATULATION!!", strlen("CONGRATULATION!!"), lpFontMng.SetFont("Sim40"));

		// 文字の表示
		DrawStringToHandle((lpSceneMng.gameScreenSize.x - drawLengh) / 2, 180, "CONGRATULATION!!", 0xffffff, lpFontMng.SetFont("Sim40"));
	}
	// ｹﾞｰﾑｵｰﾊﾞｰ時
	else if (_gameOverFlag)
	{
		// 文字の長さを取得
		int drawLengh;
		drawLengh = GetDrawStringWidthToHandle("-GAME OVER-", strlen("-GAME OVER-"), lpFontMng.SetFont("Sim40"));

		// 文字の表示
		DrawStringToHandle((lpSceneMng.gameScreenSize.x - drawLengh) / 2, 180, "-GAME OVER-", 0xffffff, lpFontMng.SetFont("Sim40"));
	}

	// ﾌﾟﾚｲﾔｰの残機表示
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

	// ｽｺｱの表示
	lpScoreMng.Draw();

	// 画像のｷｭｰ追加
	lpSceneMng.addDrawQue({ _ghGameScreen,lpSceneMng.gameScreenPos.x,lpSceneMng.gameScreenPos.y });

	// 元のｽｸﾘｰﾝに戻す
	SetDrawScreen(ghBefor);
}

SCN_ID GameScene::GetScnID(void)
{
	return SCN_ID::GAME;
}

bool GameScene::Init(void)
{
	// ｹﾞｰﾑｼｰﾝ用ｽｸﾘｰﾝの作成
	_ghGameScreen = MakeScreen(lpSceneMng.gameScreenSize.x, lpSceneMng.gameScreenSize.y, true);

	// 乱数の種を作成
	srand(time(NULL));

	// ｲﾝｽﾀﾝｽ(ﾘｽﾄに要素追加)
	// ﾌﾟﾚｲﾔｰ(画面下中央に配置)
	_objList.emplace_back(new Player(
		Vector2(lpSceneMng.gameScreenSize.x / 2, lpSceneMng.gameScreenSize.y - 16), _bulletList));

	// 残機画像
	_playerLife = LoadGraph("image/player.png");

	// ｴﾈﾐｰﾃﾞｰﾀの読み込み
	EnemyData();
	EnemyInit();

	// ｽｺｱの初期化
	lpScoreMng.ScoreReset();

	// ﾌｫﾝﾄの登録
	lpFontMng.FontInit("font/Simple.ttf", "Simple", "Sim30", 30, -1, false, false);
	lpFontMng.FontInit("font/Simple.ttf", "Simple", "Sim40", 40, -1, false, false);

	// SEの登録
	lpSoundMng.SoundInit("sound/Start.mp3", "ｽﾀｰﾄ");
	lpSoundMng.SoundInit("sound/StageSE.mp3", "ｽﾃｰｼﾞ");
	lpSoundMng.SoundInit("sound/Clear.mp3", "ｸﾘｱ");

	return true;
}

bool GameScene::EnemyData(void)
{
	// ｴﾈﾐｰ出現用座標ﾃｰﾌﾞﾙ作成
	_enemyPos.reserve(6);
	_enemyPos =
	{	// 左上,左中央,左下,右上,右中,右下
		Vector2Dbl(-16.0,15.0),
		Vector2Dbl(-16.0,static_cast<double>(lpSceneMng.gameScreenSize.y) / 2.0),
		Vector2Dbl(-16.0,static_cast<double>(lpSceneMng.gameScreenSize.y) - 15.0 - 40.0),
		Vector2Dbl(static_cast<double>(lpSceneMng.gameScreenSize.x) + 16.0,+15.0),
		Vector2Dbl(static_cast<double>(lpSceneMng.gameScreenSize.x) + 16.0,static_cast<double>(lpSceneMng.gameScreenSize.y) / 2.0),
		Vector2Dbl(static_cast<double>(lpSceneMng.gameScreenSize.x) + 16.0,static_cast<double>(lpSceneMng.gameScreenSize.y) - 15.0 - 40.0)
	};

	// ｴﾈﾐｰの最終目標地点
	for (int k = 0; k < 4; k++)
	{
		// ボス用
		_aimPos.emplace_back(Vector2(190 + (k * 40), 40));
	}
	for (int k = 0; k < 16; k++)
	{
		// 護衛用
		_aimPos.emplace_back(Vector2(110 + 40 * (k % 8), 80 + 40 * (k / 8 % 2)));
	}
	for (int k = 0; k < 20; k++)
	{
		// ザコ用
		_aimPos.emplace_back(Vector2(70 + 40 * (k % 10), 160 + 40 * (k / 10 % 2)));
	}

	return true;
}

bool GameScene::EnemyInit(void)
{
	Vector2Dbl tmp;
	MOVE_TYPE move;

	// 要素の削除
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
		INS_TIME,// 敵をｲﾝｽﾀﾝｽする時間
		F_POS_X, // 初期posX
		F_POS_Y, // 初期posY
	};
	FILE *fp = nullptr;
	char buf[256];
	int c;
	int col = 1;
	int row = 0;

	// bufのすべての要素に0を入れる(初期化)
	memset(buf, 0, sizeof(buf));

	if (_stageNum == 1)
	{
		// ﾌｧｲﾙ開く
		fopen_s(&fp, "Excel/Stage1.csv", "rb");
	}
	else if (_stageNum == 2)
	{
		// ﾌｧｲﾙ開く
		fopen_s(&fp, "Excel/Stage2.csv", "rb");
	}
	// ﾌｧｲﾙがなかったらfalseを返す
	if (&fp == nullptr)
	{
		return false;
	}
	else
	{
		//ヘッダ読み飛ばし
		while (fgetc(fp) != '\n');

		while (1)
		{
			while (1)
			{
				// 文字読み取り
				c = fgetc(fp);

				// 末尾ならﾙｰﾌﾟを抜ける。
				if (c == EOF)
				{
					goto out;
				}

				// ｶﾝﾏか改行でなければ、文字としてつなげる
				if (c != ',' && c != '\n')
				{
					strcat_s(buf, sizeof(buf), (const char*)&c);
				}
				// ｶﾝﾏか改行ならﾙｰﾌﾟ抜ける。

				else
				{
					break;
				}
			}
			// ここに来たということは、1セル分の文字列が出来上がったということ
			// atoi関数(int型で返す)で値を取得していく
			switch (col)
			{
			case INS_TIME:
				_enemyInsCnt.emplace_back(atoi(buf));
				break;
				//1列目は敵種類を表す。atoi関数で数値として代入。
			case F_POS_X:
				_enemyStartPos.emplace_back(_enemyPos[atoi(buf)]);
				break;
			case 3:		// ｴﾈﾐｰの種類
				_enemyType.emplace_back(static_cast<ENEMY_TYPE> (atoi(buf)));
				break;
			case 4:		// ｻｲｽﾞx
				tmp.x = static_cast<int>(atoi(buf));
				break;
			case 5:		// ｻｲｽﾞy
				tmp.y = static_cast<int>(atoi(buf));
				// 要素追加
				_enemySize.emplace_back(Vector2(tmp.x, tmp.y));
				break;
			case 6:		// 移動方法1の目標地点x
				tmp.x = atoi(buf);
			case 7:		// 移動方法2目標地点y
				tmp.y = atoi(buf);
				break;
			case 8:		// 移動方法1
				move = static_cast<MOVE_TYPE>(atoi(buf));
				// 要素追加
				_enemyAim.emplace_back(Vector2Dbl(tmp.x, tmp.y), move);
				break;
			case 9:		// 移動方法2の目標地点x
				tmp.x = atoi(buf);
				break;
			case 10:	// 移動方法2の目標地点y
				tmp.y = atoi(buf);
				break;
			case 11:	// 移動方法2
				move = static_cast<MOVE_TYPE>(atoi(buf));
				// 要素追加
				_enemyAim.emplace_back(Vector2Dbl(tmp.x, tmp.y), move);
				break;
			case 12:	// 移動方法3の目標地点y
				tmp.x = _aimPos[atoi(buf)].x;
				tmp.y = _aimPos[atoi(buf)].y;
				break;
			case 13:	// 移動方法3
				move = static_cast<MOVE_TYPE>(atoi(buf));
				// 要素追加
				_enemyAim.emplace_back(Vector2Dbl(tmp.x, tmp.y), move);
				break;
			default:
				break;
			}
			//バッファを初期化
			memset(buf, 0, sizeof(buf));

			//列数を足す
			++col;

			//もし読み込んだ文字が改行だったら列数を初期化して行数を増やす
			if (c == '\n')
			{
				col = 1;
				++row;
			}
		}
	}
out:

	// ﾌｧｲﾙを閉じる
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