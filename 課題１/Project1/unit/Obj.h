#pragma once
#include <memory>
#include <vector>
#include <map>
#include "../common/Vector2.h"

enum class ANIM	// アニメーションタイプ
{
	NORMAL,		// 通常
	EX,			// 特殊
	MAX
};

enum class UNIT
{
	PLAYER,		// プレイヤーユニット
	ENEMY,		// 敵
	MAX
};

class Obj;
using Shared_Obj = std::shared_ptr<Obj>;
using AnimVector = std::vector<std::pair<int, int>>;


class Obj
{
public:
	Obj();
	virtual ~Obj();
	virtual void Draw(void) = 0;
	void Draw(int id);
	virtual UNIT GetUnit(void) = 0;
protected:
	bool SetAnim(const ANIM key, const AnimVector &data);	// アニメーション情報をセットする
	Vector2 _pos;
private:
	std::map<ANIM, const AnimVector> _animMap;		// アニメーション情報を格納しているmap
};

