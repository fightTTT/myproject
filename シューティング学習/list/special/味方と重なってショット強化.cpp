void SpecialShot();
void NormalShot();

void ReinforcedShot(
	float x0, float y0,    // ���@�̍�����W
	float x1, float y1,    // ���@�̉E�����W
	float cx0, float cy0,  // �����@�̍�����W
	float cx1, float cy1,  // �����@�̉E�����W
	bool button            // �V���b�g�{�^���̏��
) {
	// �����Ɛڋ߂��Ă��邩�ǂ����̔���F
	// �ڋ߂��Ă���ꍇ�ɂ͋����V���b�g�C
	// ���Ă��Ȃ��ꍇ�ɂ͒ʏ�̃V���b�g�����B
	// �V���b�g������̓I�ȏ����́C
	// SpecialShot�CNormalShot�̊e�֐��ōs���Ƃ���B
	if (button) {
		if (cx0<x1 && x0<cx1 && cy0<y1 && y0<cy1) {
			SpecialShot();
		} else {
			NormalShot();
		}
	}
}

