void DrawChip(int id, int x, int y);

// �`�b�v���iX�����CY�����j
#define XMAX 20
#define YMAX 400

// �w�i�̕\��
void DrawBG(
	int sx, int sy,      // ��ʍ���ɑΉ�����w�i��̈ʒu
	int sw, int sh,      // ��ʂ̑傫��
	int cw, int ch,      // �`�b�v�̑傫��
	int map[YMAX][XMAX]  // �w�i�f�[�^�i�`�b�v�ԍ��̔z��j
) {
	// �`�悷��`�b�v�͈̔�
	int x0=sx/cw, y0=sy/ch;                // ����[�̃`�b�v
	int x1=(sx+sw-1)/cw, y1=(sy+sh-1)/ch;  // �E���[�̃`�b�v

	// �`�b�v�̕`��F
	// �e�`�b�v�̕`���DrawChip�֐��ōs���Ƃ���B
	for (int i=y0; i<=y1; i++) {
		for (int j=x0; j<=x1; j++) {
			DrawChip(map[i][j], j*cw-sx, i*ch-sy);
		}
	}
}

