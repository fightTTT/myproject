#pragma once
#include "Obj.h"
#include "E_Bullet.h"

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(Vector2 pos);
	Enemy(Enemy_State state);
	~Enemy();

	void Draw(void)override;		// 描画関数
	void UpDate(void)override;		// 状態更新用関数

	UNIT GetUnitType(void)override;	// ｼｰﾝのIDを返す

private:
	bool Init(void);				// 初期化用関数
	void SetAnimCnt(void);			// ｱﾆﾒｰｼｮﾝｶｳﾝﾄのｾｯﾄ(動きを統一する)

	void (Enemy::*move)(void);		// 移動処理用関数ﾎﾟｲﾝﾀ
	void Sigmoid(void);				// 移動用関数(ｼｸﾞﾓｲﾄﾞ)
	void Spiral(void);				// 移動用関数(回転)
	void MoveLR(void);

	ENEMY_TYPE _type;				// 敵の種類登録用
	AIM_VEC _aim;					// 目的地
	int _moveCnt;					//_aimの配列用

	Vector2Dbl _startPos;			// 出現位置
	Vector2Dbl _len;				// 目的地までの距離

	bool _secSigFlag;				// 2回目のｼｸﾞﾓｲﾄﾞ移動用ﾌﾗｸﾞ

	float _radian;					// 角度
	float _rad;						// 半径(円移動用)
	float _diameter;				// 直径(円移動用)

	bool _lrFlag;					// 左右移動移行ﾌﾗｸﾞ
	Vector2Dbl _centerPos;			// LR_MOVE移動完了時に使用
	double _cnt;

	int _score;				// ｽｺｱ用
	int _gameCnt = 0;

	bool _shotFlag = false;
	std::shared_ptr<E_Bullet> _e_Bullet_ptr;		// 弾用ｼｪｱｰﾄﾞﾎﾟｲﾝﾀｰ
	std::vector<shared_E_Blt> _e_Bullet_vec;		// 弾用固定長配列
};

