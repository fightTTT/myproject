#pragma once
#include <list>
#include "BaseScene.h"
#include"Geometry.h"

enum SHOTPT
{
	SHOTPT_3WAY,
	SHOTPT_BARAM,
	SHOTPT_HOUSYA,
	SHOTPT_MAX
};

struct Bullet {
	Position2 pos;//座標
	Vector2 vel;//速度
	bool isActive = false;//生きてるか～？
};

class GameCtrl;
class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base UpDate(unique_Base own);

private:
	Bullet bullets[256];

	Position2 pos;

	SHOTPT shotPT;

	Position2 enemypos/*(320, 25)*/;//敵座標
	Position2 playerpos/*(320, 400)*/;//自機座標

	//弾の半径
	float bulletRadius = 5.0f;

	//自機の半径
	float playerRadius = 10.0f;


	int frameCnt;

	char keystate[256];
	bool isDebugMode = false;
	int skyy = 0;
	int skyy2 = 0;
	int bgidx = 0;

	int enemyH[2];
	int playerH[10];
	int bulletH;
	int sky2H;
	int skyH;
	int bgH[4];

	unsigned int frame;//フレーム管理用

	void Init();
	bool IsHit(const Position2& posA, float radiusA, const Position2& posB, float radiusB);
};

