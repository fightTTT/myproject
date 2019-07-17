#include <DxLib.h>
#include <time.h>
#include <cmath>
#include "Enemy.h"
#include "../_DebugDispOut.h"
#include "../_DebugConOut.h"
#include "../common/ImageMng.h"

int Enemy::animCnt = 0;

Enemy::Enemy()
{
	Init();
	
}

Enemy::Enemy(EnemyData data)
{
	_pos = std::get<static_cast<int>(ENM_DATA::POS)>(data);
	_size = std::get<static_cast<int>(ENM_DATA::SIZE)>(data);
	_type = std::get<static_cast<int>(ENM_DATA::TYPE)>(data);
	_targetPos = std::get<static_cast<int>(ENM_DATA::TARGTPOS)>(data);

	Init();

	

	//-----------------
	/*_floatPosX = _pos.x;
	_floatPosY = _pos.y;*/
	//-----------------
}


Enemy::~Enemy()
{
}

void Enemy::Draw(void)
{
	DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y), ImageMng::GetInstance().GetID("�L����")[11], true);

}

UNIT Enemy::GetUnit(void)
{
	return UNIT::ENEMY;
}

void Enemy::SetMove()
{
	//static int charCnt;
	//static int animCnt = 0;

	//���񂾂�true�ɂȂ�֐�
	if (Active())
	{
		return;
	}
	/*if (rand()%1200 == 0)
	{
		_alive = false;
		AnimKey(ANIM::DEATH);
	}*/

	animCnt++;

	int color = 0x00ff00;
	if (firstFlag == false)
	{
		color = 0xff0000;
	}

	_posOld = _pos;
	_DbgDrawBox(static_cast<int>(_pos.x), static_cast<int>(_pos.y), static_cast<int>(_pos.x) + 32, static_cast<int>(_pos.y) + 32, color, true);

	if (firstFlag)
	{
		if ((abs(_firstTarget.x - _pos.x) > speed || abs(_firstTarget.y - _pos.y) > speed))
		{

			float angle = atan2(_firstTarget.y - _pos.y, _firstTarget.x - _pos.x);
			_angle = atan2(_firstTarget.y - _pos.y, _firstTarget.x - _pos.x)+ (90 * (DX_PI / 180));

			_pos.x += (cos(angle)*speed);
			_pos.y += (sin(angle)*speed);

			/*_pos.x = static_cast<int>(_floatPosX);
			_pos.y = static_cast<int>(_floatPosY);*/
		}

		if ((abs(_firstTarget.x - _pos.x) <= speed && abs(_firstTarget.y - _pos.y) <= speed))
		{
			_angle = 0.0f;
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
		float angle = atan2f(static_cast<float>(_targetPos.y - _pos.y), 
							 static_cast<float>(_targetPos.x - _pos.x));
		_angle = atan2f(static_cast<float>(_targetPos.y - _pos.y), static_cast<float>(_targetPos.x - _pos.x));
		_angle += 90 * (DX_PI / 180);
		_pos.x += (cos(angle)*speed);
		_pos.y += (sin(angle)*speed);

		/*_pos.x = static_cast<int>(_floatPosX);
		_pos.y = static_cast<int>(_floatPosY);*/
		if ((abs(_targetPos.x - _pos.x) <= speed && abs(_targetPos.y - _pos.y) <= speed))
		{
			_angle = 0.0f;
		}


	}
	TRACE("x%d:y%d\n", static_cast<int>(_pos.x - _posOld.x), static_cast<int>(_pos.y - _posOld.y));

	//animCnt++;

	_DbgDrawFormatString(0, 15, 0xff00ff, "enemyPos:%d,%d", _pos.x, _pos.y);
}

bool Enemy::Init(void)
{
	AnimVector data;

	//data.push_back(std::make_pair(IMAGE_ID("�L����")[0],30));

	// ��L��push_back�Ɠ�������
	/*data.emplace_back(IMAGE_ID("�L����")[10], 30);
	data.emplace_back(IMAGE_ID("�L����")[11], 60);*/

	data.reserve(2);
	switch (_type)
	{
	case ENM_TYPE::A:
		data.emplace_back(IMAGE_ID("�L����")[10], 30);
		data.emplace_back(IMAGE_ID("�L����")[11], 60);
		break;
	case ENM_TYPE::B:
		data.emplace_back(IMAGE_ID("�L����")[20], 30);
		data.emplace_back(IMAGE_ID("�L����")[21], 60);
		break;
	case ENM_TYPE::C:
		data.emplace_back(IMAGE_ID("�L����")[30], 30);
		data.emplace_back(IMAGE_ID("�L����")[31], 60);
		break;
	default:
		break;
	}
	SetAnim(ANIM::NORMAL, data);

	_firstTarget = { 250,300 };

	data.reserve(5);
	data.emplace_back(IMAGE_ID("���j")[0], 5);
	data.emplace_back(IMAGE_ID("���j")[1], 15);
	data.emplace_back(IMAGE_ID("���j")[2], 25);
	data.emplace_back(IMAGE_ID("���j")[3], 35);
	data.emplace_back(IMAGE_ID("���j")[4], 45);
	data.emplace_back(-1, 50);

	SetAnim(ANIM::DEATH, data);


	speed = 2;

	_animCnt = animCnt % 30;

	_alive = true;
	firstFlag = true;
	waitCnt = 0;

	return true;
}