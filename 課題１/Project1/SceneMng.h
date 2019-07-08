#pragma once
#include <vector>
#include "common/Vector2.h"
#include "Scene/BaseScene.h"

#define lpSceneMng SceneMng::GetInstance()



using DrawQueT = std::tuple<int, int, int>;		// �O���t�B�b�N�n���h���AX���W�AY���W

enum class DRAW_QUE		// MakeScreen�Ő��������X�N���[�����Ǘ�����v�f
{
	IMAGE,		// �O���t�B�b�N�n���h��
	X,			// X���W
	Y			// Y���W
};

class SceneMng
{
public:
	static SceneMng &GetInstance()
	{
		return *s_Instance;
	}

	void Run(void);

	// drawList�ɂ��ꂼ��̃X�N���[����ǉ�����
	bool AddDrawQue(DrawQueT dQue);

	const Vector2 screenSize;			// ��ʑS�̂̃T�C�Y
	const Vector2 gameScreenSize;		// �v���C��ʃT�C�Y
	const Vector2 gameScreenPos;		// ��ʑS�̂̃T�C�Y�ɑ΂���v���C��ʃT�C�Y��offSet�l

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
	
	std::vector<DrawQueT> drawList;		// �X�N���[���o�b�t�@���Ǘ����Ă���List

	bool Init(void);
	void Draw(void);
};

