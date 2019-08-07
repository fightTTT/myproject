#include <math.h>
#include <DxLib.h>
#include "Enemy.h"
#include <_Debug/_DebugDispOut.h>
#include <Scene/SceneMng.h>
#include <Scene/GameScene.h>
#include <Public/ScoreMng.h>
#include <Public/SoundMng.h>

Enemy::Enemy()
{
}

Enemy::Enemy(Vector2 pos)
{
	// 座標
	_pos.x = pos.x;
	_pos.y = pos.y;

	// 初期化用関数
	//Init();
	move = &Enemy::Sigmoid;
}

Enemy::Enemy(Enemy_State state)
{
	// 座標
	_pos = std::get<static_cast<int>(Enemy_State_ID::POS)>(state);

	// 初期座標
	_startPos = _pos;

	// 種類
	_type = std::get<static_cast<int>(Enemy_State_ID::TYPE)>(state);

	// 大きさ
	_size = std::get<static_cast<int>(Enemy_State_ID::SIZE)>(state);

	// 初期の移動
	_moveCnt = static_cast<int>(MOVE_TYPE::SIGMOID);

	// 目的地
	_aim = std::get<static_cast<int>(Enemy_State_ID::AIM)>(state);

	// ｽﾋﾟｰﾄﾞ
	_speed = { 2.0,2.0 };

	// 終点から始点を引いて残りの距離を出す(ｼｸﾞﾓｲﾄﾞ用)
	_len = _aim[_moveCnt].first - _startPos;

	// 半径(円運動用)
	_rad = 0;

	_secSigFlag = false;

	// ｼｸﾞﾓｲﾄﾞ用
	_cnt = -10;

	// 左右移動移行ﾌﾗｸﾞ
	_lrFlag = false;

	_centerPos.x = lpSceneMng.gameScreenSize.x / 2;
	_centerPos.y = -500;

	// HPとｽｺｱの設定
	if (_type == ENEMY_TYPE::A)
	{
		_score = 100;

		_hp = 1;
	}
	else if (_type == ENEMY_TYPE::B)
	{
		_score = 400;
	
		_hp = 1;
	}
	else if (_type == ENEMY_TYPE::C)
	{
		_score = 1000;
		_hp = 2;
	}

	_oldHp = _hp;

	// 弾生成
	_e_Bullet_vec.reserve(1);

	_e_Bullet_vec.emplace_back(std::make_shared<E_Bullet>(_pos));
	std::get<4>(state).emplace_back(_e_Bullet_vec[0]);

	// SEの登録
	// 弾
	lpSoundMng.SoundInit("sound/E_Bullet.mp3", "ｴﾈﾐｰﾊﾞﾚｯﾄ");
	// ﾀﾞﾒｰｼﾞ
	lpSoundMng.SoundInit("sound/Damage.mp3", "ﾀﾞﾒｰｼﾞ");
	// 死亡時
	lpSoundMng.SoundInit("sound/E_Destroy.mp3", "ｴﾈﾐｰ死亡");
	
	// 関数ﾎﾟｲﾝﾀｰ初期値(ｼｸﾞﾓｲﾄﾞに移行)
	move = &Enemy::Sigmoid;

	// 初期化用関数
	Init();
}

Enemy::~Enemy()
{
}

void Enemy::Draw(void)
{
}

void Enemy::UpDate(void)
{
	// 死亡時はreturnで返す
	if (DestroyPlock())
	{
		return;
	}

	if (lpSceneMng.cnt() % 120 < 60)
	{
		_gameCnt = lpSceneMng.cnt() % 120;
	}
	else
	{
		_gameCnt = 119 - (lpSceneMng.cnt() % 120);
	}

	if (_shotFlag)
	{
		if(_e_Bullet_vec[0]->actFlg()!=true)
		{
			if (rand() % 300 == 0)
			{
				_e_Bullet_vec[0]->SetactFlg(_pos);
				lpSoundMng.SetSound("ｴﾈﾐｰﾊﾞﾚｯﾄ");
			}
		}
	}

	// ｽﾃｰﾄ維持
	(this->*move)();

	// 死亡時
	if (_hp <= 0)
	{
		// ｽｺｱの加算
		lpScoreMng.AddScore(_score);

		if (_alive)
		{
			_alive = false;

			// SE
			lpSoundMng.SetSound("ｴﾈﾐｰ死亡");
		}
		// 爆発画像に差し替え
		animKey(ANIM::DEATH);
	}
	else if (_oldHp > _hp)
	{
		// ﾎﾞｽが青くなるｱﾆﾒｰｼｮﾝに変更
		animKey(ANIM::EX);
		// ｱﾆﾒｰｼｮﾝ用ｶｳﾝﾄのｾｯﾄ
		SetAnimCnt();

		// SE
		lpSoundMng.SetSound("ﾀﾞﾒｰｼﾞ");
		_oldHp = _hp;
	}

	//// ﾃﾞﾊﾞｯｸ用
	//_DebugDrawBox(_pos.x - _size.x / 2, _pos.y - _size.x / 2, _pos.x + _size.x / 2, _pos.y + _size.x / 2, 0xff4500, true);
}
// _aliveがture
// _aliveがfalseになったらtrueの処理はしない、deathがtrueになるための処理を行う
// _death = falseの時は死んだｱﾆﾒｰｼｮﾝ終わったらtrue

UNIT Enemy::GetUnitType(void)
{
	return UNIT::ENEMY;
}

