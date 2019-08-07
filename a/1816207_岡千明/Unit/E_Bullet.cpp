#include "E_Bullet.h"
#include <Scene/SceneMng.h>

E_Bullet::E_Bullet()
{
	// 初期化用関数
	Init();
}

E_Bullet::E_Bullet(Vector2Dbl pos)
{
	// 速度
	_speed = { 0,2 };

	// 大きさ
	_size = { 3,4 };

	// 初期化用関数
	Init();

	// 生存用ﾌﾗｸﾞ｡初期はfalse(弾非表示)
	_alive = false;

	_angle = DX_PI;
}


E_Bullet::~E_Bullet()
{
}

void E_Bullet::Draw(void)
{
}

void E_Bullet::UpDate(void)
{
	// 弾は画面下に向かって飛ぶ
	_pos.y += _speed.y;

	// 画面外処理
	if (lpSceneMng.gameScreenSize.y < _pos.y + (_size.y / 2))
	{
		// ﾌﾗｸﾞをfalseに(非表示)
		_actFlg = false;
	}
}

UNIT E_Bullet::GetUnitType(void)
{
	return UNIT::E_Blt;
}

void E_Bullet::SetactFlg(Vector2Dbl pos)
{
	// 発射される座標
	_pos = pos;

	// 表示する
	_actFlg = true;
}

void E_Bullet::SetactFlg(void)
{
	_actFlg = false;
}

void E_Bullet::Init(void)
{
	// ｱﾆﾒｰｼｮﾝ登録
	AnimVector data;
	data.reserve(1);

	// ｷｬﾗｸﾀｰ画像
	data.emplace_back(IMAGE_ID("弾")[1], 0);

	// ﾉｰﾏﾙに登録
	SetAnim(ANIM::NORMAL, data);

}
