#include <math.h>

void MoveHomingBullet(
	float& x, float& y,    // �e�̍��W
	float& vx, float& vy,  // �e�̑��x
	float mx, float my,    // ���@�̍��W
	float speed,           // �e�̑���
	float theta            // ����p�x�̏��
) {
	// �e�̌��̑��x
	float vx0=vx, vy0=vy;

	// ���@�����̑��x�x�N�g��(vx1,vy1)�����߂�
	float vx1, vy1;
	float d=sqrt((mx-x)*(mx-x)+(my-y)*(my-y));
	if (d) {
		vx1=(mx-x)/d*speed;
		vy1=(my-y)/d*speed;
	} else {
		vx1=0;
		vy1=speed;
	}

	// �E������p�x����̑��x�x�N�g��(vx2,vy2)�����߂�F
	// M_PI�͉~�����B
	float rad=M_PI/180*theta;
	float vx2=cos(rad)*vx0-sin(rad)*vy0;
	float vy2=sin(rad)*vx0+cos(rad)*vy0;

	// ���@�����Ɛ���p�x����̂ǂ���ɋȂ��邩�����߂�
	if (vx0*vx1+vy0*vy1<=vx0*vx2+vx0*vy2) {
		
		// ���@����������\�͈͓��̏ꍇ�F
		// ���@�����ɋȂ���
		vx=vx0;
		vy=vy0;

	} else {

		// ���@����������\�͈͊O�̏ꍇ�F
		// ��������p�x����̑��x�x�N�g��(vx3,vy3)�����߂�
		float vx3= cos(rad)*vx0+sin(rad)*vy0;
		float vy3=-sin(rad)*vx0+cos(rad)*vy0;
		
		// �e���玩�@�ւ̑��Έʒu�x�N�g��(px,py)�����߂�
		float px=mx-x, py=my-y;
		
		// �E��肩����肩�����߂�
		if (px*vx2+py*vy2<=px*vx3+py*vy3) {

			// �E���̏ꍇ
			vx=vx2;
			vy=vy2;

		} else {

			// �����̏ꍇ
			vx=vx3;
			vy=vy3;

		}
	}

	// �e�̍��W(x,y)���X�V���āC�e���ړ�������
	x+=vx;
	y+=vy;
}