bool Enemy::Init(void)
{
	// ｱﾆﾒｰｼｮﾝ登録
	AnimVector data;
	data.reserve(2);

	// ｷｬﾗｸﾀｰ画像
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[10 + (static_cast<int>(_type) * 10)], 30);
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[11 + (static_cast<int>(_type) * 10)], 60);

	// _animMapに登録(通常画像はNOMAL指定)
	SetAnim(ANIM::NORMAL, data);

	// 領域を変更
	data.reserve(1);
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[34], 30);
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[35], 60);
	// EXに登録
	SetAnim(ANIM::EX, data);

	// 爆発用に領域を変更
	data.reserve(5);

	for (int k = 0; k < 5; k++)
	{
		// 爆発用画像
		data.emplace_back(IMAGE_ID("敵爆発")[k], 5 + (k * 5));

		if (k == 4)
		{
			// ﾜﾝｼｮｯﾄ用
			data.emplace_back(-1, 5 + ((k + 1) * 5));
		}
	}
	// 爆発はEXに指定
	SetAnim(ANIM::DEATH, data);

	// ｱﾆﾒｰｼｮﾝ用ｶｳﾝﾄのｾｯﾄ
	SetAnimCnt();

	return true;
}

void Enemy::SetAnimCnt(void)
{
	_animCount = lpSceneMng.cnt() % LastAnimCnt();
}

void Enemy::Sigmoid()
{
	auto X = ((_cnt + 10) / 20);
	auto Y = 1.0 / (1.0 + exp(-1.0 * _cnt));

	// 1ﾌﾚｰﾑ前の座標(ｱﾆﾒｰｼｮﾝの向き用)
	auto oldPos = _pos;

	// 移動
	_pos.x = X * _len.x + _startPos.x;
	_pos.y = Y * _len.y + _startPos.y;

	// ｱﾆﾒｰｼｮﾝの向き
	_angle = atan2(_pos.y - oldPos.y, _pos.x - oldPos.x) + 90 * DX_PI / 180;

	if (round(_pos.x) == round(_aim[_moveCnt].first.x))
	{
		_cnt = 0;

		_moveCnt = static_cast<int>(MOVE_TYPE::SPIRAL);

		// 半径
		_rad = hypot(_aim[_moveCnt].first.x - _pos.x, _aim[_moveCnt].first.y - _pos.y);

		// 直径
		_diameter = _rad * 2;

		// 角度
		_radian = atan2(_aim[_moveCnt].first.y - _pos.y, _aim[_moveCnt].first.x - _pos.x);

		// 次の移動関数へ
		move = &Enemy::Spiral;
	}

	if (_cnt < 10)
	{
		_cnt += 0.2;
	}

}

void Enemy::Spiral(void)
{
	// 1ﾌﾚｰﾑ前の座標(ｱﾆﾒｰｼｮﾝの向き用)
	auto oldPos = _pos;

	// 初期に左から出現してた場合
	if (_startPos.x < 0)
	{
		// 移動(左回り)
		_pos.x = _aim[_moveCnt].first.x + cos(_radian) * _rad + _diameter;
		_pos.y = _aim[_moveCnt].first.y + sin(_radian) * -_rad;
	}
	// 右から来ていた場合
	else
	{
		// 移動(右回り)
		_pos.x = _aim[_moveCnt].first.x + _rad * -cos(_radian);
		_pos.y = _aim[_moveCnt].first.y + _rad * -sin(_radian);
	}

	// ｱﾆﾒｰｼｮﾝの向き
	_angle = atan2(_pos.y - oldPos.y, _pos.x - oldPos.x) + 90 * DX_PI / 180;

	// 半径が一定量小さくなったら
	if (_rad < 20)
	{
		_moveCnt = static_cast<int>(MOVE_TYPE::MOVE_LR);

		// 次の移動関数へ
		move = &Enemy::MoveLR;
	}

	// 円の大きさを変えていく
	_radian += 0.1;
	_rad--;

}

void Enemy::MoveLR(void)
{
	//// 中心座標から自分のposまでのﾍﾞｸﾄﾙ
	//Vector2Dbl a = _pos - _centerPos;

	//// 正規化
	//Vector2Dbl i = a / hypot(_pos.y, _pos.x);

	// ﾍﾞｸﾄﾙ
	Vector2Dbl i = _aim[_moveCnt].first - _centerPos;
	// 正規化
	Vector2Dbl k = i / hypot(i.x, i.y);
	k.y = k.y / 3;

	if (_lrFlag)
	{
		_pos.x = _aim[_moveCnt].first.x + k.x * _gameCnt;
		_pos.y = _aim[_moveCnt].first.y + k.y * _gameCnt;

		_shotFlag = true;
	}
	else if (_pos != _aim[_moveCnt].first)
	{

		// 目的地までの距離を出す
		float	_ang = atan2(_aim[_moveCnt].first.y - _pos.y, _aim[_moveCnt].first.x - _pos.x);

		// ｽﾋﾟｰﾄﾞの設定
		_speed.x = cos(_ang) * 10;
		_speed.y = sin(_ang) * 10;

		// 目的地まで
		if ((abs(_aim[_moveCnt].first.x - _pos.x) > abs(_speed.x)) && (abs(_aim[_moveCnt].first.y - _pos.y) > abs(_speed.y)))
		{
			// ｱﾆﾒｰｼｮﾝの向き
			_angle = atan2(_aim[_moveCnt].first.y - _pos.y, _aim[_moveCnt].first.x - _pos.x) + 90 * DX_PI / 180;

			// 移動
			_pos += _speed;
		}
		else
		{
			// ずれてたらそろえる
			_speed = _aim[_moveCnt].first - _pos;
			_pos += _speed;

			// 目標地点に到達してるので左右移動に移行
			_lrFlag = true;

			// ｱﾆﾒｰｼｮﾝの向き
			_angle = 0;
		}
	}


}
