void GrazeBullet(
	float gx0, float gy0,    // �����蔻��̍�����W
	float gx1, float gy1,    // �����蔻��̉E�����W
	int num_bullet,          // �e�̐�
	float x0[], float y0[],  // �e�̓����蔻��̍�����W
	float x1[], float y1[],  // �e�̓����蔻��̉E�����W
	bool grazing[],          // �e���������Ă��邩�ǂ���
	int time[],              // �����莞��
	int& power               // ���@�̃p���[
	                         // �i�o���l�C���_�{���Ȃǁj
) {
	// �S�Ă̒e�ɂ��ď������s��
	for (int i=0; i<num_bullet; i++) {

		// �ʏ��ԁF
		// �����蔻�菈�����s���C�e�����@�ɂ���������C
		// �������Ԃɂ���B
		// �������Ԃ̎c�莞�Ԃ�ݒ肵�C���@�̃p���[�𑝂₷�B
		if (!grazing[i]) {
			if (gx0<x1[i] && x0[i]<gx1 && 
				gy0<y1[i] && y0[i]<gy1) {
				grazing[i]=true;
				time[i]=20;
				power++;
			}
		}
		
		// �������ԁF
		// �������Ԃ̎c�莞�Ԃ����炵�C
		// ���Ԃ�0�ɂȂ�����ʏ��Ԃɖ߂�B
		// ���̏������Ȃ����΁C1�̒e��1�x����������Ȃ��Ȃ�B
		else {
			if (time[i]==0) grazing[i]=false; else time[i]--;
		}
	}
	
}

