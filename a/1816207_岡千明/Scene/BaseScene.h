#pragma once
#include <memory>

// ��ݗpID
// �׽���ŉ����킩��悤�ɂ��ϐ����͒Z�߂ɂ���
enum class SCN_ID
{
	TITLE,	// 
	GAME,	// �ްѼ��
	MAX
};

// �������ߐ錾
class BaseScene;

// using�錾
using shared_Base = std::shared_ptr<BaseScene>;			// �������߲���

class BaseScene
{
public:
	BaseScene() {};
	virtual ~BaseScene() {};

	virtual shared_Base UpDate(shared_Base own) = 0;	// ��ԑJ��
	virtual SCN_ID GetScnID(void) = 0;					// �����̼�݂�ID��Ԃ�(�������z�֐�)
};

