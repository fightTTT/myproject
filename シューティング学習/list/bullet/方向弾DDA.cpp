#include <math.h>

void InitDirectedBulletDDA(
	int theta,         // ���ˊp�x
	int ex, int ey,    // �G�̍��W
	int& x, int& y,    // �e�̍��W
	int& vx, int& vy,  // �e�̈ړ�����
	int& dx, int& dy,  // X������Y�����̍���
	int& diff          // �덷
) {
	// ���z�I�Ȏ��@�������ɔz�u����F
	// M_PI�͉~�����B
	int mx=cos(M_PI/180*theta)*1000;
	int my=sin(M_PI/180*theta)*1000;

	// ���Ƃ�DDA���g�����_�������e�̏����Ɠ���

	// �e�̍��W��ݒ肷��
	x=ex; y=ey;

	// �e�̈ړ�����(vx,vy)�����߂�F�l��1�܂���-1
	vx=mx>ex?1:-1;
	vy=my>ey?1:-1;

	// �ڕW�ɑ΂���X������Y�����̍����̐�Βl(dx,dy)�����߂�
	dx=mx>=ex?mx-ex:ex-mx;
	dy=my>=ey?my-ey:ey-my;

	// �덷diff�Fdx>=dy�̂Ƃ���dx/2�Cdx<dy�̂Ƃ���dy/2�Ƃ���
	diff=dx>=dy?dx/2:dy/2;
}

