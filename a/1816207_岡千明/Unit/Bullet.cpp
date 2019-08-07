#include "Bullet.h"
#include <_Debug/_DebugConOut.h>

Bullet::Bullet()
{
	Init();
}

Bullet::Bullet(Vector2Dbl pos)
{
	// 速度
	_speed = { 0,5 };

	// 大きさ
	_size = { 3,4 };

	// 初期化用関数
	Init();

	// 生存用ﾌﾗｸﾞ｡初期はfalse(弾非表示)
	_alive = false;
}


Bullet::~Bullet()
{
}

void Bullet::Draw(void)
{
}

void Bullet::UpDate(void)
{
	// 弾は画面上部に向かって飛ぶ
	_pos.y-= _speed.y;

	// 画面外処理
	if (_pos.y + (_size.y / 2) < 0)
	{
		// ﾌﾗｸﾞをfalseに(非表示)
		_actFlg = false;
	}
}

UNIT Bullet::GetUnitType(void)
{
	return UNIT::P_Blt;
}

void Bullet::SetactFlg(Vector2Dbl pos)
{
	// 発射される座標
	_pos = pos;

	// 表示する
	_actFlg = true;
}

void Bullet::SetactFlg(void)
{
	_actFlg = false;
}

void Bullet::Init(void)
{
	// ｱﾆﾒｰｼｮﾝ登録
	AnimVector data;
	data.reserve(1);

	// ｷｬﾗｸﾀｰ画像
	data.emplace_back(IMAGE_ID("弾")[0], 0);
	
	// ﾉｰﾏﾙに登録
	SetAnim(ANIM::NORMAL, data);

	// ﾃﾞﾊﾞｯｸｳｨﾝﾄﾞｳ
	TRASE("%d:%d\n", _pos.x, _pos.y);
}
