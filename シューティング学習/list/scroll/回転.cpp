#include <math.h>

void DrawChip(int id, int x, int y);

// �`�b�v���iX�����CY�����j
#define XMAX 20
#define YMAX 400

// �w�i�̕\��
void DrawBG(
	int sx, int sy,      // ��ʂ̒��S���W
	int sw, int sh,      // ��ʂ̑傫��
	int cw, int ch,      // �`�b�v�̑傫��
	int map[YMAX][XMAX]  // �w�i�f�[�^�i�`�b�v�ԍ��̔z��j
) {
	// ��]�ŉ�ʓ��ɓ���w�i�̍ő�͈͂����߂�
	int w2=sw/2, h2=sh/2;            // ��ʂ̕��ƍ�����1/2
	int r=(int)sqrt(w2*w2+h2*h2);    // �~�̔��a
	int x0=(sx-r)/cw, y0=(sy-r)/ch;  // ����[�̃`�b�v
	int x1=(sx+r)/cw, y1=(sy+r)/ch;  // �E���[�̃`�b�v

	// �`�b�v�̕`��F
	// �e�`�b�v�̕`���DrawChip�֐��ōs���Ƃ���B
	for (int i=y0; i<=y1; i++) {
		for (int j=x0; j<=x1; j++) {
			DrawChip(map[i][j], j*cw-sx+sw/2, i*ch-sy+sh/2);
		}
	}
}

