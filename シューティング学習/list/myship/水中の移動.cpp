void WaveEffect();

void Underwater1(
	float& x, float& y,  // ���@�̍��W
	float vx, float vy,  // ���@�̑��x
	float h              // ���ʂ̍���
) {
	// �󒆂̏ꍇ�F
	// �ʏ�̑��x�ňړ�����B
	if (y<h) {
		x+=vx; y+=vy;
	}

	// �����̏ꍇ�F
	// ���x��x������B�����ł͋󒆂̔����Ƃ����B
	else {
		x+=vx/2; y+=vy/2;
	}
}

void Underwater2(
	float& x, float& y,        // ���@�̍��W
	float x0, float y0,        // ���@�̍�����W
	float x1, float y1,        // ���@�̉E�����W
	float vx, float vy,        // ���@�̑��x
	float wx0[], float wy0[],  // ���̓����蔻��
	float wx1[], float wy1[],  // �i������W�C�E�����W�j
	int num_water              // ���̓����蔻��̐�
) {
	// ���@�������ɂ��邩�ǂ����𒲂ׂ�
	int i;
	for (i=0; i<num_water; i++) {
		if (wx0[i]<=x0 && x1<=wx1[i] && 
			wy0[i]<=y0 && y1<=wy1[i]) break;
	}
	
	// ���@�������ɂ���ꍇ�F
	// ���x��x������B�����ł͋󒆂̔����Ƃ����B
	if (i<num_water) {
		x+=vx/2; y+=vy/2;
	}
	
	// ���@�������ɂ͂��Ȃ��ꍇ�F
	// �ʏ�̑��x�ňړ�����
	else {
		x+=vx; y+=vy;
		
		// ���@�����ʂɐڐG���Ă��邩�ǂ����𒲂ׂ�
		for (i=0; i<num_water; i++) {
			if (wx0[i]<x1 && x0<wx1[i] && 
				wy0[i]<y1 && y0<wy1[i]) break;
		}

		// ���@�����ʂɐڐG���Ă���ꍇ�F
		// �g���Ԃ��Ȃǂ̃G�t�F�N�g��\������B
		// ��̓I�ȏ�����WaveEffect�֐��ōs���Ƃ���B
		if (i<num_water) WaveEffect();
	}
}

