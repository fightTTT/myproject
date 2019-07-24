#include <DxLib.h>
#include <algorithm>
#include <tuple>
#include "GameScene.h"
#include "../SceneMng.h"
#include "../unit/Player.h"

GameScene::GameScene()
{
	Init();
}


GameScene::~GameScene()
{
}

void GameScene::Init(void)
{
	srand(1);

	_objList.reserve(40);
	_objList.emplace_back(std::make_shared<Player>(Vector2Dbl(100, 100), Vector2(30, 32)));

	enemAppPos = { Vector2Dbl(lpSceneMng.gameScreenSize.x - 15,16),
					Vector2Dbl(15 + lpSceneMng.gameScreenSize.x,lpSceneMng.lpSceneMng.gameScreenSize.y / 2),
					Vector2Dbl(lpSceneMng.gameScreenSize.x - 15,lpSceneMng.gameScreenSize.y / 2),
					Vector2Dbl(15,lpSceneMng.gameScreenSize.y - 16),
					Vector2Dbl(lpSceneMng.gameScreenSize.x - 15,lpSceneMng.gameScreenSize.y - 16), 
				 };

	for (int i = 0; i < 50; i++)
	{
		_targetPos[i].x = 80 + 40 * (i % 10);
		_targetPos[i].y = 80 + 40 * (i / 10 % 5);
	}
	

	_ghGameScreen = MakeScreen(lpSceneMng.gameScreenSize.x, lpSceneMng.gameScreenSize.y, true);
}

Unique_Base GameScene::UpDate(Unique_Base own)
{
	static int enemCount[3];
	for (int i = 0; i > 3; i++)
	{
		enemCount[i] = 0;
	}

	for(auto &data: _objList)
	{
		data->SetMove();
	}

	GetHitKeyStateAll(key);
	
	checkKeyOld = checkKey;

	if (key[KEY_INPUT_I])
	{
		checkKey = 1;
	}
	else
	{
		checkKey = 0;
	}
	

	if (checkKey == 1 && checkKeyOld == 0)
	{
		int enemRand = rand();

		for (int i = 0; i < 3; i++)
		{
			if (enemCount[0] != 0 && enemCount[0] != 1 && enemCount[0] != 2 && enemCount[0] != 7 && enemCount[0] != 8 && enemCount[0] != 9 && enemCount[0] != 10 && enemCount[0] != 19 && enemCount[0] != 20 && enemCount[0] != 29 && enemCount[0] < 50)
			{
				/*if (_objList.size() < 10)
				{*/
				AddEnemy({ enemAppPos[enemRand % 5], ENM_TYPE(enemRand % 3), {32,32}, _targetPos[enemCount[0]],i });
				//}
				enemCount[0]++;
			}
			else
			{
				i = 0;
				enemCount[0]++;
				continue;
			}
		
		}
			
	}

	// std::remove_if(開始位置、終了位置、プレディケート)
	auto deth_itr = std::remove_if(_objList.begin(), _objList.end(), [](std::shared_ptr<Obj> obj) {return obj->IsDeath(); });
	_objList.erase(deth_itr, _objList.end());

	Draw();

	return std::move(own);
}

SCN_ID GameScene::GetScnID(void)
{
	return SCN_ID::GAME;
}

void GameScene::AddEnemy(EnemyData data)
{
	_objList.emplace_back(std::make_shared<Enemy>(data));
}

void GameScene::Draw(void)
{
	int ghBefor;
	ghBefor = GetDrawScreen();
	SetDrawScreen(_ghGameScreen);

	ClsDrawScreen();
	for (auto &data : _objList)
	{
		data->Obj::Draw();
	}
	lpSceneMng.AddDrawQue({ _ghGameScreen,lpSceneMng.gameScreenPos.x, lpSceneMng.gameScreenPos.y });
	SetDrawScreen(ghBefor);
}
