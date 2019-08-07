#pragma once
#include <Unit/Obj.h>
#include <Unit/Bullet.h>
#include <Input/KeyState.h>

// using宣言
using shared_Blt = std::shared_ptr<Bullet>;	// 弾用vectorの型

class Player :
	public Obj
{
public:
	Player();
	Player(Vector2 pos);
	Player(Vector2 pos, std::list<std::shared_ptr<Bullet>>& bulletlist);

	~Player();

	void Draw(void)override;				// 描画関数
	void UpDate(void)override;				// 状態更新用関数

	UNIT GetUnitType(void)override;			// UnitのIDを返す

private:
	bool Init(void);						// 初期化用関数
	std::unique_ptr<InputState> _input;		// ｷｰﾎﾞｰﾄﾞなどの入力用ﾕﾆｰｸﾎﾟｲﾝﾀｰ

	std::shared_ptr<Bullet> _bullet_ptr;	// 弾用ｼｪｱｰﾄﾞﾎﾟｲﾝﾀｰ
	std::vector<shared_Blt> _bullet_vec;	// 弾用固定長配列

	int invincibleFlag = 0;					// ﾀﾞﾒｰｼﾞが入ったときに一定時間無敵にする為のｶｳﾝﾄ
};

// ｸﾗｽ･･･ﾃﾞﾌｫﾙﾄがﾌﾟﾗｲﾍﾞｰﾄ
//class Player :Obj
//{
//public:
//	Player();
//	~Player();
//};


// 構造体･･･ﾃﾞﾌｫﾙﾄがﾊﾟﾌﾞﾘｯｸ
//struct Player : Obj
//{
//public:
//	Player();
//	~Player();
//};