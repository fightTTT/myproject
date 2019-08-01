void Shot();
void Laser();

void ShotAndLaser(
	bool button,    // �{�^���̏�ԁi�����ꂽ�Ƃ�true�j
	int min_power,  // ���߃p���[�̍ŏ��l
	int max_gauge   // �A�˃Q�[�W�̍ő�l
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
		// �A�˃Q�[�W��0�ɂ��āC���[�U�[�����B
		// ��̓I�ȏ�����Laser�֐��ōs���Ƃ���B
		else {
			gauge=0;
			Laser();
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

