void DrawChip(int id, int x, int y);

// �`�b�v���iX�����CY�����j
#define XMAX 1000
#define YMAX 50

// �㉺���E���Ȃ������w�i�̕\��
void DrawCirculatedBG(
	int sx, int sy,      // ��ʍ���ɑΉ�����w�i��̈ʒu
	int sw, int sh,      // ��ʂ̑傫��
	int cw, int ch,      // �`�b�v�̑傫��
	int map[XMAX][YMAX]  // �w�i�f�[�^�i�`�b�v�ԍ��̔z��j
) {
	// �`�悷��`�b�v�͈̔�
	int x0=sx/cw, y0=sy/ch;    // ����[�̃`�b�v
	int x1=(sx+sw-1)/cw%XMAX, 
		y1=(sy+sh-1)/ch%YMAX;  // �E���[�̃`�b�v

	// �`�b�v�̕`��F
	// �e�`�b�v�̕`���DrawChip�֐��ōs���Ƃ���B
	for (int i=x0; i!=x1+1; i=(i+1)%XMAX) {
		for (int j=y0; j!=y1+1; j=(j+1)%YMAX) {
			DrawChip(map[i][j], j*cw-sx, i*ch-sy);
		}
	}
}
