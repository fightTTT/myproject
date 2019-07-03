#pragma once
#include <vector>
#include "common/Vector2.h"
#include "Scene/BaseScene.h"

#define lpSceneMng SceneMng::GetInstance()



using DrawQueT = std::tuple<int, int, int>;		// グラフィックハンドル、X座標、Y座標

enum class DRAW_QUE
{
	IMAGE,
	X,
	Y
};

class SceneMng
{
public:
	static SceneMng &GetInstance()
	{
		return *s_Instance;
	}

	void Run(void);

	bool AddDrawQue(DrawQueT dQue);

	const Vector2 screenSize;			// 画面全体のサイズ
	const Vector2 gameScreenSize;		// プレイ画面サイズ
	const Vector2 gameScreenPos;		// 画面全体のサイズに対するプレイ画面サイズのoffSet値

private:
	struct SceneMngDeleter
	{
		void operator()(SceneMng* _debugContOut) const
		{
			delete _debugContOut;
		}
	};

	SceneMng();
	~SceneMng();

	static std::unique_ptr<SceneMng, SceneMngDeleter> s_Instance;
	Unique_Base _activeScene;
	
	std::vector<DrawQueT> drawList;

	bool Init(void);
	void Draw(void);
};

