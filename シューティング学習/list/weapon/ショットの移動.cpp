void DeleteShot();

void MoveShot(
	float& x0, float& y0,  // �V���b�g�̍�����W
	float& x1, float& y1,  // �V���b�g�̉E�����W
	float vx, float vy,    // �V���b�g�̑��x�iX�����CY�����j
	float sx0, float sy0,  // ��ʘg�̍�����W
	float sx1, float sy1   // ��ʘg�̉E�����W
) {
	// �V���b�g����ʊO�ɏo�Ă���������F
	// ��̓I�ȏ�����DeleteShot�֐��ōs���Ƃ���B
	if (x1<=sx0 || sx1<=x0 || y1<=sy0 || sy1<=y0) DeleteShot();

	// �V���b�g���ړ�����i���W���X�V����j
	x0+=vx; y0+=vy;
	x1+=vx; y1+=vy;
}

