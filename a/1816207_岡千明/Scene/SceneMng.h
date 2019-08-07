#pragma once
#include <memory>
#include <vector>
#include <common/VECTOR2.h>
#include <Scene/BaseScene.h>

// ��`
#define lpSceneMng SceneMng::GetInstance()

// using�錾
using DrawQueT = std::tuple<int, int, int>; // ���̨������٤x���W�y���W

// �摜�ptuple�ϐ�
enum class DRAW_QUE
{
	IMAGE,	// ���̨�������
	X,		// ���WX
	Y		// ���WY
};

class SceneMng
{
public:
	static SceneMng& GetInstance()	// ���ڽ���~���������߲������Q�Ƃ�
	{
		return (*s_Instance);		// *�Œ��g(�׽�̎���)��Ԃ�
	}

	void Run(void);					// �ް�ٰ��

	bool addDrawQue(DrawQueT dQue);	// �摜�̷���ǉ��p�֐�

	const Vector2 screenSize;		// ��ذ݂̻���
	const Vector2 gameScreenSize;	// �ްщ�ʂ̻���
	const Vector2 gameScreenPos;	// �̾��

	const int cnt(void);			// �ޯ����ްѓඳ�Ă̎擾

private:
	// �֐���޼ު��
	// �޽�׸����Ă�
	struct SceneMngDeleter
	{
		void operator()(SceneMng* sceneMng)const
		{
			delete sceneMng;
		}
	};

	SceneMng();
	~SceneMng();

	bool SysInit(void);				// ���я������p�֐�

	void Draw(void);				// �`��֐�

	std::vector<DrawQueT>_drawList;	// �摜�ۑ��pvector

	static std::unique_ptr<SceneMng, SceneMngDeleter> s_Instance;	// �ݽ�ݽ�p�ư��߲���
	shared_Base _activeScene;		// ���݂̼�݂������߲���

	int _cnt = 0;					// �ްѓඳ��(��Ұ��ݓ���p)
};

