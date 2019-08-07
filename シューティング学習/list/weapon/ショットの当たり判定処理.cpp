void DeleteOpponent();
void DeleteShot();

void HitShot(
	float x0, float y0,    // �V���b�g�̓����蔻��̍�����W
	float x1, float y1,    // �V���b�g�̓����蔻��̉E�����W
	float attack,          // �V���b�g�̍U����
	float ox0, float oy0,  // �Ώۂ̓����蔻��̍�����W
	float ox1, float oy1,  // �Ώۂ̓����蔻��̉E�����W
	float endurance,       // �Ώۂ̑ϋv��
	bool invincible        // �Ώۂ��j��s�\���ǂ���
) {
	// �V���b�g���Ώۂɓ��������ꍇ
	if (ox0<x1 && x0<ox1 && oy0<y1 && y0<oy1) {

		// �Ώۂ����G�łȂ��ꍇ�F
		// �V���b�g�̍U���͂őΏۂ̑ϋv�͂����C
		// �ϋv�͂�0�ɂȂ�����Ώۂ������B
		// ��̓I�ȏ�����DeleteOpponent�֐��ōs���Ƃ���B
		if (!invincible) {
			endurance-=attack;
			if (endurance<0) DeleteOpponent();
		}
		
		// �V���b�g�������F
		// ��̓I�ȏ�����DeleteShot�֐��ōs���Ƃ���B
		// �����ŃV���b�g�������Ȃ��ƁC�ђʒe�ɂȂ�B
		DeleteShot();
	}
}

