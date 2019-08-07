#pragma once
#include "Vector2.h"

class Collision
{
public:
	Collision();
	~Collision();

};

// �����蔻��

// ��`���m�̓����蔻��
// ����(    �n�_, �I�_ )
bool Square(Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2);

// �~���m�̓����蔻�� 
// ����(���S���W,���a)
bool Circle(Vector2 centerPos1, int r1, Vector2 centerPos2, int r2);

// �~�Ƌ�`�̓����蔻��
// ����(���S���W,���a,��`�̎n�_,�I�_)
bool CircleToSpuare(Vector2 pos, int r, Vector2 startPos, Vector2 endPos);