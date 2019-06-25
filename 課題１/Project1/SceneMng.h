#pragma once
#include "Scene/BaseScene.h"

#define lpSceneMng SceneMng::GetInstance()

class SceneMng
{
public:
	static SceneMng &GetInstance()
	{
		return *s_Instance;
	}

	void Run(void);
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
	
	bool Init(void);
};

