bool PickItem();
void PowerUp(int id);

// �p���[�A�b�v�̎��
typedef enum {
	NONE,  // �J�[�\�����Ȃ����
	SPEED, MISSILE, DOUBLE, 
	LASER, OPTION, BARRIER, 
	END    // �Q�[�W�̉E�[������
} POWER_UP_TYPE;

// �Q�[�W���g�����p���[�A�b�v
void PowerUpGauge(
	bool power_up_button  // �p���[�A�b�v�{�^���̓���
) {
	static POWER_UP_TYPE cursor=NONE;  // �J�[�\���̈ʒu
	
	// �A�C�e�����E�����Ƃ��̏����F
	// �A�C�e�����E������C�J�[�\����1�E�ɓ������B
	// �E�[�܂œ������獶�[�ɖ߂��B
	// �E�����菈����PickItem�֐��ōs���Ƃ���B
	if (PickItem()) {
		cursor++;
		if (cursor==END) cursor=SPEED;
	}
	
	// �p���[�A�b�v�̏����F
	// �{�^���������ꂽ��C
	// �J�[�\�����w���Ă���p���[�A�b�v���s���B
	// ��̓I�ȏ�����PowerUp�֐��ōs���Ƃ���B
	if (power_up_button) {
		PowerUp(cursor);
	}
}

