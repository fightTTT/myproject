#include <math.h>

void InitAimingBullet(
	float mx, float my,   // ���@�̍��W
	float ex, float ey,   // �G�̍��W
	float speed,          // �e�̑���
	float& x, float& y,   // �e�̍��W
	float& vx, float& vy  // �e�̑��x
) {
	// �e�̍��W��ݒ肷��
	x=ex; y=ey;

	// �ڕW�܂ł̋���d�����߂�
	float d=sqrt((mx-ex)*(mx-ex)+(my-ey)*(my-ey));

	// ���������lspeed�ɂȂ�悤�ɑ��x(vx,vy)�����߂�F
	// �ڕW�܂ł̋���d��0�̂Ƃ��ɂ͉������ɔ��˂���B
	if (d) {
		vx=(mx-ex)/d*speed;
		vy=(my-ey)/d*speed;
	} else {
		vx=0;
		vy=speed;
	}
}

void MoveAimingBullet(
	float& x, float& y,  // �e�̍��W
	float vx, float vy   // �e�̑��x
) {
	// �e�̍��W(x,y)�ɑ��x(vx,vy)��������
	x+=vx;
	y+=vy;
}

