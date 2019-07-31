#include <math.h>

void MoveTentacle(
	float x[], float y[],  // �e�p�[�c�̍��W
	int num_part,          // �p�[�c�̐�
	float tx, float ty,    // �ڕW�̍��W
	float v,               // ��[���ړ����鑬��
	float limit,           // ��[�ƍ����̍ő勗��
	int num_loop           // �v�Z�̌J��Ԃ���
) {
	// ��[�̍��W�ƍ����̍��W
	float hx=x[0], hy=y[0];
	float rx=x[num_part-1], ry=y[num_part-1];

	// �ڕW�̕����ɐ�[�𓮂���
	hx+=(tx>=hx+v ? v : (tx<=hx-v ? -v : 0));
	hy+=(ty>=hy+v ? v : (ty<=hy-v ? -v : 0));

	// ��[�̈ړ��͈͂𐧌�����F
	// ��[�ƍ����Ƃ̋��������E�l�𒴂��Ă�����C
	// �ړ��\�͈͓��ɖ߂��B
	float dx=hx-rx, dy=hy-ry;
	float d=sqrt(dx*dx+dy*dy);
	if (d>limit) {
		hx=dx*limit/d+rx;
		hy=dy*limit/d+ry;
	}

	// ���ԕ����̍��W���v�Z����F
	// �אڕ����̍��W�̕��ς��Ƃ�B
	// �v�Z�͐�[���獪���Ɍ������čs���B
	// �K�v�ɉ����Čv�Z�𕡐���J��Ԃ��B
	x[0]=hx; y[0]=hy;
	for (int l=0; l<num_loop; l++) {
		for (int i=1; i<num_part-1; i++) {
			x[i]=(x[i-1]+x[i+1])/2;
			y[i]=(y[i-1]+y[i+1])/2;
		}
	}
}

