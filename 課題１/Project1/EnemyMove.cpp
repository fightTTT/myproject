#include <cmath>
#include "EnemyMove.h"
#include "common//Vector2.h"


EnemyMove::EnemyMove()
{
}

EnemyMove::EnemyMove(EnemyData enemData)
{


}


EnemyMove::~EnemyMove()
{
}

void EnemyMove::MoveSigmoid(void)
{
	//auto sigmoid = [](double x) {return (1.0 / (1.0 + exp(x*-1.0))); };

	//Vector2Dbl oneTimepos;

	//oneTimepos.x = (X + 10) / 20;
	//oneTimepos.y = sigmoid(X);

	//_pos.x = oneTimepos.x *(std::get<0>(moveData[0]).x - debgPos.x) + debgPos.x;
	//_pos.y = oneTimepos.y *(std::get<0>(moveData[0]).y - debgPos.y) + debgPos.y;

	//X += step;
	///*
	//	if (X> 10)
	//	{
	//		step = 0;
	//		move = &Enemy::MoveSpiral;
	//	}*/

	//_angle = atan2f(_pos.y - _posOld.y, _pos.x - _posOld.x);
	//_angle += 90 * (DX_PI / 180);
}

void EnemyMove::MoveSpiral(void)
{
}

void EnemyMove::MoveLastTarget(void)
{
}

void EnemyMove::MoveLR(void)
{
}

void EnemyMove::MoveWait(void)
{
}
