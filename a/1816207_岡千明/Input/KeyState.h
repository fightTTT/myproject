#pragma once
#include <vector>
#include "InputState.h"

class KeyState :
	public InputState
{
public:
	KeyState();
	~KeyState();

	void UpDate(void)override;		// ��ԍX�V�p�֐�

private:
	void DefKey(void);				// ���z�u�������p

	void RefKeyData(void);			// �����X�V�p�֐�
	void SetKeyConfig(void);		// ����̨�ޗp�֐�
	INPUT_ID confID;				// ����̨�ޗpID
	int lastKeyID;					// ��̨�ނōŌ�ɓ��͂�����������(�d���h�~�p)

	bool KeySave(void);				// ������ޗp�֐�
	bool KyeLoad(void);				// �����۰�ޗp�֐�

	char _buf[256];					// �����擾�p
	char _oldBuf[256];				// �ضް�����p

	std::vector<int>_keyCon;		// �����͗pvector

	void(KeyState::*func)(void);	// �֐��߲���(���ް�֐��ւ��߲���)
};

