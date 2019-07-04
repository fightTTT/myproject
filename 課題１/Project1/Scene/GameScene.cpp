#include <DxLib.h>
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
	_objList.emplace_back(std::make_shared<Enemy>(Vector2(20, 20)));
	_objList.emplace_back(std::make_shared<Player>(Vector2(100, 100)));

	_ghGameScreen = MakeScreen(lpSceneMng.gameScreenSize.x, lpSceneMng.gameScreenSize.y, true);
}
