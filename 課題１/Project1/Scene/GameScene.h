#pragma once
#include <vector>
#include <array>
#include <memory>
#include "BaseScene.h"
#include "../unit/Obj.h"
#include "../unit/Enemy.h"
#include "../Input/InputState.h"
#include "../StarScroll.h"


using EnemLine = std::tuple<ENM_TYPE,Vector2Dbl,int,int>;		// 敵の種類、集合場所の左上座標、X軸機数、Y軸機数

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	Unique_Base UpDate(Unique_Base own) override;

	// 自身のシーンの種類を返す
	SCN_ID GetScnID(void) override;		

	// Enemyを追加する
	void AddEnemy(EnemyData data);		

	void Draw(void);
protected:
	void Init(void)override;
private:

	// shotの当たり判定
	bool HitShot(void);		

	std::vector<Shared_Obj> _objList;		// キャラクターを管理するList
	int _ghGameScreen;
	std::array<Vector2Dbl, 6> enemAppPos;	// 敵の出現座標

	std::unique_ptr<StarScroll> star;

	// デバッグ用
	//--------------------
	char key[256];
	int checkKey = 0;
	int checkKeyOld = 0;
	std::vector<EnemLine> enemLine;
	std::array<std::vector<int>, 3> enemNum;
	//--------------------
};

