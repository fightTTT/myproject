void SpeedControlByButton(
	float& speed,     // �X�s�[�h
	float accel,      // �X�s�[�h�A�b�v�̓x����
	float max_speed,  // �ō���
	float min_speed,  // �Œᑬ
	bool button       // ���x���߃{�^���̓���
) {
	// �O��̃{�^���̏��
	static bool prev_button=false;
	
	// �{�^������x�����ĉ������ꍇ�F
	// ���x���߂��s���B
	if (!prev_button && button) {
		if (speed>=max_speed) speed=min_speed;
		else speed+=accel;
	}
	
	// �{�^���̏�Ԃ��L�^����
	prev_button=button;
}

void SpeedControlByItem(
	float& speed,          // �X�s�[�h
	float max_speed,       // �ō���
	float min_speed,       // �Œᑬ
	float x0, float y0,    // �E������̍�����W
	float x1, float y1,    // �E������̉E�����W
	float ix0, float iy0,  // �A�C�e���̓����蔻��̍�����W
	float ix1, float iy1,  // �A�C�e���̓����蔻��̉E�����W
	float accel            // �X�s�[�h�A�b�v�E�_�E���̓x����
) {
	// �A�C�e�����E�����Ƃ��̏����F
	// �����蔻�菈�����s���C���������Ƃ��ɂ́C
	// �X�s�[�h�A�b�v�܂��̓X�s�[�h�_�E�����s���B
	if (ix0<x1 && x0<ix1 && iy0<y1 && y0<iy1) {
		speed+=accel;
		
		// �ȉ��̂悤�ɂ���ƁC
		// �X�s�[�h�_�E����1�E���������ŁC
		// �X�s�[�h���Œ�ɂȂ�悤�ɂł���B
		// if (accel<0) speed=min_speed;
		
		// �X�s�[�h���ō�����Œᑬ�𒴂�����␳����
		if (speed>max_speed) speed=max_speed;
		if (speed<min_speed) speed=min_speed;
	}
}


