#pragma once
#include "Vector2.h"

class Collision
{
public:
	Collision();
	~Collision();

};

// 当たり判定

// 矩形同士の当たり判定
// 引数(    始点, 終点 )
bool Square(Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2);

// 円同士の当たり判定 
// 引数(中心座標,半径)
bool Circle(Vector2 centerPos1, int r1, Vector2 centerPos2, int r2);

// 円と矩形の当たり判定
// 引数(中心座標,半径,矩形の始点,終点)
bool CircleToSpuare(Vector2 pos, int r, Vector2 startPos, Vector2 endPos);