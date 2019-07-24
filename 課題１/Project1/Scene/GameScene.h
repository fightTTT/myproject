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
	SCN_ID GetScnID(void) override;		// 自身のシーンの種類を返す
	void AddEnemy(EnemyData data);
	void Draw(void);
protected:
	void Init(void)override;
private:
	std::vector<Shared_Obj> _objList;
	int _ghGameScreen;
	std::array<Vector2Dbl, 5> enemAppPos;
	char key[256];
	int checkKey = 0;
	int checkKeyOld = 0;
};

