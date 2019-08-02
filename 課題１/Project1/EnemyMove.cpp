#include <DxLib.h>
#include <cmath>
#include "EnemyMove.h"
#include "common//Vector2.h"

bool EnemyMove::enemGather = false;

EnemyMove::EnemyMove()
{
}

EnemyMove::EnemyMove(EnemyData enemData)
{
	_pos = std::get<static_cast<int>(ENM_DATA::POS)>(enemData);
	_size = std::get<static_cast<int>(ENM_DATA::SIZE)>(enemData);
	_targetPos = std::get<static_cast<int>(ENM_DATA::TARGTPOS)>(enemData);
	_enemCnt = std::get<static_cast<int>(ENM_DATA::ENEMCNT)>(enemData);
	_enemNum = std::get<static_cast<int>(ENM_DATA::ENEMNUM)>(enemData);
	Init();
	InstancePos = _pos;
}


EnemyMove::~EnemyMove()
{
}

void EnemyMove::Init(void)
{
	moveData.reserve(static_cast<int>(MOVE_TYPE::MAX));
	if (_pos.x < 100)
	{
		leftFlag = true;
		moveData.emplace_back(Vector2Dbl(400, 200), MOVE_TYPE::SIGMOID);
	}
	else
	{
		leftFlag = false;
		moveData.emplace_back(Vector2Dbl(100, 200), MOVE_TYPE::SIGMOID);
	}

	moveData.emplace_back(Vector2Dbl(250, 300), MOVE_TYPE::SPIRAL);
	moveData.emplace_back(_targetPos, MOVE_TYPE::LR);

	speed = 0.1;
	X = -10;

	sigmoidStep = 0.1;
	move = &EnemyMove::MoveWait;
	enemGather = false;
}

void EnemyMove::SetMove(void)
{
	_posOld = _pos;

	if (abs(std::get<0>(moveData[0]).x - _pos.x) < speed && abs(std::get<0>(moveData[0]).y - _pos.y) < speed && move == &EnemyMove::MoveSigmoid)
	{
		move = &EnemyMove::MoveSpiral;
	}

	(this->*move)();
}

void EnemyMove::MoveSigmoid(void)
{
	auto sigmoid = [](double x) {return (1.0 / (1.0 + exp(x*-1.0))); };

	Vector2Dbl oneTimepos;

	oneTimepos.x = (X + 10) / 20;
	oneTimepos.y = sigmoid(X);

	_pos.x = oneTimepos.x *(std::get<0>(moveData[0]).x - InstancePos.x) + InstancePos.x;
	_pos.y = oneTimepos.y *(std::get<0>(moveData[0]).y - InstancePos.y) + InstancePos.y;

	X += sigmoidStep;
	/*
		if (X> 10)
		{
			step = 0;
			move = &Enemy::MoveSpiral;
		}*/

	_angle = atan2f(_pos.y - _posOld.y, _pos.x - _posOld.x);
	_angle += 90 * (DX_PI / 180);
}

void EnemyMove::MoveSpiral(void)
{
	if (leftFlag)
	{
		_vel.x = cos((sigmoidStep) * (DX_PI / 180) * 2) * 2;
		_vel.y = sin((sigmoidStep) * (DX_PI / 180) * 2) * 2;
	}
	else
	{
		_vel.x = -cos((sigmoidStep) * (DX_PI / 180) * 2) * 2;
		_vel.y = sin((sigmoidStep) * (DX_PI / 180) * 2) * 2;
	}

	if ((sigmoidStep / 120) > 2)
	{
		speed = 2;
		move = &EnemyMove::MoveLastTarget;
	}
	_pos += _vel;
	sigmoidStep++;

	_angle = atan2f(_pos.y - _posOld.y, _pos.x - _posOld.x);
	_angle += 90 * (DX_PI / 180);
}

void EnemyMove::MoveLastTarget(void)
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
		sigmoidStep = 0;
		move = &EnemyMove::MoveLR;
	}
}

void EnemyMove::MoveLR(void)
{
	if (enemGather)
	{
		float angle = atan2f(_pos.y - 0, _pos.x - 200);
		float len = hypot(200 - _pos.x, 0 - _pos.y);
		_vel.x = cos(angle) * (len * 0.002);
		_vel.y = sin(angle) * (len * 0.002);

		if (static_cast<int>(sigmoidStep) / 120 % 2 == 0)
		{
			_pos += _vel;
		}
		else
		{
			_pos -= _vel;
		}

		sigmoidStep++;
	}
	else
	{
		if (_enemNum == 40)
		{
			enemGather = true;
		}
	}
}

void EnemyMove::MoveWait(void)
{
	if (sigmoidStep > _enemCnt * 25)
	{
		sigmoidStep = 0.1;
		move = &EnemyMove::MoveSigmoid;
	}
	else
	{
		sigmoidStep++;   
	}
}
