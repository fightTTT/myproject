void DeleteShot();
void SpecialShot();

void ReinforcedShot3(
	float sx0, float sy0,  // �V���b�g�̍�����W
	float sx1, float sy1,  // �V���b�g�̉E�����W
	float cx0, float cy0,  // �����̍�����W
	float cx1, float cy1   // �����̉E�����W
) {
	// �V���b�g�Ɩ����Ƃ̓����蔻�菈���F
	// ���������Ƃ��ɂ̓V���b�g�������C
	// ����ɋ����V���b�g���o���B
	// ��̓I�ȏ����́C
	// DeleteShot�CSpecialShot�̊e�֐��ōs���Ƃ���B
	// �V���b�g���������ɁC
	// �V���b�g�̋���������ς�����@������B
	if (cx0<sx1 && sx0<cx1 && cy0<sy1 && sy0<cy1) {
		DeleteShot();
		SpecialShot();
	}
}

