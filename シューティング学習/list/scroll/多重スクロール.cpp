void DrawBG(int id);

void OverlaidScroll(
	int num_bg,           // �w�i�̐�
	int sx[], int sy[],   // �e�w�i��̕\���ʒu
	int svx[], int svy[]  // �e�w�i�̃X�N���[�����x
) {
	// �S�w�i�̕`��F
	// �e�w�i�̕\���ʒu�����ɍX�V������ɕ\������B
	// �\���̋�̓I�ȏ�����DrawBG�֐��ōs���Ƃ���B
	for (int i=0; i<num_bg; i++) {
		sx[i]+=svx[i];
		sy[i]+=svy[i];
		DrawBG(i);
	}
}

