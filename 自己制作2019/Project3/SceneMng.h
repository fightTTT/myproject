#pragma once

#define lpSceneMng SceneMng::GetInstance()

class SceneMng
{
public:
	static SceneMng &GetInstance()
	{
		static SceneMng s_Instance;
		return s_Instance;
	}
	void Run();
private:
	SceneMng();
	~SceneMng();
	bool Init();

};

