#pragma once
#include <vector>
#include <list>
#include <map>
#include <memory>
#include <tuple>
#include <Public/ImageMng.h>
#include <common/Vector2.h>

// ｸﾗｽ宣言
class Obj;
class Bullet;
class E_Bullet;

// using宣言
using shared_Obj = std::shared_ptr<Obj>;				// ｼｪｱｰﾄﾞﾎﾟｲﾝﾀｰ
using shared_Blt = std::shared_ptr<Bullet>;				// ｼｪｱｰﾄﾞﾎﾟｲﾝﾀｰ
using shared_E_Blt = std::shared_ptr<E_Bullet>;				// ｼｪｱｰﾄﾞﾎﾟｲﾝﾀｰ
using AnimVector = std::vector<std::pair<int, int>>;	// ｱﾆﾒｰｼｮﾝ用のﾍﾟｱ

// ｱﾆﾒｰｼｮﾝの種類
enum class ANIM
{
	NORMAL,	// 通常
	EX,		// 特殊
	DEATH,	// 死亡
	MAX
};

// ｵﾌﾞｼﾞｪｸﾄの種類
enum class UNIT
{
	PLAYER,	// ﾌﾟﾚｲﾔｰ
	P_Blt,	// ﾌﾟﾚｲﾔｰの弾
	ENEMY,	// 敵
	E_Blt,	// 敵の弾
	MAX
};

// ｴﾈﾐｰの種類
enum class ENEMY_TYPE
{
	A,	// 
	B,	// 
	C,	//
	MAX
};

// ｴﾈﾐｰの引数用
enum class Enemy_State_ID
{
	POS,	// 座標
	TYPE,	// 種類
	SIZE,	// 大きさ
	AIM,	// 目的地
	MAX
};

// ｴﾈﾐｰ移動ﾀｲﾌﾟ
enum class MOVE_TYPE
{
	SIGMOID,	// ｼｸﾞﾓｲﾄﾞ
	SPIRAL,		// 回転
	MOVE_LR,	// 左右移動
	MAX
};

// ｴﾈﾐｰの左右移動用
enum class TYPE_LR
{
	TYPE_L,	// 左移動
	TYPE_R,	// 右移動
	MAX
};
// using宣言
// ｴﾈﾐｰの目的地､移動ﾀｲﾌﾟ
using AIM_VEC = std::vector<std::pair<Vector2Dbl, MOVE_TYPE>>;

// ｴﾈﾐｰのｲﾝｽﾀﾝｽ情報用｡引数は(Vector2 座標,敵の種類,ｻｲｽﾞ,目的地)
using Enemy_State = std::tuple<Vector2Dbl, ENEMY_TYPE, Vector2, AIM_VEC,std::list<std::shared_ptr<E_Bullet>>&>;

class Obj
{
public:
	Obj();
	virtual ~Obj();

	virtual void Draw(void);						// 描画関数
	void Draw(int id);								// 引数付き描画関数(引数はImageMngのGetIDを入れる)

	virtual void UpDate(void) = 0;					// 状態更新用関数(純粋仮想関数)

	virtual UNIT GetUnitType(void) = 0;				// UNITのIDを返す

	bool animKey(const ANIM key);					// _animKeyのｾｯﾀｰ
	const ANIM animKey(void) const;					// _animKeyのｹﾞｯﾀｰ

	const Vector2Dbl pos(void) const;				// _posのｹﾞｯﾀｰ
	const Vector2 size(void) const;					// _sizeのｹﾞｯﾀｰ
	void hp(const int val);							// _hpのｾｯﾀｰ
	const int hp(void)const;						// _hpのｹﾞｯﾀｰ

	bool isAnimEnd(void);							// ｱﾆﾒｰｼｮﾝのﾜﾝｼｮｯﾄ用

	void SetAlive(bool alive);						// 生存判定用ﾌﾗｸﾞのｾｯﾀｰ
	bool isAlive(void) { return _alive; };			// 叙述関数
	bool isDeath(void) { return _death; };			// 叙述関数(死亡用)

	void CheckHit(std::vector<shared_Obj>& objList);	// 当たり判定(ﾌﾟﾚｲﾔｰとｴﾈﾐｰ用)
	void CheckHit(std::list<std::shared_ptr<Bullet>>& bulletlist);	// 当たり判定(弾用)
	void CheckHit(std::list<std::shared_ptr<E_Bullet>>& bulletlist);	// 当たり判定(弾用)

private:
	std::map<ANIM, AnimVector>_animMap;				// ｱﾆﾒｰｼｮﾝ登録用map
	ANIM _animKey;									// ｱﾆﾒｰｼｮﾝの名前ID
	int _animFrame;									// ｱﾆﾒｰｼｮﾝのﾌﾚｰﾑ数

protected:
	bool SetAnim(const ANIM key, AnimVector& data);	// ｱﾆﾒｰｼｮﾝ登録用関数
	int LastAnimCnt(void);							// ｱﾆﾒｰｼｮﾝｶｳﾝﾄの取得
	int _animCount;									// ｱﾆﾒｰｼｮﾝ用ｶｳﾝﾄ

	bool DestroyPlock(void);						// _alive = falseでﾜﾝｼｮｯﾄｱﾆﾒｰｼｮﾝが終わったら_death =trueにする
	float _angle;									// ｱﾆﾒｰｼｮﾝの向き用

	bool _alive;									// 生存判定用ﾌﾗｸﾞ通常true,falseでﾜﾝｼｮｯﾄｱﾆﾒｰｼｮﾝなどを使用する
	bool _death;									// 死亡判定用ﾌﾗｸﾞ通常false,ﾜﾝｼｮｯﾄｱﾆﾒｰｼｮﾝが終わったらtrueになる

	Vector2Dbl _pos;								// 座標
	Vector2 _size;									// ｵﾌﾞｼﾞｪｸﾄの大きさ
	Vector2Dbl _speed;								// 速度
	int _hp;										// 体力
	int _oldHp;										// 1ﾌﾚｰﾑ前の体力
};

// map
// kye = std::string でｱﾆﾒｰｼｮﾝ名
// data = [画像ID､ﾌﾚｰﾑ数]
// ｺﾏ数

// map<ANIM(種類), vecor<pair<int画像ID, intFrame数>>>
// _animMap[ANIM::種類][ﾌﾚｰﾑ].first(IMAGE_ID("名前")[〇])
// _animMap[ANIM::種類][ﾌﾚｰﾑ].second(表示するﾌﾚｰﾑ数)
// _animMap[ANIM::種類].size()←要素数

//std::map   （keyｱﾆﾒｰｼｮﾝのID   （date画像のID､表示ﾌﾚｰﾑ）１コマもあれば複数もあるvectorを使う）一つのアニメーション
//std::pair<型1,型2>名前;宣言の場合
// 終端ｰ1(ル