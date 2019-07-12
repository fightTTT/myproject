#include <DxLib.h>
#include <time.h>
#include <cmath>
#include "Enemy.h"
#include "../_DebugDispOut.h"
#include "../common/ImageMng.h"


Enemy::Enemy()
{
	Init();
}

Enemy::Enemy(const Vector2& pos, ENM_TYPE type, const Vector2& size, const Vector2& targetPos)
{
	_pos = pos;
	_size = size;
	_type = type;
	_targetPos = targetPos;

	Init();
}


Enemy::~Enemy()
{
}

void Enemy::Draw(void)
{
	DrawGraph(_pos.x, _pos.y, ImageMng::GetInstance().GetID("キャラ")[11], true);
}

UNIT Enemy::GetUnit(void)
{
	return UNIT::ENEMY;
}

void Enemy::SetMove()
{
	if (Active())
	{
		return;
	}
	//if (rand()%1200 == 0)
	//{
	//	_alive = false;
	//	AnimKey(ANIM::DEATH);
	//}
	if (firstFlag)
	{
		if ((abs(_firstTarget.x - _pos.x) > speed || abs(_firstTarget.y - _pos.y) > speed))
		{
			float angle = atan2(_firstTarget.y - _pos.y, _firstTarget.x - _pos.x);
			_pos.x += cos(angle)*speed;
			_pos.y += sin(angle)*speed;

		}

		if ((abs(_firstTarget.x - _pos.x) < speed && abs(_firstTarget.y - _pos.y) < speed))
		{
			_pos = _firstTarget;
			waitCnt++;
			if (waitCnt > 60)
			{
				firstFlag = false;
			}
		}
	}
	else if (!firstFlag&&(abs(_targetPos.x - _pos.x) > speed || abs(_targetPos.y - _pos.y) > speed))
	{
		float angle = atan2(_targetPos.y - _pos.y, _targetPos.x - _pos.x);
		_pos.x += cos(angle)*speed;
		_pos.y += sin(angle)*speed;
	}
	else
	{

	}
	

	_DbgDrawFormatString(0, 15, 0xff00ff, "enemyPos:%d,%d", _pos.x, _pos.y);
}

bool Enemy::Init(void)
{
	AnimVector data;

	//data.push_back(std::make_pair(IMAGE_ID("キャラ")[0],30));

	// 上記のpush_backと同じ処理
	/*data.emplace_back(IMAGE_ID("キャラ")[10], 30);
	data.emplace_back(IMAGE_ID("キャラ")[11], 60);*/

	data.reserve(2);
	switch (_type)
	{
	case ENM_TYPE::A:
		data.emplace_back(IMAGE_ID("キャラ")[10], 30);
		data.emplace_back(IMAGE_ID("キャラ")[11], 60);
		break;
	case ENM_TYPE::B:
		data.emplace_back(IMAGE_ID("キャラ")[20], 30);
		data.emplace_back(IMAGE_ID("キャラ")[21], 60);
		break;
	case ENM_TYPE::C:
		data.emplace_back(IMAGE_ID("キャラ")[30], 30);
		data.emplace_back(IMAGE_ID("キャラ")[31], 60);
		break;
	default:
		break;
	}
	SetAnim(ANIM::NORMAL, data);

	_firstTarget = { 300,300 };

	data.reserve(5);
	data.emplace_back(IMAGE_ID("爆破")[0], 5);
	data.emplace_back(IMAGE_ID("爆破")[1], 15);
	data.emplace_back(IMAGE_ID("爆破")[2], 25);
	data.emplace_back(IMAGE_ID("爆破")[3], 35);
	data.emplace_back(IMAGE_ID("爆破")[4], 45);
	data.emplace_back(-1, 50);

	SetAnim(ANIM::DEATH, data);

	speed = 3;

	_alive = true;
	firstFlag = true;
	waitCnt = 0;

	return true;
}