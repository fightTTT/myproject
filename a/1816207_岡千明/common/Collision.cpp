#include <math.h>
#include "Collision.h"

Collision::Collision()
{
}

Collision::~Collision()
{
}

bool Square(Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2)
{
	// 必ずstartPosが左上、endPosが右下になるように入れ替える
	auto swap = [](int &start, int &end)
	{
		if (start > end)
		{
			int tmp = start;
			start = end;
			end = tmp;
		}
	};
	swap(startPos1.x, endPos1.x);
	swap(startPos1.y, endPos1.y);
	swap(startPos2.x, endPos2.x);
	swap(startPos2.y, endPos2.y);

	Vector2 length1 = endPos1 - startPos1;
	Vector2 length2 = endPos2 - startPos2;
	if ((startPos1.x > startPos2.x + length2.x) || (startPos1.x + length1.x < startPos2.x)
		|| (startPos1.y > startPos2.y + length2.y) || (startPos1.y + length1.y < startPos2.y))
	{
		return false;	// 衝突してない
	}
	return true;		// 衝突している
}

bool Circle(Vector2 centerPos1, int r1, Vector2 centerPos2, int r2)
{
	Vector2 length = centerPos1 - centerPos2;
	length = length * length;
	int r = static_cast<int>(sqrt(length.x + length.y));
	if (r >= r1 + r2)
	{
		return false;
	}
	return true;
}

bool CircleToSpuare(Vector2 pos, int r, Vector2 startPos, Vector2 endPos)
{
	// 必ずstartPosが左上、endPosが右下になるように入れ替える
	auto swap = [](int &start, int &end)
	{
		if (start > end)
		{
			int tmp = start;
			start = end;
			end = tmp;
		}
	};
	swap(startPos.x, endPos.x);
	swap(startPos.y, endPos.y);

	if (pos.x >= startPos.x - r && pos.x <= endPos.x + r
		&& pos.y >= startPos.y && pos.y <= endPos.y)
	{
		return true;
	}
	if (pos.x >= startPos.x && pos.x <= endPos.x
		&& pos.y >= startPos.y - r && pos.y <= endPos.y + r)
	{
		return true;
	}

	Vector2 sidePos[4] = {
		startPos,
		Vector2(startPos.x,endPos.y),
		Vector2(endPos.x , startPos.y),
		endPos
	};
	for (int j = 0; j < 4; j++)
	{
		if (Circle(pos, 1, sidePos[j], r))
		{
			return true;
		}
	}
	return false;
}
