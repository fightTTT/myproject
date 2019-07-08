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
	std::vector<int> _keyCondef;	// �L�[�R���t�B�O�̃f�t�H���g

	// �L�[�R���t�B�O�ƃv���C���[����̐؂�ւ�
	void (KeyState::*func)(void);	// �����o�֐��|�C���^...���O��Ԃ��w�肷��
	
	// �L�[���͍X�V
	void RefkeyData(void);	

	// �L�[�R���t�B�O���Z�[�u
	void confSave(void);
	// �L�[�R���t�B�O��񃍁[�h
	void ConfLoad(void);

	// �L�[�R���t�B�O���s��
	void SetKeyConfig(void);
	

	INPUT_ID confID;	// �L�[�R���t�B�O�̎�ނ̏�������
	int lastKeyID;		// �L�[�R���t�B�O�ōŌ�ɓ��͂����L�[
};

