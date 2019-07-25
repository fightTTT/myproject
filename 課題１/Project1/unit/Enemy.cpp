#include <DxLib.h>
#include <time.h>
#include <cmath>
#include "Enemy.h"
#include "../_DebugDispOut.h"
#include "../_DebugConOut.h"
#include "../common/ImageMng.h"

int Enemy::animCnt = 0;
bool Enemy::enemGather = false;

Enemy::Enemy()
{
	Init();	
}

Enemy::Enemy(EnemyData& data)
{
	_pos = std::get<static_cast<int>(ENM_DATA::POS)>(data);
	_size = std::get<static_cast<int>(ENM_DATA::SIZE)>(data);
	_type = std::get<static_cast<int>(ENM_DATA::TYPE)>(data);
	_targetPos = std::get<static_cast<int>(ENM_DATA::TARGTPOS)>(data);
	_enemCnt = std::get<static_cast<int>(ENM_DATA::ENEMNUM)>(data);
	enemCounter = std::get<static_cast<int>(ENM_DATA::ENEMCNT)>(data);
	Init();

	debgPos = _pos;
}

Enemy::~Enemy()
{
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

	data.reserve(5);
	data.emplace_back(IMAGE_ID("爆破")[0], 5);
	data.emplace_back(IMAGE_ID("爆破")[1], 15);
	data.emplace_back(IMAGE_ID("爆破")[2], 25);
	data.emplace_back(IMAGE_ID("爆破")[3], 35);
	data.emplace_back(IMAGE_ID("爆破")[4], 45);
	data.emplace_back(-1, 50);

	SetAnim(ANIM::DEATH, data);

	moveData.reserve(static_cast<int>(MOVE_TYPE::MAX));
	moveData.emplace_back(Vector2Dbl(100, 300), MOVE_TYPE::SIGMOID);
	moveData.emplace_back(Vector2Dbl(250, 300), MOVE_TYPE::SPIRAL);
	moveData.emplace_back(_targetPos, MOVE_TYPE::LR);

	speed = 0.1;
	X = -10;
	
	step = 0.1;
	_alive = true;
	firstFlag = true;
	waitCnt = 0;
	
	move = &Enemy::MoveWait;

	return true;
}


void Enemy::Draw(void)
{
	DrawGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y), ImageMng::GetInstance().GetID("キャラ")[11], true);
}

UNIT Enemy::GetUnit(void)
{
	return UNIT::ENEMY;
}

void Enemy::SetMove()
{
	//static int charCnt;
	//static int animCnt = 0;




	//死んだらtrueになる関数
	if (DeathProc())
	{
		return;
	}
	/*if (rand()%1200 == 0)
	{
		_alive = false;
		AnimKey(ANIM::DEATH);
	}*/

	_posOld = _pos;



	int color = 0x00ff00;
	if (firstFlag == false)
	{
		color = 0xff0000;
	}

	
	_DbgDrawBox(static_cast<int>(_pos.x), static_cast<int>(_pos.y), static_cast<int>(_pos.x) + 32, static_cast<int>(_pos.y) + 32, color, true);

	if (abs(std::get<0>(moveData[0]).x - _pos.x) < speed && abs(std::get<0>(moveData[0]).y - _pos.y) < speed && move == &Enemy::MoveSigmoid)
	{
		move = &Enemy::MoveSpiral;
	}

	(this->*move)();

	if (enemGather)
	{

	}

	animCnt++;
}

void Enemy::MoveSigmoid(void)
{
	auto sigmoid = [](double x) {return (1.0 / (1.0 + exp(x*-1.0))); };

	Vector2Dbl oneTimepos;

	oneTimepos.x = (X + 10)/20;
	oneTimepos.y = sigmoid(X);

	_pos.x = oneTimepos.x *(std::get<0>(moveData[0]).x-debgPos.x) + debgPos.x;
	_pos.y = oneTimepos.y *(std::get<0>(moveData[0]).y - debgPos.y) + debgPos.y;

	X += step;
/*
	if (X> 10)
	{
		step = 0;
		move = &Enemy::MoveSpiral;
	}*/

	_angle = atan2f(_pos.y - _posOld.y, _pos.x - _posOld.x);
	_angle += 90 * (DX_PI / 180);
}

void Enemy::MoveSpiral(void)
{
	_vel.x = cos(((DX_PI + (step / 120+3) * step) / 180)) * 2;
	_vel.y = sin(((DX_PI + (step / 120+3) * step) / 180)) * 2;
	if ((step / 120) > 2)
	{
		speed = 2;
		move = &Enemy::MoveLastTraget;
	}
	_pos += -_vel;
	step++;

	_angle = atan2f(_pos.y - _posOld.y, _pos.x - _posOld.x);
	_angle += 90 * (DX_PI / 180);
}

void Enemy::MoveLastTraget(void)
{
	float angle = atan2f(static_cast<float>(_targetPos.y - _pos.y), static_cast<float>(_targetPos.x - _pos.x));
	_vel.x = cos(angle) * speed;
	_vel.y = sin(angle) * speed;
	_pos += _vel;

	_angle = atan2f(_pos.y - _posOld.y, _pos.x - _posOld.x);
	_angle += 90 * (DX_PI / 180);

	if (abs(_targetPos.y - _pos.y) <= speed && abs(_targetPos.x - _pos.x) <= speed)
	{
		_pos = _targetPos;
		_angle = 0.0f;
		step = 0;
		move = &Enemy::MoveLR;
	}
}

void Enemy::MoveLR(void)
{
	
	if (enemGather)
	{
		float angle = atan2f(_pos.y - 0, _pos.x - 250);
		_vel.x = cos(angle)*0.5;
		_vel.y = sin(angle)*0.5;

		if (static_cast<int>(step) / 60 % 2 == 0)
		{
			_pos += _vel;
		}
		else
		{
			_pos -= _vel;
		}
		
		step++;
	}
	else
	{
		if (enemCounter == 40)
		{
			enemGather = true;
		}

	}
	
}
void Enemy::MoveWait(void)
{
	if (step > _enemCnt * 25)
	{
		step = 0.1;
		move = &Enemy::MoveSigmoid;
	}
	else
	{
		step++;
	}
}
