#include <Dxlib.h>
#include <algorithm>
#include <common/Collision.h>
#include "Obj.h"
#include "Bullet.h"
#include "E_Bullet.h"

Obj::Obj()
{
	// 初期化
	// ｱﾆﾒｰｼｮﾝ用
	_animCount	= 0;
	_animFrame	= 0;
	_angle = 0;
	_animKey = ANIM::NORMAL;

	// 生存用ﾌﾗｸﾞ
	_alive = true;
	_death = false;
}

Obj::~Obj()
{
}

void Obj::Draw(void)
{
	// 範囲ﾁｪｯｸ
	// 無かったらreturn
	if (_animMap.find(_animKey) == _animMap.end())
	{
		return;
	}
	// 総ｺﾏ数を超えていたら
	if (_animMap[_animKey].size() <= _animFrame)
	{
		return;
	}

	// 設定したﾌﾚｰﾑ数まで
	if (_animCount >= _animMap[_animKey][_animFrame].second)
	{
		// ｱﾆﾒｰｼｮﾝのｺﾏを進める
		_animFrame++;

		// ﾙｰﾌﾟｱﾆﾒｰｼｮﾝ用､	総ｺﾏ数超えたら初期値に戻す
		if (_animFrame >= _animMap[_animKey].size())
		{
			// 初期値に設定
			_animCount	= 0;
			_animFrame	= 0;
		}
	}

	DrawRotaGraph(_pos.x, _pos.y, 1, _angle, _animMap[_animKey][_animFrame].first, true);

	// ﾌﾚｰﾑ管理用､ｶｳﾝﾄはなるべく後ろに書く
	_animCount++;
}

void Obj::Draw(int id)
{
	DrawRotaGraph(_pos.x, _pos.y, 1, _angle, id, true);
}

bool Obj::animKey(const ANIM key)
{
	// 範囲ﾁｪｯｸ
	if ((key < ANIM::NORMAL) || (ANIM::MAX < key))
	{
		return false;
	}
	// ｱﾆﾒｰｼｮﾝの種類が変わったらｶｳﾝﾄを初期化
	if (_animKey != key)
	{
		_animCount = 0;
	}		

	_animKey = key;

	return true;
}

const ANIM Obj::animKey(void) const
{
	return _animKey;
}

const Vector2Dbl Obj::pos(void) const
{
	return _pos;
}

const Vector2 Obj::size(void) const
{
	return _size;
}

void Obj::hp(const int val)
{
	_hp = _hp + val;
	if (_hp + val >= 3)
	{
		_hp = 3;
	}
}

const int Obj::hp(void) const
{
	return _hp;
}

bool Obj::isAnimEnd(void)
{
	// 範囲ﾁｪｯｸ
	// 無かったらreturn
	if (_animMap.find(_animKey) == _animMap.end())
	{
		return false;
	}
	// 総ｺﾏ数を超えていたら
	if (_animMap[_animKey].size() <= _animFrame)
	{
		return false;
	}
	// ｱﾆﾒｰｼｮﾝの最後が-1ならばtrueを返す(ﾜﾝｼｮｯﾄ用)
	return (_animMap[_animKey][_animFrame].first == -1 ? true : false);
}

void Obj::SetAlive(bool alive)
{
	_alive = alive;
}

void Obj::CheckHit(std::vector<shared_Obj>& objList)
{
	Vector2 myStartPos;
	myStartPos.x = static_cast<int>(_pos.x) - (_size.x / 2);
	myStartPos.y = static_cast<int>(_pos.y) - (_size.y / 2);
	Vector2 myEndPos;
	myEndPos.x = static_cast<int>(_pos.x) + (_size.x / 2);
	myEndPos.y = static_cast<int>(_pos.y) + (_size.y / 2);

	for (auto itr = std::remove_if(objList.begin(), objList.end(),
		[](shared_Obj& obj) {return obj->GetUnitType() == UNIT::PLAYER; }); itr != objList.end(); itr++)
	{
		if ((*itr)== nullptr && ((*itr)->isAlive() == false && (*itr)->isDeath() == true))
		{
			continue;
		}

		auto playerPos = (*itr)->pos();
		auto playerSize = (*itr)->size();

		Vector2 playerStartPos;
		playerStartPos.x = static_cast<int>(playerPos.x) - playerSize.x;
		playerStartPos.y = static_cast<int>(playerPos.y) - playerSize.y;

		Vector2 playerEndPos;
		playerEndPos.x = static_cast<int>(playerPos.x) + playerSize.x;
		playerEndPos.y = static_cast<int>(playerPos.y) + playerSize.y;

		// 当たり判定を行う
		if (Square(myStartPos, myEndPos, playerStartPos, playerEndPos))
		{
			(*itr)->hp(-1);
			_hp = _hp - 1;
		}
	}
}

