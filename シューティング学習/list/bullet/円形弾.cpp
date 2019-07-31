#include <math.h>

void InitCircleBullets(
	int n,                   // �e�̐�
	float speed,             // �e�̑���
	bool odd,                // ��p�^�[���̂Ƃ�true
	float vx[], float vy[]   // �~�`�e�̑��x
) {
	// �e�ƒe�Ƃ̊Ԃ̊p�x���v�Z����
	float rad_step=M_PI*2/n;

	// �ŏ��̒e�̊p�x���v�Z����F
	// ��p�^�[���̂Ƃ��ɂ�rad_step/2�������炷�B
	float rad=odd ? rad_step/2 : 0;

	// n�̒e�̑��x�����߂�F
	// ����speed�Ŋp�xrad�̕����ɔ�Ԓe�̑��x�����߂�B
	// ����͕����e���΂������̉��p�B
	for (int i=0; i<16; i++, rad+=rad_step) {
		vx[i]=cos(rad)*speed;
		vy[i]=sin(rad)*speed;
	}
}

