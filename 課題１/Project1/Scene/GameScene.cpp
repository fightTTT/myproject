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
	_objList.emplace_back(std::make_shared<Player>(Vector2Dbl(100, 100), Vector2Dbl(30, 32)));

	enemAppPos = { Vector2Dbl(lpSceneMng.gameScreenSize.x - 15,16),
					Vector2Dbl(15 + lpSceneMng.gameScreenSize.x,lpSceneMng.lpSceneMng.gameScreenSize.y / 2),
					Vector2Dbl(lpSceneMng.gameScreenSize.x - 15,lpSceneMng.gameScreenSize.y / 2),
					Vector2Dbl(15,lpSceneMng.gameScreenSize.y - 16),
					Vector2Dbl(lpSceneMng.gameScreenSize.x - 15,lpSceneMng.gameScreenSize.y - 16), 
				 };

	enemLine.reserve(3);
	enemLine.emplace_back(ENM_TYPE::A,Vector2Dbl(30*3,0),4,1);
	enemLine.emplace_back(ENM_TYPE::B, Vector2Dbl(30,32), 8, 2);
	enemLine.emplace_back(ENM_TYPE::C, Vector2Dbl(0,32*3), 10, 2);

	enemNum[0].resize(4);;
	enemNum[0] = {1,2,0,3};
	enemNum[1].resize(16);
	enemNum[1] = {3,11,4,12,2,10,5,13,1,9,6,14,0,8,7,15};
	enemNum[2].resize(20);
	enemNum[2] = { 4,14,5,15,3,13,6,16,2,12,7,17,1,11,8,18,0,10,9,19 };

	_ghGameScreen = MakeScreen(lpSceneMng.gameScreenSize.x, lpSceneMng.gameScreenSize.y, true);
}

Unique_Base GameScene::UpDate(Unique_Base own)
{
	static int enemCount[3];
	static int cnt = 0;
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

	/*if (_objList.size() == 1)
	{
		enemCount[0] = 0;
		enemCount[1] = 0;
	}*/

	if (enemCount[1] >= 40)
	{
		enemCount[2] = 0;
	}

	if (enemCount[0] >= std::get<2>(enemLine[enemCount[2]])*std::get<3>(enemLine[enemCount[2]])-1)
	{
		enemCount[2]++;
		cnt = 0;
		enemCount[0] = 0;
	}


	if (checkKey == 1 && checkKeyOld == 0)
	{
		int enemRand = rand();
		for (int i = 0; i < 4;)
		{
			if (enemCount[1] < 40)
			{
				enemCount[1]++;
				AddEnemy({ enemAppPos[enemRand % 5], ENM_TYPE(std::get<0>(enemLine[enemCount[2]])), {32,32},
					Vector2Dbl(80 + std::get<1>(enemLine[enemCount[2]]).x + 30 * (enemNum[enemCount[2]][cnt] % std::get<2>(enemLine[enemCount[2]])),
								80 + std::get<1>(enemLine[enemCount[2]]).y + 30 * (enemNum[enemCount[2]][cnt] / std::get<2>(enemLine[enemCount[2]]) % std::get<3>(enemLine[enemCount[2]]))),
								i,enemCount[1] });
				enemCount[0]++;

				i++;
				cnt++;
			}
			else
			{
				break;
			}
		}
	}

	HitShot();
	

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

bool GameScene::HitShot(void)
{
	std::vector<Shared_Obj> shotObj;

	for (auto &player : _objList)
	{
		if (player->GetUnit() == UNIT::PLAYER)
		{
			shotObj.resize(player->GetShotData().size());
			shotObj = player->GetShotData();
		}
	}

	for (auto shot : shotObj)
	{
		for (auto &enem : _objList)
		{
			if (enem->GetUnit() == UNIT::ENEMY && enem->IsAlive() == true)
			{
				if (shot->Pos().y - (shot->Size().y / 2) <= enem->Pos().y + (enem->Size().y / 2)
					&& shot->Pos().y + (shot->Size().y / 2) >= enem->Pos().y - (enem->Size().y / 2)
					&& enem->Pos().x + (enem->Size().x / 2) >= shot->Pos().x - (shot->Size().x / 2)
					&& enem->Pos().x - (enem->Size().x / 2) <= shot->Pos().x + (shot->Size().x / 2))
				{
					enem->Life(enem->Life() - 1);
					shot->IsDeath(true);

					return true;
				}
			}
		}
	}

	return true;
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
		data->Draw();
	}

	lpSceneMng.AddDrawQue({ _ghGameScreen,lpSceneMng.gameScreenPos.x, lpSceneMng.gameScreenPos.y });
	SetDrawScreen(ghBefor);
}