void Obj::CheckHit(std::list<std::shared_ptr<Bullet>>& bulletlist)
{
	Vector2 myStartPos;
	myStartPos.x = static_cast<int>(_pos.x) - (_size.x / 2);
	myStartPos.y = static_cast<int>(_pos.y) - (_size.y / 2);
	Vector2 myEndPos;
	myEndPos.x = static_cast<int>(_pos.x) + (_size.x / 2);
	myEndPos.y = static_cast<int>(_pos.y) + (_size.y / 2);

	for (auto &obj : bulletlist)
	{
		if ((*obj).actFlg() == false)
		{
			continue;
		}

		auto bulletPos = (*obj).pos();
		auto bulletSize = (*obj).size();

		Vector2 bulletStartPos;
		bulletStartPos.x = static_cast<int>(bulletPos.x) - bulletSize.x;
		bulletStartPos.y = static_cast<int>(bulletPos.y) - bulletSize.y;

		Vector2 bulletEndPos;
		bulletEndPos.x = static_cast<int>(bulletPos.x) + bulletSize.x;
		bulletEndPos.y = static_cast<int>(bulletPos.y) + bulletSize.y;

		// 当たり判定を行う
		if (Square(myStartPos, myEndPos, bulletStartPos, bulletEndPos))
		{		
			(*obj).SetactFlg();
			_hp = _hp - 1;
		}
	}
}
void Obj::CheckHit(std::list<std::shared_ptr<E_Bullet>>& bulletlist)
{
	Vector2 myStartPos;
	myStartPos.x = static_cast<int>(_pos.x) - (_size.x / 2);
	myStartPos.y = static_cast<int>(_pos.y) - (_size.y / 2);
	Vector2 myEndPos;
	myEndPos.x = static_cast<int>(_pos.x) + (_size.x / 2);
	myEndPos.y = static_cast<int>(_pos.y) + (_size.y / 2);

	for (auto &obj : bulletlist)
	{
		if ((*obj).actFlg() == false)
		{
			continue;
		}

		auto bulletPos = (*obj).pos();
		auto bulletSize = (*obj).size();

		Vector2 bulletStartPos;
		bulletStartPos.x = static_cast<int>(bulletPos.x) - bulletSize.x;
		bulletStartPos.y = static_cast<int>(bulletPos.y) - bulletSize.y;

		Vector2 bulletEndPos;
		bulletEndPos.x = static_cast<int>(bulletPos.x) + bulletSize.x;
		bulletEndPos.y = static_cast<int>(bulletPos.y) + bulletSize.y;

		// 当たり判定を行う
		if (Square(myStartPos, myEndPos, bulletStartPos, bulletEndPos))
		{
			(*obj).SetactFlg();
			_hp = _hp - 1;
		}
	}
}

bool Obj::DestroyPlock(void)
{
	// 生きていたらretrun
	if (_alive)
	{
		return false;
	}

	// ﾜﾝｼｮｯﾄ用ｱﾆﾒｰｼｮﾝが終わったら
	if (isAnimEnd())
	{
		_death = true;
	}

	return true;
}


int Obj::LastAnimCnt(void)
{
	return _animMap[_animKey][_animMap[_animKey].size() - 1].second;
}

bool Obj::SetAnim(const ANIM key,AnimVector& data)
{
	// 初期に確保したﾒﾓﾘｰを最後まで使う(dataはﾛｰｶﾙ変数なのでmoveでOK)
	return _animMap.try_emplace(key, std::move(data)).second;
}
//std::map   （keyｱﾆﾒｰｼｮﾝのID   （date画像のID､表示ﾌﾚｰﾑ）１コマもあれば複数もあるvectorを使う）一つのアニメーション
//std::pair<型1,型2>名前;宣言の場合
// 終端ｰ1(ループ終わる)