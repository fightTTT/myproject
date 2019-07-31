#include <math.h>

void InitDirectedBullet(
	float ex, float ey,    // �G�̍��W
	float& x, float& y,    // �e�̍��W
	float& vx, float& vy,  // �e�̑��x
	float speed,           // �e�̑���
	float theta            // ���ˊp�x
) {
	// �e�̍��W��ݒ肷��
	x=ex; y=ey;

	// ����speed�Ŋp�xtheta�̕����ɔ�Ԓe�̑��x(vx,vy)�����߂�F
	// M_PI�͉~�����B
	vx=cos(M_PI/180*theta)*speed;
	vy=sin(M_PI/180*theta)*speed;
}

void MoveDirectedBullet(
	float& x, float& y,  // �e�̍��W
	float vx, float vy   // �e�̑��x
) {
	// �e�̍��W(x,y)�ɑ��x(vx,vy)��������
	x+=vx;
	y+=vy;
}

