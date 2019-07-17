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

Unique_Base GameScene::UpDate(Unique_Base own)
{
	static int enemCount = 0;

	for(auto &data: _objList)
	{
		data->SetMove();
	}

	GetHitKeyStateAll(key);

	if (key[KEY_INPUT_I])
	{
		int enemRand = rand();
		for (int i = 0; i < 3; i++)
		{
			if (_objList.size() < 22)
			{
				AddEnemy({ enemAppPos[enemRand % 6][i], ENM_TYPE(enemRand % 3), {32,32},Vector2Dbl(80 + 40 * (enemCount % 7),80 + 40 * (enemCount / 7 % 3) )});
				enemCount++;
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

void GameScene::Init(void)
{
	srand(1);
	/*_objList.emplace_back(std::make_shared<Enemy>(Vector2(20*2, 20*4), Vector2(30, 32)));
	for (int i = 0; i < 9; i++)
	{
		_objList.emplace_back(std::make_shared<Enemy>(Vector2(20*(i%3+1), 20 * (i / 3 + 1)), Vector2(30, 32)));
	}*/

	
	_objList.reserve(22);
	_objList.emplace_back(std::make_shared<Player>(Vector2Dbl(100, 100), Vector2(30, 32)));

	enemAppPos = { {
	{Vector2Dbl(-lpSceneMng.gameScreenPos.x + 15,-lpSceneMng.gameScreenPos.y + 16),
	Vector2Dbl(-lpSceneMng.gameScreenPos.x + 15*3,-lpSceneMng.gameScreenPos.y + 16* 3),
	Vector2Dbl(-lpSceneMng.gameScreenPos.x + 15*6,-lpSceneMng.gameScreenPos.y + 16* 6)},

	{Vector2Dbl(-lpSceneMng.gameScreenPos.x + lpSceneMng.screenSize.x - 15,-lpSceneMng.gameScreenPos.y + 16),
	Vector2Dbl(-lpSceneMng.gameScreenPos.x + lpSceneMng.screenSize.x - 15 * 3,-lpSceneMng.gameScreenPos.y + 16 * 3),
	Vector2Dbl(-lpSceneMng.gameScreenPos.x + lpSceneMng.screenSize.x - 15 * 6,-lpSceneMng.gameScreenPos.y + 16 * 6)},

	{Vector2Dbl(-lpSceneMng.gameScreenPos.x + 15,-lpSceneMng.gameScreenPos.y + lpSceneMng.screenSize.y / 2),
	Vector2Dbl(-lpSceneMng.gameScreenPos.x + 15 * 3,-lpSceneMng.gameScreenPos.y + lpSceneMng.screenSize.y / 2),
	Vector2Dbl(-lpSceneMng.gameScreenPos.x + 15 * 6,-lpSceneMng.gameScreenPos.y + lpSceneMng.screenSize.y / 2)},

	{Vector2Dbl(-lpSceneMng.gameScreenPos.x + lpSceneMng.screenSize.x - 15,-lpSceneMng.gameScreenPos.y + lpSceneMng.screenSize.y / 2),
	Vector2Dbl(-lpSceneMng.gameScreenPos.x + lpSceneMng.screenSize.x - 15 * 3,-lpSceneMng.gameScreenPos.y + lpSceneMng.screenSize.y / 2),
	Vector2Dbl(-lpSceneMng.gameScreenPos.x + lpSceneMng.screenSize.x - 15 * 6,-lpSceneMng.gameScreenPos.y + lpSceneMng.screenSize.y / 2)},

	{Vector2Dbl(-lpSceneMng.gameScreenPos.x + 15,-lpSceneMng.gameScreenPos.y + lpSceneMng.screenSize.y - 16),
	Vector2Dbl(-lpSceneMng.gameScreenPos.x + 15 * 3,-lpSceneMng.gameScreenPos.y + lpSceneMng.screenSize.y - 16 * 3),
	Vector2Dbl(-lpSceneMng.gameScreenPos.x + 15 * 6,-lpSceneMng.gameScreenPos.y + lpSceneMng.screenSize.y - 16 * 6)},

	{Vector2Dbl(-lpSceneMng.gameScreenPos.x + lpSceneMng.screenSize.x - 15,-lpSceneMng.gameScreenPos.y + lpSceneMng.screenSize.y - 16),
	Vector2Dbl(-lpSceneMng.gameScreenPos.x + lpSceneMng.screenSize.x - 15 * 3,-lpSceneMng.gameScreenPos.y + lpSceneMng.screenSize.y - 16 * 3),
	Vector2Dbl(-lpSceneMng.gameScreenPos.x + lpSceneMng.screenSize.x - 15 * 6,-lpSceneMng.gameScreenPos.y + lpSceneMng.screenSize.y - 16 * 6)},}
	};
	_ghGameScreen = MakeScreen(lpSceneMng.gameScreenSize.x, lpSceneMng.gameScreenSize.y, true);
}
