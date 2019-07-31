void NormalAttack();
void SpecialAttack();

void ItemSpecialAttack(
	float x0, float y0,        // ���@�̍�����W
	float x1, float y1,        // ���@�̉E�����W
	float ix0[], float iy0[],  // �A�C�e���̍�����W
	float ix1[], float iy1[],  // �A�C�e���̍�����W
	int num_item               // �A�C�e���̐�
) {
	static bool special=false;  // ���̏�Ԃ�����Ȃ��true
	static int time;            // ����U���̎c�莞��
	
	// �ʏ��Ԃ̂Ƃ�
	if (!special) {

		// �ʏ�U�����s���F
		// ��̓I�ȏ�����NormalAttack�֐��ōs���Ƃ���B
		NormalAttack();
		
		// �A�C�e�����E�������ǂ����̔���F
		// �E����������ԂɈڂ�C�c�莞�Ԃ�ݒ肷��B
		for (int i=0; i<num_item; i++) {
			if (ix0[i]<x1 && x0<ix1[i] && 
				iy0[i]<y1 && y0<iy1[i]) {
				special=true;
				time=300;
			}
		}
	}
	
	// �����Ԃ̂Ƃ�
	else {
		
		// ����U�����s���F
		// ��̓I�ȏ�����SpecialAttack�֐��ōs���Ƃ���B
		SpecialAttack();
		
		// ��莞�Ԃ��߂������ǂ����̔���F
		// �c�莞�Ԃ��Ȃ��Ȃ�����ʏ��Ԃɖ߂�B
		if (time==0) special=false; else time--;
	}
}

