#pragma once
#include "BaseScene.h"

class SceneMng
{
public:
	static SceneMng &GetInstance(void)			// ���̸׽���߲�����擾����A�����żݸ���݂̏�Ԃɂ��Ă���
	{
		static SceneMng s_Instance;
		return s_Instance;
	}
	void Run(void);

private:
	SceneMng();
	~SceneMng();

	unique_Base activeScene;	// �e��݂ɱ������邽�߂��ư��߲���

	bool SysInit(void);			// ���ѓI�ȕϐ��̏��������s��
};

