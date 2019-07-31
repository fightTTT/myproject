#include <math.h>

void MoveSimpleHomingBullet(
	float& x, float& y,  // �e�̍��W
	float mx, float my,  // ���@�̍��W
	float speed          // �e�̑���
) {
	// �ڕW�܂ł̋���d�����߂�
	float d=sqrt((mx-x)*(mx-x)+(my-y)*(my-y));

	// �e�̑��x(vx, vy)�����߂�F
	// ���������lspeed�ɂȂ�悤�ɂ���B
	// �ڕW�܂ł̋���d��0�̂Ƃ��ɂ͑��x���������ɂ���B
	float vx, vy;
	if (d) {
		vx=(mx-x)/d*speed;
		vy=(my-y)/d*speed;
	} else {
		vx=0;
		vy=speed;
	}

	// �e�̍��W(x,y)���X�V���āC�e���ړ�������
	x+=vx;
	y+=vy;
}

