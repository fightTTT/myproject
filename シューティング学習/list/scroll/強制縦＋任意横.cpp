void DrawBG(int x, int y);
void DrawMyShip(int x, int y);

void MixedScroll(
	int x, int y,  // ���@�̔w�i��̍��W
	int w,         // ���@�̕�
	int sy,        // �X�N���[���ʒu��Y���W
	int svy,       // Y�����̃X�N���[�����x
	int sw,        // ��ʕ�
	int bw         // �w�i�̕�
) {
	// �w�i�̕`��F
	// �X�N���[���ʒu���X�V���C�w�i��`�悷��B
	// �`��̋�̓I�ȏ�����DrawBG�֐��ōs���Ƃ���B
	int sx=(bw-sw)*x/(bw-w);
	sy+=svy;
	DrawBG(sx, sy);
	
	// ���@�̕`��F
	// �X�N���[���ʒu����̑��Έʒu�ɕ\������B
	// �`��̋�̓I�ȏ�����DrawMyShip�֐��ōs���Ƃ���B
	DrawMyShip(x-sx, y-sy);
}

