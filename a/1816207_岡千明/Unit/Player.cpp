#include <DxLib.h>
#include "Player.h"
#include <Input/KeyState.h>
#include <Unit/Bullet.h>
#include <Scene/SceneMng.h>
#include <_Debug/_DebugConOut.h>
#include <_Debug/_DebugDispOut.h>
#include <Public/SoundMng.h>

Player::Player()
{
}

Player::Player(Vector2 pos)
{
	// 座標
	_pos.x = pos.x;
	_pos.y = pos.y;

	// 大きさ
	_size.x = 30;
	_size.y = 32;

	// 速度
	_speed = { 5,5 };

	// ﾃﾞﾊﾞｯｸｳｨﾝﾄﾞｳ
	TRASE("%d:%d\n", pos.x, pos.y);

	// ｺﾝﾄﾛｰﾗｰｸﾗｽ制作
	_input = std::make_unique<KeyState>();

	// 初期化関数
	Init();
}

Player::Player(Vector2 pos, std::list<std::shared_ptr<Bullet>>& list)
{
	// 座標
	_pos.x = pos.x;
	_pos.y = pos.y;

	// 大きさ
	_size.x = 30;
	_size.y = 32;

	// 速度
	_speed = { 5,5 };

	// 体力
	_hp = 3;
	_oldHp = _hp;

	//// ﾃﾞﾊﾞｯｸｳｨﾝﾄﾞｳ
	//TRASE("%d:%d\n", pos.x, pos.y);

	// ｺﾝﾄﾛｰﾗｰｸﾗｽ生成
	_input = std::make_unique<KeyState>();

	// 弾生成
	_bullet_vec.reserve(2);
	for (int k = 0; k < 2; k++)
	{
		// 2発まで出せるようにする
		_bullet_vec.emplace_back(std::make_shared<Bullet>(_pos));

		// GameSceneの弾用ﾘｽﾄにいれる
		list.emplace_back(_bullet_vec[k]);
	}

	// 初期化関数
	Init();
}


Player::~Player()
{
}

void Player::Draw(void)
{
	DrawGraph(_pos.x, _pos.y,
		ImageMng::GetInstance().GetID("ｷｬﾗ")[0],
		true);
}

void Player::UpDate(void)
{
	// 死亡時はreturnで返す
	if (DestroyPlock())
	{
		return;
	}

	// ｷｰ入力の状態更新
	_input->UpDate();

	// ﾌﾟﾚｲﾔｰの移動(左右のみ)
	int TmpPos = _pos.x;
	// 左移動
	if (_input->state(INPUT_ID::LEFT).first)
	{
		TmpPos -= _speed.x;
		// 画面外に出る場合
		if (_size.x / 2 > TmpPos)
		{
			// 補正
			TmpPos = _size.x / 2;
		}
	}
	// 右移動
	if (_input->state(INPUT_ID::RIGHT).first)
	{
		TmpPos += _speed.x;
		// 画面外に出る場合
		if (TmpPos > lpSceneMng.gameScreenSize.x - (_size.x / 2))
		{
			// 補正
			TmpPos = lpSceneMng.gameScreenSize.x - (_size.x / 2);
		}
	}
	// ここで移動
	_pos.x = TmpPos;

	// 弾発射(Zｷｰ)
	if (_input->state(INPUT_ID::BTN_1).first && !(_input->state(INPUT_ID::BTN_1).second))
	{
		for (int k = 0; k < 2; k++)
		{
			// ｱｸﾃｨﾌﾞでない弾を探す
			if (_bullet_vec[k]->actFlg() != true)
			{
				// 弾のflagをtrueにして出す
				_bullet_vec[k]->SetactFlg(_pos);

				// SE再生
				lpSoundMng.SetSound("ﾌﾟﾚｲﾔｰﾊﾞﾚｯﾄ");

				break;
			}
		}
	}

	//if ()
	//{

	//}
	// 死亡時
	else if (_hp <= 0)
	{
		if (_alive)
		{
			// SE再生
			lpSoundMng.SetSound("ﾌﾟﾚｲﾔｰ死亡");
			_alive = false;
		}
		// 爆発画像に差し替え
		animKey(ANIM::DEATH);
	}
	// ﾀﾞﾒｰｼﾞ時
	else if (_oldHp > _hp)
	{
		// SE
		lpSoundMng.SetSound("ﾀﾞﾒｰｼﾞ");
		_oldHp = _hp;
	}
	// ﾃﾞﾊﾞｯｸ用
	//_DebugDrawBox(_pos.x - _size.x / 2, _pos.y - _size.x / 2, _pos.x + _size.x / 2, _pos.y + _size.x / 2, 0x00fa9a, true);
	//_DebugDrawFormatString(0, 0, 0x00fa9a,"%d:%d", _pos.x, _pos.y);
}

UNIT Player::GetUnitType(void)
{
	return UNIT::PLAYER;
}

bool Player::Init(void)
{
	// ｱﾆﾒｰｼｮﾝ登録
	AnimVector data;
	data.reserve(2);

	// ｷｬﾗｸﾀｰ画像
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[0], 30);
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[1], 60);
	// ﾉｰﾏﾙに登録
	SetAnim(ANIM::NORMAL, data);

	// 領域を変更
	data.reserve(1);
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[2], 60);
	// EXに登録
	SetAnim(ANIM::EX, data);

	// 爆発用に領域を変更
	data.reserve(5);
	for (int k = 0; k < 4; k++)
	{
		// 爆発用画像登録
		data.emplace_back(IMAGE_ID("PL爆発")[k], 8 + (k * 8));

		if (k == 3)
		{
			data.emplace_back(-1, 8 + ((k + 1) * 8));
		}
	}
	// 爆発はEXに指定
	SetAnim(ANIM::DEATH, data);

	// SEの登録
	// 弾
	lpSoundMng.SoundInit("sound/P_Bullet.mp3", "ﾌﾟﾚｲﾔｰﾊﾞﾚｯﾄ");
	// ﾀﾞﾒｰｼﾞ
	lpSoundMng.SoundInit("sound/Damage.mp3", "ﾀﾞﾒｰｼﾞ");
	// 死亡
	lpSoundMng.SoundInit("sound/P_Destroy.mp3", "ﾌﾟﾚｲﾔｰ死亡");
	return true;
}
