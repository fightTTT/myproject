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
	if (key[KEY_INPUT_I]&&!_objList.size())
	{

		AddEnemy({ enemAppPos[rand()%6], ENM_TYPE(rand() % 3), {32,32},{80+40 *( enemCount%7),80+40 * (enemCount % 3)} });
		enemCount++;
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
	_objList.emplace_back(std::make_shared<Enemy>(std::get<0>(data), std::get<1>(data), std::get<2>(data), std::get<3>(data)));
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

	/*srand(1);*/
	/*_objList.emplace_back(std::make_shared<Enemy>(Vector2(20*2, 20*4), Vector2(30, 32)));
	for (int i = 0; i < 9; i++)
	{
		_objList.emplace_back(std::make_shared<Enemy>(Vector2(20*(i%3+1), 20 * (i / 3 + 1)), Vector2(30, 32)));
	}*/

	
	_objList.reserve(22);
	_objList.emplace_back(std::make_shared<Player>(Vector2(100, 100), Vector2(30, 32)));

	enemAppPos = {
		Vector2(-lpSceneMng.gameScreenPos.x + 15,-lpSceneMng.gameScreenPos.y + 16),
		Vector2(-lpSceneMng.gameScreenPos.x+lpSceneMng.screenSize.x - 15,-lpSceneMng.gameScreenPos.y+16),
		Vector2(-lpSceneMng.gameScreenPos.x + 15,-lpSceneMng.gameScreenPos.y + lpSceneMng.screenSize.y / 2),
		Vector2(-lpSceneMng.gameScreenPos.x + lpSceneMng.screenSize.x - 15,-lpSceneMng.gameScreenPos.y+lpSceneMng.screenSize.y/2),
		Vector2(-lpSceneMng.gameScreenPos.x + 15,-lpSceneMng.gameScreenPos.y + lpSceneMng.screenSize.y - 16),
		Vector2(-lpSceneMng.gameScreenPos.x + lpSceneMng.screenSize.x - 15,-lpSceneMng.gameScreenPos.y + lpSceneMng.screenSize.y - 16)};
	_ghGameScreen = MakeScreen(lpSceneMng.gameScreenSize.x, lpSceneMng.gameScreenSize.y, true);
}
