#pragma once
#include <vector>
#include <array>
#include "BaseScene.h"
#include "../unit/Obj.h"
#include "../unit/Enemy.h"
#include "../Input/InputState.h"


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
	std::vector<Shared_Obj> _objList;		// キャラクターを管理するList
	int _ghGameScreen;
	std::array<Vector2Dbl, 5> enemAppPos;	// 敵の出現座標

	// デバッグ用
	//--------------------
	char key[256];
	int checkKey = 0;
	int checkKeyOld = 0;
	std::vector<char> enemON;
	//--------------------
};

