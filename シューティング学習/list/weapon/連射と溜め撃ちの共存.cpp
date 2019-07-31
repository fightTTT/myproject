void PowerEffect();
void Shot();
void BigShot(int power);
void MaxShot();

void SemiAutoShot(
	bool button,    // �{�^���̏�ԁi�����ꂽ�Ƃ�true�j
	int min_power,  // ���߃p���[�̍ŏ��l
	int max_power,  // ���߃p���[�̍ő�l
	int max_gauge   // �A�˃Q�[�W�̍ő�l
) {
	// ���߃p���[�C�A�˃Q�[�W
	static int power=0, gauge=0;

	// �{�^���������Ă���ꍇ
	if (button) {
		
		// ���߃p���[�s���̏ꍇ�F
		// �ʏ�̒e�����B
		// ��̓I�ȏ�����Shot�֐��ōs���Ƃ���B
		if (power<min_power) Shot();
	
		// ���߃p���[�\���̏ꍇ�F
		// ���ߏ�Ԃ̕\��������B
		// ��̓I�ȏ�����PowerEffect�֐��ōs���Ƃ���B
		else PowerEffect();
	
		// ���߃p���[�𑝂₵�C�A�˃Q�[�W���ő�ɂ���
		if (power<max_power) power++;
		gauge=max_gauge;
	}
	
	// �{�^���𗣂��Ă���ꍇ�F
	else {
		
		// ���߃p���[�\���̏ꍇ�F
		// ���ߌ����e�����F
		// �ő�p���[�̂Ƃ��͓��ʂȒe�����B
		// ��̓I�ȏ�����MaxShot�֐���BigShot�֐��ōs���Ƃ���B
		if (min_power<=power) {
			if (power==max_power) MaxShot(); 
				else BigShot(power);
			gauge=0;
		}
		
		// �A�˃Q�[�W>0�̏ꍇ�F
		// �ʏ�̒e�������C�A�˃Q�[�W��-1����B
		// ��̓I�ȏ�����Shot�֐��ōs���Ƃ���B
		if (gauge>0) {
			Shot();
			gauge--;
		}

		// ���߃p���[��0�ɂ���
		power=0;
	}
}

