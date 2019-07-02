#pragma once
#include <vector> 
#include "InputState.h"

class KeyState :
	public InputState
{
public:
	KeyState();
	~KeyState();
	void Update(void)override;
	
private:
	char _buf[256];					// �L�[�{�[�h�̂��ׂẴL�[�̉�����Ԃ��i�[���Ă���z��
	std::vector<int> _keyCon;		// �L�[�����Ǘ����Ă���vector

	// �����o�֐��|�C���^...���O��Ԃ��w�肷��
	void (KeyState::*func)(void);	// �L�[�R���t�B�O�ƃv���C���[����̐؂�ւ�
	
	// �L�[���͍X�V
	void RefkeyData(void);	
	void confSave(void);
	void ConfLoad(void);

	// �L�[�R���t�B�O���s��
	void SetKeyConfig(void);
	

	INPUT_ID confID;
	int lastKeyID;
};

