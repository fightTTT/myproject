void Shot();
void AimingShot(int id);
void DirectedShot(int dir);

void LockShot(
	bool button,     // �{�^���̏�ԁi�����ꂽ�Ƃ�true�j
	int min_power,   // ���߃p���[�̍ŏ��l
	int max_gauge,   // �A�˃Q�[�W�̍ő�l
	int enemy_id,    // ���b�N�V���b�g���ǔ����Ă���G��ID
	                 // �i�ǔ����Ă��Ȃ��Ƃ��ɂ͕��̒l�j
	float front_dir  // ���@�̐��ʂɑ����������
) {
	// ���߃p���[�C�A�˃Q�[�W
	static int power=0, gauge=0;

	// �{�^���������Ă���ꍇ
	if (button) {
		
		// ���߃p���[�s���̏ꍇ�F
		// ���߃p���[�𑝂₵�C�A�˃Q�[�W���ő�ɂ��āC
		// �e�����B��̓I�ȏ�����Shot�֐��ōs���Ƃ���B
		if (power<min_power) {
			power++;
			gauge=max_gauge;
			Shot();
		}
	
		// ���߃p���[�\���̏ꍇ�F
		// �A�˃Q�[�W��0�ɂ��āC���b�N�V���b�g�����B
		else {
			gauge=0;
			
			// ���b�N�V���b�g�����F
			// �G��ǔ����Ă���Ƃ��͓G��_����������B
			// �i�u���@�Ɍ������Ĕ�Ԓe�v�Ɠ��l�j
			// �G��ǔ����Ă��Ȃ��Ƃ��͎��@�̐��ʂɒe�����B
			// �i�u���R�ȕ����ɔ�Ԓe�v�Ɠ��l�j
			// ���ꂼ���̓I�ȏ�����AimingShot�֐���
			// DirectedShot�֐��ōs���Ƃ���B
			if (enemy_id>=0) {
				AimingShot(enemy_id);
			} else {
				DirectedShot(front_dir);
			}
		}
	}
	
	// �{�^���𗣂��Ă���ꍇ�F
	else {
		
		// �A�˃Q�[�W>0�̏ꍇ�F
		// ���ʂ̒e�������C�A�˃Q�[�W��-1����B
		if (gauge>0) {
			Shot();
			gauge--;
		}

		// ���߃p���[��0�ɂ���
		power=0;
	}
}

