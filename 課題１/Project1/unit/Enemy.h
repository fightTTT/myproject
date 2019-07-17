#pragma once
#include <tuple>
#include "Obj.h"

enum class ENM_DATA
{
	POS,
	TYPE,
	SIZE,
	TARGTPOS
};

enum class ENM_TYPE
{
	A,
	B,
	C
};

using EnemyData = std::tuple<Vector2Dbl, ENM_TYPE, Vector2,Vector2Dbl>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyData data);
	~Enemy();

	// override‚Æ‘‚­‚±‚Æ‚É‚æ‚Á‚ÄƒI[ƒo[ƒ‰ƒCƒh‚µ–Y‚ê‚É‚æ‚éƒoƒO‚ğ–h~‚·‚é
	void Draw(void) override;	
	UNIT GetUnit(void) override;
	void SetMove();
private:
	bool Init(void);
	ENM_TYPE _type;				// “G‚Ìí—Ş
	Vector2Dbl _targetPos;			// “G‚ª•À‚ÔêŠ
	Vector2Dbl _firstTarget;		// “G‚ªÅ‰‚ÉŒü‚©‚¤êŠ
	int speed;
	bool firstFlag;
	int waitCnt;
	Vector2Dbl _posOld;
	static int animCnt;
	//-----------------
	float _floatPosX;
	float _floatPosY;
	//-----------------
};
