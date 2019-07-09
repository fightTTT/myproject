#include <DxLib.h>
#include <algorithm>
#include "GameScene.h"
#include "../SceneMng.h"
#include "../unit/Enemy.h"
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
	for(auto &data: _objList)
	{
		data->SetMove();
	}

	
	auto deth_itr = std::remove_if(_objList.begin(), _objList.end(), [](std::shared_ptr<Obj> obj) {return obj->IsAlive(); });
	_objList.erase(deth_itr, _objList.end());

	Draw();

	return std::move(own);
}

SCN_ID GameScene::GetScnID(void)
{
	return SCN_ID::GAME;
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
	_objList.emplace_back(std::make_shared<Enemy>(Vector2(40*2, 80*4), Vector2(30, 32), KEY_INPUT_NUMPAD0));
	_objList.emplace_back(std::make_shared<Enemy>(Vector2(40, 80), Vector2(30, 32), KEY_INPUT_NUMPAD1));
	_objList.emplace_back(std::make_shared<Enemy>(Vector2(40*2, 80), Vector2(30, 32), KEY_INPUT_NUMPAD2));
	_objList.emplace_back(std::make_shared<Enemy>(Vector2(40*3, 80), Vector2(30, 32), KEY_INPUT_NUMPAD3));
	_objList.emplace_back(std::make_shared<Enemy>(Vector2(40, 80*2), Vector2(30, 32), KEY_INPUT_NUMPAD4));
	_objList.emplace_back(std::make_shared<Enemy>(Vector2(40*2, 80*2), Vector2(30, 32), KEY_INPUT_NUMPAD5));
	_objList.emplace_back(std::make_shared<Enemy>(Vector2(40*3, 80*2), Vector2(30, 32), KEY_INPUT_NUMPAD6));
	_objList.emplace_back(std::make_shared<Enemy>(Vector2(40, 80*3), Vector2(30, 32), KEY_INPUT_NUMPAD7));
	_objList.emplace_back(std::make_shared<Enemy>(Vector2(40*2, 80*3), Vector2(30, 32), KEY_INPUT_NUMPAD8));
	_objList.emplace_back(std::make_shared<Enemy>(Vector2(40*3, 80*3), Vector2(30, 32), KEY_INPUT_NUMPAD9));
	/*for (int i = 0; i < 9; i++)
	{
		_objList.emplace_back(std::make_shared<Enemy>(Vector2(20*(i%3+1), 20 * (i / 3 + 1)), Vector2(30, 32)));
	}*/
	_objList.emplace_back(std::make_shared<Player>(Vector2(100, 100), Vector2(30, 32)));


	_ghGameScreen = MakeScreen(lpSceneMng.gameScreenSize.x, lpSceneMng.gameScreenSize.y, true);
}
