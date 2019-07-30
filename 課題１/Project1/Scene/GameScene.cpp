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

	enemON.resize(50);
	for (int i = 0; i < 50; i++)
	{
		enemON[i] = 1;
	}

	enemON[0] = 0;
	enemON[1] = 0;
	enemON[2] = 0;
	enemON[7] = 0;
	enemON[8] = 0;
	enemON[9] = 0;
	enemON[10] = 0;
	enemON[19] = 0;
	enemON[20] = 0;
	enemON[29] = 0;


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

	if (_objList.size() == 1)
	{
		enemCount[0] = 0;
		enemCount[1] = 0;
	}

	if (checkKey == 1 && checkKeyOld == 0)
	{
		int enemRand = rand();
		for (int i = 0; i < 4;)
		{
			if (enemCount[0] < 50)
			{
				/*if (_objList.size() < 10)
				{*/
				if (enemON[enemCount[0]] == 1)
				{
					enemCount[1]++;
					AddEnemy({ enemAppPos[enemRand % 5], ENM_TYPE(enemRand % 3), {32,32},
						Vector2Dbl(80 + 40 * (enemCount[0] % 10),80 + 40 * (enemCount[0] / 10 % 5)),i,enemCount[1] });
					//}
					enemCount[0]++;
					
					i++;
				}
				else
				{
					enemCount[0]++;
					continue;
				}
			}
			else
			{
				break;
			}
		}
	}

	HitShot();
	SetShot();
	

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

void GameScene::SetShot(void)
{
	static int shotNum = 0;

	for (auto &data : _objList)
	{
		if (shotNum >= 2)
		{
			break;
		}
		if (data->GetShotData().size() >= (2 - shotNum))
		{
			for (auto &shot : data->GetShotData())
			{
				_objList.emplace_back(shot);
				shotNum++;
			}
		}
	}	

	for (auto &data : _objList)
	{
		if (data->GetUnit() == UNIT::SHOT)
		{
			if (data->IsDeath())
			{
				shotNum--;
			}
		}
	}

}

bool GameScene::HitShot(void)
{
	for (auto &shot : _objList)
	{
		if (shot->GetUnit() == UNIT::SHOT)
		{
			for (auto &enem : _objList)
			{
				if (enem->GetUnit() == UNIT::ENEMY)
				{
					if (shot->Pos().y - (shot->Size().y / 2) <= enem->Pos().y + (enem->Size().y / 2)
					 && shot->Pos().y + (shot->Size().y / 2) >= enem->Pos().y - (enem->Size().y / 2)
					 && enem->Pos().x + (enem->Size().x / 2) >= shot->Pos().x - (shot->Size().x / 2)
					 && enem->Pos().x - (enem->Size().x / 2) <= shot->Pos().x + (shot->Size().x / 2))
					{
						enem->IsAlive(false);
						enem->AnimKey(ANIM::DEATH);
						shot->IsDeath(true);

						return true;
					}
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
